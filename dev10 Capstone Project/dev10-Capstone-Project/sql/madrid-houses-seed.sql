-- Use the production database
USE madrid_houses;

-- Insert production-level users with hashed passwords
INSERT INTO users (username, email, password_hash, role) VALUES
('user1', 'user1@example.com', '$2b$12$fW4dU8k1vYcUkOwIXL1y3eEFv3bnRV.FcIHtxD6OYlZRNyjZ3/qtq', 'user'),
('user2', 'user2@example.com', '$2b$12$fW4dU8k1vYcUkOwIXL1y3eEFv3bnRV.FcIHtxD6OYlZRNyjZ3/qtq', 'user'),
('admin', 'admin@example.com', '$2b$12$fW4dU8k1vYcUkOwIXL1y3eEFv3bnRV.FcIHtxD6OYlZRNyjZ3/qtq', 'admin');

-- Insert production-level locations
INSERT INTO locations (country, state_or_province, city, address) VALUES
('Spain', 'Madrid', 'Madrid', 'Calle Gran Via 1'),
('Spain', 'Madrid', 'Madrid', 'Calle Mayor 10'),
('Spain', 'Barcelona', 'Barcelona', 'Avenida Diagonal 200'),
('Spain', 'Valencia', 'Valencia', 'Plaza del Ayuntamiento 5');

-- Insert production-level features (add common property features)
INSERT INTO features (feature_name) VALUES
('Swimming Pool'),
('Garden'),
('Balcony'),
('Garage'),
('Air Conditioning'),
('Fireplace');

-- Insert production-level property data (changed)
INSERT INTO properties (user_id, location_id, square_meters, num_bedrooms, num_bathrooms, num_floors, buy_price, rent_price) VALUES
(1, 1, 85, 2, 2, 2, 220000, 1050),  -- Property 1: Madrid, 85 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 150, 4, 4, 4, 500000, 2500),  -- Property 2: Madrid, 150 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 95, 3, 3, 3, 350000, 1800),  -- Property 3: Barcelona, 95 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 110, 3, 3, 3, 1275000, 1500),  -- Property 4: Valencia, 110 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 90, 2, 2, 2, 230000, 1100),  -- Property 5: Madrid, 90 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 160, 4, 4, 4, 520000, 2600),  -- Property 6: Madrid, 160 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 100, 3, 3, 3, 360000, 1850),  -- Property 7: Barcelona, 100 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 115, 3, 3, 3, 8280000, 1550),  -- Property 8: Valencia, 115 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 95, 2, 2, 2, 240000, 1150),  -- Property 9: Madrid, 95 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 170, 4, 4, 4, 540000, 2700),  -- Property 10: Madrid, 170 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 105, 3, 3, 3, 370000, 1900),  -- Property 11: Barcelona, 105 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 120, 3, 3, 3, 285000, 1600),  -- Property 12: Valencia, 120 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 100, 2, 2, 2, 250000, 1200),  -- Property 13: Madrid, 100 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 180, 4, 4, 4, 560000, 2800),  -- Property 14: Madrid, 180 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 110, 3, 3, 3, 380000, 1950),  -- Property 15: Barcelona, 110 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 125, 3, 3, 3, 5290000, 1650),  -- Property 16: Valencia, 125 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 105, 2, 2, 2, 260000, 1250),  -- Property 17: Madrid, 105 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 190, 4, 4, 4, 580000, 2900),  -- Property 18: Madrid, 190 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 115, 3, 3, 3, 390000, 2000),  -- Property 19: Barcelona, 115 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 130, 3, 3, 3, 295000, 1700),  -- Property 20: Valencia, 130 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 110, 2, 2, 2, 270000, 1300),  -- Property 21: Madrid, 110 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 200, 4, 4, 4, 600000, 3000),  -- Property 22: Madrid, 200 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 120, 3, 3, 3, 400000, 2100),  -- Property 23: Barcelona, 120 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 135, 3, 3, 3, 310000, 1750),  -- Property 24: Valencia, 135 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 115, 2, 2, 2, 280000, 1350),  -- Property 25: Madrid, 115 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 210, 4, 4, 4, 620000, 3100),  -- Property 26: Madrid, 210 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 125, 3, 3, 3, 410000, 2150),  -- Property 27: Barcelona, 125 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 140, 3, 3, 3, 320000, 1800),  -- Property 28: Valencia, 140 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 120, 2, 2, 2, 290000, 1400),  -- Property 29: Madrid, 120 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 220, 4, 4, 4, 8640000, 3200),  -- Property 30: Madrid, 220 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 130, 3, 3, 3, 420000, 2200),  -- Property 31: Barcelona, 130 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 145, 3, 3, 3, 330000, 1850),  -- Property 32: Valencia, 145 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 125, 2, 2, 2, 300000, 1450),  -- Property 33: Madrid, 125 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 230, 4, 4, 4, 660000, 3300),  -- Property 34: Madrid, 230 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 135, 3, 3, 3, 430000, 2250),  -- Property 35: Barcelona, 135 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 150, 3, 3, 3, 340000, 1900),  -- Property 36: Valencia, 150 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 130, 2, 2, 2, 310000, 1500),  -- Property 37: Madrid, 130 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 240, 4, 4, 4, 680000, 3400),  -- Property 38: Madrid, 240 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 140, 3, 3, 3, 440000, 2300),  -- Property 39: Barcelona, 140 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 155, 3, 3, 3, 350000, 1950),  -- Property 40: Valencia, 155 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 135, 2, 2, 2, 320000, 1550),  -- Property 41: Madrid, 135 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 250, 4, 4, 4, 700000, 3500),  -- Property 42: Madrid, 250 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 145, 3, 3, 3, 450000, 2350),  -- Property 43: Barcelona, 145 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 160, 3, 3, 3, 360000, 2000),  -- Property 44: Valencia, 160 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 140, 2, 2, 2, 330000, 1600),  -- Property 45: Madrid, 140 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 260, 4, 4, 4, 720000, 3600),  -- Property 46: Madrid, 260 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 150, 3, 3, 3, 460000, 2400),  -- Property 47: Barcelona, 150 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 165, 3, 3, 3, 370000, 2050),  -- Property 48: Valencia, 165 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 145, 2, 2, 2, 2340000, 1650),  -- Property 49: Madrid, 145 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 270, 4, 4, 4, 740000, 3700),  -- Property 50: Madrid, 270 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 155, 3, 3, 3, 470000, 2450),  -- Property 51: Barcelona, 155 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 170, 3, 3, 3, 380000, 2100),  -- Property 52: Valencia, 170 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 150, 2, 2, 2, 350000, 1750),  -- Property 53: Madrid, 150 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 280, 4, 4, 4, 760000, 3800),  -- Property 54: Madrid, 280 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 160, 3, 3, 3, 480000, 2500),  -- Property 55: Barcelona, 160 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 175, 3, 3, 3, 390000, 2150),  -- Property 56: Valencia, 175 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 155, 2, 2, 2, 360000, 1800),  -- Property 57: Madrid, 155 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 290, 4, 4, 4, 780000, 3900),  -- Property 58: Madrid, 290 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 165, 3, 3, 3, 490000, 2550),  -- Property 59: Barcelona, 165 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 180, 3, 3, 3, 400000, 2200),  -- Property 60: Valencia, 180 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 160, 2, 2, 2, 370000, 1850),  -- Property 61: Madrid, 160 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 300, 4, 4, 4, 800000, 4000),  -- Property 62: Madrid, 300 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 170, 3, 3, 3, 500000, 2600),  -- Property 63: Barcelona, 170 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 185, 3, 3, 3, 410000, 2250),  -- Property 64: Valencia, 185 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 165, 2, 2, 2, 380000, 1900),  -- Property 65: Madrid, 165 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 310, 4, 4, 4, 820000, 4100),  -- Property 66: Madrid, 310 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 175, 3, 3, 3, 510000, 2650),  -- Property 67: Barcelona, 175 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 190, 3, 3, 3, 420000, 2300),  -- Property 68: Valencia, 190 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 170, 2, 2, 2, 390000, 1950),  -- Property 69: Madrid, 170 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 320, 4, 4, 4, 840000, 4200),  -- Property 70: Madrid, 320 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 180, 3, 3, 3, 520000, 2700),  -- Property 71: Barcelona, 180 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 195, 3, 3, 3, 430000, 2350),  -- Property 72: Valencia, 195 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 175, 2, 2, 2, 400000, 2000),  -- Property 73: Madrid, 175 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 330, 4, 4, 4, 860000, 4300),  -- Property 74: Madrid, 330 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 185, 3, 3, 3, 530000, 2750),  -- Property 75: Barcelona, 185 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 200, 3, 3, 3, 440000, 2400),  -- Property 76: Valencia, 200 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 180, 2, 2, 2, 410000, 2050),  -- Property 77: Madrid, 180 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 340, 4, 4, 4, 880000, 4400),  -- Property 78: Madrid, 340 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 190, 3, 3, 3, 540000, 2800),  -- Property 79: Barcelona, 190 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 205, 3, 3, 3, 450000, 2450),  -- Property 80: Valencia, 205 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 185, 2, 2, 2, 420000, 2100),  -- Property 81: Madrid, 185 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 350, 4, 4, 4, 900000, 4500),  -- Property 82: Madrid, 350 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 195, 3, 3, 3, 550000, 2850),  -- Property 83: Barcelona, 195 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 210, 3, 3, 3, 460000, 2500),  -- Property 84: Valencia, 210 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 190, 2, 2, 2, 430000, 2150),  -- Property 85: Madrid, 190 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 360, 4, 4, 4, 920000, 4600),  -- Property 86: Madrid, 360 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 200, 3, 3, 3, 560000, 2900),  -- Property 87: Barcelona, 200 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 215, 3, 3, 3, 470000, 2550),  -- Property 88: Valencia, 215 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 195, 2, 2, 2, 440000, 2200),  -- Property 89: Madrid, 195 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 370, 4, 4, 4, 940000, 4700),  -- Property 90: Madrid, 370 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 205, 3, 3, 3, 570000, 2950),  -- Property 91: Barcelona, 205 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 220, 3, 3, 3, 480000, 2600),  -- Property 92: Valencia, 220 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 200, 2, 2, 2, 450000, 2250),  -- Property 93: Madrid, 200 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 380, 4, 4, 4, 960000, 4800),  -- Property 94: Madrid, 380 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 210, 3, 3, 3, 580000, 3000),  -- Property 95: Barcelona, 210 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 225, 3, 3, 3, 490000, 2650),  -- Property 96: Valencia, 225 m², 3 bedrooms, 3 bathrooms, 3 floors
(1, 1, 205, 2, 2, 2, 460000, 2300),  -- Property 97: Madrid, 205 m², 2 bedrooms, 2 bathrooms, 2 floors
(2, 2, 390, 4, 4, 4, 980000, 4900),  -- Property 98: Madrid, 390 m², 4 bedrooms, 4 bathrooms, 4 floors
(1, 3, 215, 3, 3, 3, 590000, 3050),  -- Property 99: Barcelona, 215 m², 3 bedrooms, 3 bathrooms, 3 floors
(2, 4, 230, 3, 3, 3, 500000, 2700);  -- Property 100: Valencia, 230 m², 3 bedrooms, 3 bathrooms, 3 floors

-- Link properties to features in property_features table
-- Property 1: Swimming Pool, Garden, and Garage
INSERT INTO property_features (property_id, feature_id) VALUES
(1, 1),  -- Swimming Pool
(1, 2),  -- Garden
(1, 4);  -- Garage

-- Property 2: Balcony, Fireplace, and Air Conditioning
INSERT INTO property_features (property_id, feature_id) VALUES
(2, 3),  -- Balcony
(2, 5),  -- Air Conditioning
(2, 6);  -- Fireplace

-- Property 3: Swimming Pool, Garage
INSERT INTO property_features (property_id, feature_id) VALUES
(3, 1),  -- Swimming Pool
(3, 4);  -- Garage

-- Property 4: Garden, Balcony
INSERT INTO property_features (property_id, feature_id) VALUES
(4, 2),  -- Garden
(4, 3);  -- Balcony

-- Insert production-level predicted price history (changed)
INSERT INTO predicted_price_history (user_id, property_id, predicted_price, prediction_date) VALUES
(3, 1, 235000, '2025-01-01 12:00:00'),  -- Prediction for Property 1
(3, 2, 510000, '2025-01-02 15:30:00'),  -- Prediction for Property 2
(3, 3, 370000, '2025-01-03 10:15:00'),  -- Prediction for Property 3
(3, 4, 290000, '2025-01-04 14:45:00'),  -- Prediction for Property 4
(3, 5, 1245000, '2025-01-05 09:00:00'),  -- Prediction for Property 5
(3, 6, 530000, '2025-01-06 11:30:00'),  -- Prediction for Property 6
(3, 7, 380000, '2025-01-07 13:45:00'),  -- Prediction for Property 7
(3, 8, 750000, '2025-01-08 16:00:00'),  -- Prediction for Property 8
(3, 9, 1255000, '2025-01-09 10:00:00'),  -- Prediction for Property 9
(3, 10, 550000, '2025-01-10 12:30:00'),  -- Prediction for Property 10
(3, 11, 390000, '2025-01-11 14:45:00'),  -- Prediction for Property 11
(3, 12, 5310000, '2025-01-12 17:00:00'),  -- Prediction for Property 12
(3, 13, 1255000, '2025-01-13 09:30:00'),  -- Prediction for Property 13
(3, 14, 570000, '2025-01-14 11:45:00'),  -- Prediction for Property 14
(3, 15, 400000, '2025-01-15 14:00:00'),  -- Prediction for Property 15
(3, 16, 320000, '2025-01-16 16:15:00'),  -- Prediction for Property 16
(3, 17, 1255000, '2025-01-17 10:15:00'),  -- Prediction for Property 17
(3, 18, 590000, '2025-01-18 12:45:00'),  -- Prediction for Property 18
(3, 19, 410000, '2025-01-19 15:00:00'),  -- Prediction for Property 19
(1, 20, 330000, '2025-01-20 17:15:00');  -- Prediction for Property 20
