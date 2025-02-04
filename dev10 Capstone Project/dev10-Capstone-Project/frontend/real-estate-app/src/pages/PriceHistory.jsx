import React, { useEffect, useState } from 'react';
import { getPriceHistory } from '../api/priceHistory';
import { getPropertyById } from '../api/properties';
import { getLocationById } from '../api/locations';

const PriceHistory = ({ userId, token }) => {
  const [priceHistory, setPriceHistory] = useState([]);
  const [error, setError] = useState('');
  const [isLoading, setIsLoading] = useState(true);
  const [loadingMessageVisible, setLoadingMessageVisible] = useState(false); // For the "Loading..." message
  const [currentPage, setCurrentPage] = useState(1);
  const [totalPages, setTotalPages] = useState(1);
  const itemsPerPage = 5;

  useEffect(() => {
    // Set timeout for showing "Loading..." after 3 seconds
    const timeout = setTimeout(() => {
      if (isLoading) {
        setLoadingMessageVisible(true);
      }
    }, 3000);

    const fetchData = async () => {
      try {
        const data = await getPriceHistory(userId, token);
        if (data.length === 0) {
          throw new Error(
            'You have not added any price prediction history yet. Try predicting a price first.'
          );
        }
        const enrichedData = await Promise.all(
          data.map(async (entry) => {
            const property = await getPropertyById(entry.property_id);
            const location = await getLocationById(property.location_id);
            return { ...entry, ...property, ...location };
          })
        );
        setPriceHistory(enrichedData);
        setTotalPages(Math.ceil(enrichedData.length / itemsPerPage));
      } catch (err) {
        setError(err.message);
      } finally {
        setIsLoading(false);
        setLoadingMessageVisible(false); // Hide the "Loading" message once done
      }
    };

    fetchData();

    // Cleanup timeout if the component unmounts or the data is fetched early
    return () => clearTimeout(timeout);
  }, [userId, token, isLoading]);

  const handlePageChange = (pageNumber) => {
    setCurrentPage(pageNumber);
  };

  const indexOfLastItem = currentPage * itemsPerPage;
  const indexOfFirstItem = indexOfLastItem - itemsPerPage;
  const currentItems = priceHistory.slice(indexOfFirstItem, indexOfLastItem);

  return (
    <div className='price-history-container'>
      <h1>Price Prediction History</h1>
      {isLoading ? (
        loadingMessageVisible && (
          <p style={{ textAlign: 'center', fontWeight: 'bold' }}>
            Loading History...
          </p>
        ) // Show message after 3 seconds
      ) : error ? (
        <div className='alert alert-danger'>
          {error === 'No price prediction history found' ? (
            <p>No history found for this user.</p>
          ) : (
            <p>{error}</p>
          )}
        </div>
      ) : priceHistory.length === 0 ? (
        <p>No history found.</p>
      ) : (
        <>
          <table className='price-history-table'>
            <thead>
              <tr>
                <th>City, Country</th>
                <th>Address</th>
                <th>Predicted Price</th>
                <th>Predicted Date</th>
              </tr>
            </thead>
            <tbody>
              {currentItems.map((entry) => (
                <tr key={entry.prediction_id}>
                  <td>
                    {entry.city}, {entry.country}
                  </td>
                  <td>{entry.address}</td>
                  <td>
                    {entry.predicted_price.toLocaleString('en-US', {
                      style: 'currency',
                      currency: 'USD',
                    })}
                  </td>
                  <td>
                    {new Date(entry.prediction_date).toLocaleString('en-US', {
                      month: 'long',
                      day: 'numeric',
                      year: 'numeric',
                    })}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
          <div className='pagination-buttons'>
            {Array.from({ length: totalPages }, (_, index) => (
              <button
                key={index}
                onClick={() => handlePageChange(index + 1)}
                className={`page-button ${
                  currentPage === index + 1 ? 'active-page' : ''
                }`}
              >
                {index + 1}
              </button>
            ))}
          </div>
        </>
      )}
    </div>
  );
};

export default PriceHistory;
