import React, { useState, useEffect } from 'react';
import { getAllProperties } from '../api/properties';
import { getLocationById } from '../api/locations';

const PropertiesList = () => {
  const [properties, setProperties] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [currentPage, setCurrentPage] = useState(1);
  const [loadingMessageVisible, setLoadingMessageVisible] = useState(false);
  const propertiesPerPage = 10;

  useEffect(() => {
    // Set timeout for showing "Loading properties..." after 3 seconds
    const timeout = setTimeout(() => {
      if (loading) {
        setLoadingMessageVisible(true);
      }
    }, 3000);

    const getProperties = async () => {
      try {
        const data = await getAllProperties();
        console.log('Fetched properties:', data); // Debugging fetched data
        const enrichedData = await Promise.all(
          data.map(async (entry) => {
            try {
              const location = await getLocationById(entry.location_id);
              return { ...entry, ...location };
            } catch (locErr) {
              console.error('Error fetching location:', locErr);
              return { ...entry }; // Fallback in case location fails
            }
          })
        );
        setProperties(enrichedData);
      } catch (err) {
        console.error('Error fetching properties:', err);
        setError('Failed to load properties');
      } finally {
        setLoading(false);
        setLoadingMessageVisible(false); // Hide the "Loading" message once done
      }
    };

    getProperties();

    // Cleanup timeout if the component unmounts or the data is fetched early
    return () => clearTimeout(timeout);
  }, [loading]);

  // Calculate pagination details
  const indexOfLastProperty = currentPage * propertiesPerPage;
  const indexOfFirstProperty = indexOfLastProperty - propertiesPerPage;
  const currentProperties = properties.slice(
    indexOfFirstProperty,
    indexOfLastProperty
  );
  const totalPages = Math.ceil(properties.length / propertiesPerPage);

  const handlePageChange = (pageNumber) => {
    if (pageNumber !== currentPage) {
      console.log('Changing to page:', pageNumber); // Debugging page change
      setCurrentPage(pageNumber);
    }
  };

  return (
    <div className='extra-space-div'>
      <div className='properties-list-container'>
        <h1>Properties List</h1>
        {loading ? (
          loadingMessageVisible && (
            <p style={{ textAlign: 'center', fontWeight: 'bold' }}>
              Loading properties...
            </p>
          )
        ) : error ? (
          <div className='alert alert-danger'>{error}</div>
        ) : (
          <div>
            <table className='properties-table'>
              <thead>
                <tr>
                  <th>City, Country</th>
                  <th>Address</th>
                  <th>Square Meters</th>
                  <th>Number of Bedrooms</th>
                  <th>Number of Bathrooms</th>
                  <th>Number of Floors</th>
                  <th>Buy Price</th>
                </tr>
              </thead>
              <tbody>
                {currentProperties.map((property) => (
                  <tr key={property.property_id}>
                    <td>
                      {property.city}, {property.country}
                    </td>
                    <td>{property.address}</td>
                    <td>{property.square_meters}</td>
                    <td>{property.num_bedrooms}</td>
                    <td>{property.num_bathrooms}</td>
                    <td>{property.num_floors}</td>
                    {property.buy_price.toLocaleString('en-US', {
                      style: 'currency',
                      currency: 'USD',
                    })}
                  </tr>
                ))}
              </tbody>
            </table>
            <div className='pagination-buttons'>
              {Array.from({ length: totalPages }, (_, index) => (
                <button
                  key={`page-${index}`}
                  onClick={() => handlePageChange(index + 1)}
                  className={currentPage === index + 1 ? 'active-page' : ''}
                >
                  {index + 1}
                </button>
              ))}
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default PropertiesList;
