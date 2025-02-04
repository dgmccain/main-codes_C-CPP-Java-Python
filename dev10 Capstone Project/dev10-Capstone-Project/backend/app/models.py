from sqlalchemy import Column, Integer, String, Float, ForeignKey, DateTime
from sqlalchemy.orm import relationship
from sqlalchemy.sql import func
from app.database import Base

class User(Base):
    __tablename__ = "users"

    user_id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    username = Column(String, unique=True, nullable=False, index=True)
    email = Column(String, unique=True, nullable=False, index=True)
    password_hash = Column(String, nullable=False, index=True)
    role = Column(String, nullable=True) # Role can be null

    properties = relationship("Property", back_populates="owner")

class Location(Base):
    __tablename__ = "locations"

    location_id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    country = Column(String, nullable=False, index=True)
    state_or_province = Column(String, nullable=True, index=True) # State can be null
    city = Column(String, nullable=False, index=True)
    address = Column(String, nullable=True, index=True) # Address can be null

    properties = relationship("Property", back_populates="location")

class Property(Base):
    __tablename__ = "properties"

    property_id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    user_id = Column(Integer, ForeignKey("users.user_id"), nullable=False, index=True)
    location_id = Column(Integer, ForeignKey("locations.location_id"), nullable=False, index=True)
    square_meters = Column(Integer, nullable=False)
    num_bedrooms = Column(Integer, nullable=False)
    num_bathrooms = Column(Integer, nullable=False)
    num_floors = Column(Integer, nullable=False)
    buy_price = Column(Float, nullable=True) # Buy price can be null
    rent_price = Column(Float, nullable=True) # Rent price can be null
    created_at = Column(DateTime, default=func.now())

    owner = relationship("User", back_populates="properties")
    location = relationship("Location", back_populates="properties")

class Feature(Base):
    __tablename__ = "features"

    feature_id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    feature_name = Column(String, unique=True, nullable=False, index=True)

class PropertyFeature(Base):
    __tablename__ = "property_features"

    property_id = Column(Integer, ForeignKey("properties.property_id"), primary_key=True)
    feature_id = Column(Integer, ForeignKey("features.feature_id"), primary_key=True)

class PredictedPriceHistory(Base):
    __tablename__ = "predicted_price_history"

    prediction_id = Column(Integer, primary_key=True, autoincrement=True, index=True)
    user_id = Column(Integer, ForeignKey("users.user_id"), nullable=False, index=True)
    property_id = Column(Integer, ForeignKey("properties.property_id"), nullable=False, index=True)
    predicted_price = Column(Float, nullable=False)
    prediction_date = Column(DateTime, default=func.now())
