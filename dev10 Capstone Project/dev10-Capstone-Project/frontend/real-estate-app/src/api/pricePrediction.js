const API_URL = 'http://localhost:8000/api';

export async function predictPrice(data, token) {
  // TODO: Implement predictPrice function currectly, passing in the data and token
  // TODO: implement the fetch call to the backend
  // try {
  //   const response = await fetch(`${API_URL}/predict`, {
  //     method: 'GET',
  //   });

  //   if (!response.ok) {
  //     throw new Error('Failed to predict price');
  //   }

  //   const data = await response.json();
  //   return data; // Predicted price
  // } catch (error) {
  //   console.error(error);
  //   throw new Error('Error predicting price');
  // }

  // Algorithm approach...

  // Example coefficients (can be adjusted based on your dataset or AI model)
  const basePrice = 300000; // Base price for any property
  const coeffSquareMeters = 4813; // Price per square meter
  const coeffBedrooms = 22393; // Additional price per bedroom
  const coeffBathrooms = 15372; // Additional price per bathroom
  const coeffFloors = 12431; // Additional price per floor

  // Extract input data
  const { sq_mt_built, n_rooms, n_bathrooms, n_floors } = data;

  // Calculate the predicted price using a simple linear regression formula
  const predictedPrice =
    basePrice +
    coeffSquareMeters * 1.01 * sq_mt_built +
    coeffBedrooms * 0.99 * n_rooms +
    coeffBathrooms * 0.99 * n_bathrooms +
    coeffFloors * 0.99 * n_floors;

  // Format the predicted price to currency
  const formattedPrice = predictedPrice.toLocaleString('en-US', {
    style: 'currency',
    currency: 'USD',
  });

  // Add the predicted price to the data object
  data.predicted_price = formattedPrice;

  return data;
}
