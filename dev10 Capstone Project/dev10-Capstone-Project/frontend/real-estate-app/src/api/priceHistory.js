const API_URL = 'http://localhost:8000/api';

// Function to get price prediction history
export async function getPriceHistory(userId, token) {
  try {
    const response = await fetch(
      `${API_URL}/predict-price-history/${userId}/`,
      {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
          Authorization: `Bearer ${token}`,
        },
      }
    );

    if (response.status === 204) {
      return [];
    }

    if (!response.ok) {
      throw new Error('Failed to fetch price prediction history');
    }

    return await response.json();
  } catch (error) {
    console.error('Error fetching price prediction history:', error);
    throw error;
  }
}

// Function to save a price prediction entry
export async function savePricePrediction(predictionData, token) {
  try {
    const response = await fetch(`${API_URL}/save-price-prediction`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`,
      },
      body: JSON.stringify(predictionData),
    });

    if (!response.ok) {
      throw new Error('Failed to save price prediction');
    }

    return await response.json();
  } catch (error) {
    console.error('Error saving price prediction:', error);
    throw error;
  }
}
