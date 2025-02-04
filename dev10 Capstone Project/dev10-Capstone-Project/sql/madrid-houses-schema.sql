drop database if exists madrid_houses;
create database madrid_houses;
use madrid_houses;

CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(255) UNIQUE NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    role VARCHAR(255) NOT NULL
);

CREATE TABLE locations (
    location_id INT PRIMARY KEY AUTO_INCREMENT,
    country VARCHAR(255) NOT NULL,
    state_or_province VARCHAR(255),
    city VARCHAR(255) NOT NULL,
    address VARCHAR(255)
);

CREATE TABLE features (
    feature_id INT PRIMARY KEY AUTO_INCREMENT,
    feature_name VARCHAR(255) UNIQUE NOT NULL
);

CREATE TABLE properties (
    property_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    location_id INT NOT NULL,
    square_meters INT NOT NULL,
    num_bedrooms INT NOT NULL,
    num_bathrooms INT NOT NULL,
    num_floors INT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    buy_price FLOAT,
    rent_price FLOAT,
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (location_id) REFERENCES locations(location_id)
);

CREATE TABLE property_features (
    property_id INT NOT NULL,
    feature_id INT NOT NULL,
    PRIMARY KEY (property_id, feature_id),
    FOREIGN KEY (property_id) REFERENCES properties(property_id),
    FOREIGN KEY (feature_id) REFERENCES features(feature_id)
);

CREATE TABLE predicted_price_history (
    prediction_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    property_id INT NOT NULL,
    predicted_price FLOAT NOT NULL,
    prediction_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (property_id) REFERENCES properties(property_id)
);
