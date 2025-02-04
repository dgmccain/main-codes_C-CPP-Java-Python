const API_URL = 'http://localhost:8000/api'; // Backend server URL

// Function to fetch all properties
export async function getAllProperties() {
  try {
    const response = await fetch(`${API_URL}/properties/`, {
      method: 'GET',
    });

    if (!response.ok) {
      throw new Error('Failed to fetch properties');
    }

    const data = await response.json();
    return data; // List of properties
  } catch (error) {
    console.error(error);
    throw new Error('Error fetching properties');
  }
}

// Function to fetch a single property by ID
export async function getPropertyById(propertyId) {
  try {
    const response = await fetch(`${API_URL}/properties/${propertyId}`, {
      method: 'GET',
    });

    if (!response.ok) {
      throw new Error(`Failed to fetch property with ID: ${propertyId}`);
    }

    const data = await response.json();
    return data; // Property details
  } catch (error) {
    console.error(error);
    throw new Error('Error fetching property by ID');
  }
}

// Function to add a new property
export async function addNewProperty(propertyData) {
  try {
    const response = await fetch(`${API_URL}/properties/`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(propertyData),
    });

    if (!response.ok) {
      throw new Error('Failed to add new property');
    }

    const data = await response.json();
    return data; // Newly added property details
  } catch (error) {
    console.error(error);
    throw new Error('Error adding new property');
  }
}

// Function to delete a property by ID (if applicable)
export async function deleteProperty(propertyId) {
  try {
    const response = await fetch(`${API_URL}/properties/${propertyId}`, {
      method: 'DELETE',
    });

    if (!response.ok) {
      throw new Error(`Failed to delete property with ID: ${propertyId}`);
    }

    return { message: 'Property deleted successfully' };
  } catch (error) {
    console.error(error);
    throw new Error('Error deleting property');
  }
}
