const API_URL = 'http://localhost:8000/api';

export const getLocations = async () => {
  try {
    const response = await fetch(`${API_URL}/locations`, {
      method: 'GET',
    });

    if (!response.ok) {
      throw new Error('Failed to fetch locations');
    }

    const data = await response.json();
    return data; // List of locations
  } catch (error) {
    console.error(error);
    throw new Error('Error fetching locations');
  }
};

export const getLocationById = async (locationId, token) => {
  try {
    const response = await fetch(`${API_URL}/locations/${locationId}`, {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`,
      },
    });
    if (!response.ok) {
      throw new Error('Failed to fetch location data');
    }
    const data = await response.json();
    return data; // Location details
  } catch (error) {
    throw new Error(error.message);
  }
};

export const createLocation = async (locationData) => {
  try {
    const response = await fetch(`${API_URL}/locations/`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${token}`,
      },
      body: JSON.stringify(locationData),
    });

    if (!response.ok) {
      throw new Error('Failed to add new location');
    }

    const data = await response.json();
    return data; // Newly added location details
  } catch (error) {
    console.error(error);
    throw new Error('Error adding new location');
  }
};

export const updateLocation = async (locationId, locationData) => {
  try {
    const response = await fetch(`${API_URL}/locations/${locationId}`, {
      method: 'PUT',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(locationData),
    });

    if (!response.ok) {
      throw new Error(`Failed to update location with ID: ${locationId}`);
    }

    const data = await response.json();
    return data; // Updated location details
  } catch (error) {
    console.error(error);
    throw new Error('Error updating location');
  }
};

export const deleteLocation = async (locationId) => {
  try {
    const response = await fetch(`${API_URL}/locations/${locationId}`, {
      method: 'DELETE',
    });

    if (!response.ok) {
      throw new Error(`Failed to delete location with ID: ${locationId}`);
    }

    const data = await response.json();
    return data; // Deleted location details
  } catch (error) {
    console.error(error);
    throw new Error('Error deleting location');
  }
};
