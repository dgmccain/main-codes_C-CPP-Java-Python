import React, { useState, useEffect } from 'react';
import { getLocations } from '../api/locations';
import { predictPrice } from '../api/pricePrediction';
// import { savePricePrediction } from '../api/priceHistory';

const PricePrediction = ({ userId, token }) => {
  const [squareMeters, setSquareMeters] = useState('');
  const [numBedrooms, setNumBedrooms] = useState('');
  const [numBathrooms, setNumBathrooms] = useState('');
  const [numFloors, setNumFloors] = useState('');
  const [location, setLocation] = useState('');
  const [locations, setLocations] = useState([]);
  const [predictedPrice, setPredictedPrice] = useState(null);
  const [error, setError] = useState('');

  useEffect(() => {
    // Fetch locations from backend
    const fetchLocations = async () => {
      try {
        const data = await getLocations(token);

        // Filter unique city-country combinations
        const uniqueLocations = [];
        const seen = new Set();
        data.forEach((loc) => {
          const key = `${loc.city}, ${loc.country}`;
          if (!seen.has(key)) {
            seen.add(key);
            uniqueLocations.push(loc);
          }
        });
        setLocations(uniqueLocations);
      } catch (err) {
        setError('Failed to fetch locations');
      }
    };

    fetchLocations();
  }, [token]);

  const handlePredict = async (e) => {
    e.preventDefault();
    setError('');

    // Validation
    if (squareMeters < 11 || squareMeters > 30000) {
      setError('Square meters must be between 11 and 30,000');
      return;
    }
    if (numBedrooms < 1 || numBedrooms > 260) {
      setError('Number of bedrooms must be between 1 and 260');
      return;
    }
    if (numBathrooms < 1 || numBathrooms > 260) {
      setError('Number of bathrooms must be between 1 and 260');
      return;
    }
    if (numFloors < 1 || numFloors > 170) {
      setError('Number of floors must be between 1 and 170');
      return;
    }

    try {
      const response = await predictPrice(
        {
          sq_mt_built: squareMeters,
          n_rooms: numBedrooms,
          n_bathrooms: numBathrooms,
          n_floors: numFloors,
          location,
        },
        token
      );
      setPredictedPrice(response.predicted_price);

      // Save the price prediction into the price history table if the user is logged in
      // if (userId) {
      //   await savePricePrediction(
      //     {
      //       user_id: userId,
      //       sq_mt_built: squareMeters,
      //       n_rooms: numBedrooms,
      //       n_bathrooms: numBathrooms,
      //       n_floors: numFloors,
      //       predicted_price: response.predicted_price,
      //     },
      //     token
      //   );
      // }
    } catch (err) {
      setError('Failed to get price prediction');
    }
  };

  return (
    <div className='price-prediction-container'>
      <h1>Price Prediction</h1>
      <form onSubmit={handlePredict} className='price-prediction-form'>
        {/* Location Dropdown */}
        <div className='price-form-group'>
          <label>Location:</label>
          <select
            value={location}
            onChange={(e) => setLocation(e.target.value)}
            className='form-control'
            required
          >
            <option value=''>Select a location</option>
            {locations.map((loc) => (
              <option key={loc.location_id} value={loc.location_id}>
                {loc.city}, {loc.country}
              </option>
            ))}
          </select>
        </div>
        {/* Square Meters Input */}
        <div className='price-form-group'>
          <label>Square Meters:</label>
          <input
            type='number'
            id='squareMeters'
            value={squareMeters}
            onChange={(e) => setSquareMeters(e.target.value)}
            className='form-control'
            min='11'
            max='30000'
            required
          />
        </div>
        {/* Bedrooms Input */}
        <div className='price-form-group'>
          <label>Number of Bedrooms:</label>
          <input
            type='number'
            id='numBedrooms'
            value={numBedrooms}
            onChange={(e) => setNumBedrooms(e.target.value)}
            className='form-control'
            min='1'
            max='260'
            required
          />
        </div>
        {/* Bathrooms Input */}
        <div className='price-form-group'>
          <label>Number of Bathrooms:</label>
          <input
            type='number'
            id='numBathrooms'
            value={numBathrooms}
            onChange={(e) => setNumBathrooms(e.target.value)}
            className='form-control'
            min='1'
            max='260'
            required
          />
        </div>
        {/* Floors Input */}
        <div className='price-form-group'>
          <label>Number of Floors:</label>
          <input
            type='number'
            id='numFloors'
            value={numFloors}
            onChange={(e) => setNumFloors(e.target.value)}
            className='form-control'
            min='1'
            max='170'
            required
          />
        </div>
        {/* Submit Button */}
        <div className='price-form-group'>
          <button type='submit' className='submit-price-btn'>
            Get Predicted Price
          </button>
        </div>
      </form>

      {predictedPrice && (
        <div className='prediction-result'>
          Predicted Price: <span className='price'>{predictedPrice}</span>
        </div>
      )}
      {error && <div className='error-message'>{error}</div>}
    </div>
  );
};

export default PricePrediction;
