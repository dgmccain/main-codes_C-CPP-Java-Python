-- Use the test database
USE madrid_houses_test;

-- Insert test-level users with hashed passwords
INSERT INTO users (username, email, password_hash, role) VALUES
('testuser1', 'testuser1@example.com', '$2b$12$KhZ8zF1OV5XyFA9l8OTv8lIT7MwW.H3Tpt9M4a1Z45RV8HpfH52B6', 'user'),
('testuser2', 'testuser2@example.com', '$2b$12$hwK.Vw6gGmUBZya9b.k08L.DKAm59.EiXHBr9Tt07uJY2bxnZkqPa', 'user'),
('testadmin', 'testadmin@example.com', '$2b$12$TL6HbOIXmPjFOclox9DRkHfl5h0vf7l5.v5IUzr8UuCcdFLab6.qO', 'admin');

-- Insert test-level locations
INSERT INTO locations (country, state_or_province, city, address) VALUES
('Spain', 'Madrid', 'Madrid', 'Calle Sol 12'),
('Spain', 'Barcelona', 'Barcelona', 'Avenida de la Luz 15'),
('Spain', 'Seville', 'Seville', 'Calle de la Feria 100');

-- Insert test-level property data (changed)
INSERT INTO properties (user_id, location_id, square_meters, num_bedrooms, num_bathrooms, num_floors, buy_price, rent_price) VALUES
(1, 1, 50, 1, 1, 1, 150000, 800),  -- Property 1: Madrid, 50 m², 1 bedroom, 1 bathroom, 1 floor
(2, 2, 80, 2, 2, 2, 250000, 1200),  -- Property 2: Barcelona, 80 m², 2 bedrooms, 2 bathrooms, 2 floors
(1, 3, 120, 3, 3, 3, 350000, 1600);  -- Property 3: Seville, 120 m², 3 bedrooms, 3 bathrooms, 3 floors

-- Insert test-level predicted price history (changed)
INSERT INTO predicted_price_history (user_id, property_id, predicted_price, prediction_date) VALUES
(3, 1, 160000, '2025-01-01 08:00:00'),  -- Prediction for Property 1
(3, 2, 270000, '2025-01-02 09:30:00'),  -- Prediction for Property 2
(3, 3, 380000, '2025-01-03 11:00:00');  -- Prediction for Property 3

-- Insert test features (new seed)
INSERT INTO features (feature_name) VALUES
('Swimming Pool'),
('Garage'),
('Furnished'),
('Air Conditioning');

-- Insert test property features (new seed)
-- Property 1 (Madrid) has "Swimming Pool" and "Furnished"
INSERT INTO property_features (property_id, feature_id) VALUES
(1, 1),  -- Swimming Pool for Property 1
(1, 3);  -- Furnished for Property 1

-- Property 2 (Barcelona) has "Garage" and "Air Conditioning"
INSERT INTO property_features (property_id, feature_id) VALUES
(2, 2),  -- Garage for Property 2
(2, 4);  -- Air Conditioning for Property 2

-- Property 3 (Seville) has "Swimming Pool" and "Furnished"
INSERT INTO property_features (property_id, feature_id) VALUES
(3, 1),  -- Swimming Pool for Property 3
(3, 3);  -- Furnished for Property 3
