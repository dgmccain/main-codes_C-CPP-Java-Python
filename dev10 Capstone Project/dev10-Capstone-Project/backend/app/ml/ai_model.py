import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

# Sample data
data = {
    'square_meters': [50, 60, 70, 80, 90, 100, 110, 120, 130, 140],
    'num_bedrooms': [1, 2, 2, 3, 3, 3, 4, 4, 4, 5],
    'num_bathrooms': [1, 1, 2, 2, 2, 3, 3, 3, 4, 4],
    'num_floors': [1, 1, 2, 2, 2, 3, 3, 3, 4, 4],
    'price': [200000, 250000, 300000, 350000, 400000, 450000, 500000, 550000, 600000, 650000]
}

# Convert to DataFrame
df = pd.DataFrame(data)

# Features and target variable
X = df[['square_meters', 'num_bedrooms', 'num_bathrooms', 'num_floors']]
y = df['price']

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create and train the model
model = LinearRegression()
model.fit(X_train, y_train)

# Make predictions
y_pred = model.predict(X_test)

# Evaluate the model
mse = mean_squared_error(y_test, y_pred)
print(f'Mean Squared Error: {mse}')

# Function to predict price based on input parameters
def predict_price(square_meters, num_bedrooms, num_bathrooms, num_floors):
    # TODO: Implement the ACTUAL AI_model ability to predict the price based on the input parameters
    input_data = np.array([[square_meters, num_bedrooms, num_bathrooms, num_floors]])
    predicted_price = model.predict(input_data)
    return predicted_price[0]
