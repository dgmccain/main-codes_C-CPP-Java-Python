from pydantic import BaseModel
from typing import List, Optional
from datetime import datetime

# For login form validation
class LoginForm(BaseModel):
    email: str
    password: str

# For returning the JWT token
class Token(BaseModel):
    access_token: str
    token_type: str

# For user creation (optional for other use cases)
class UserCreate(BaseModel):
    username: str
    email: str
    password: str
    role: Optional[str] = None  # Optional role field

class UserBase(BaseModel):
    username: str
    email: str

class User(UserBase):
    user_id: int
    role: Optional[str] = None  # Optional role field

    class Config:
        orm_mode = True

# For returning the JWT token with user information
class TokenWithUser(BaseModel):
    access_token: str
    token_type: str
    user: User

# Same fields as LocationBase
class LocationCreate(BaseModel):
    country: str
    state_or_province: str
    city: str
    address: Optional[str] = None  # Optional address field

class LocationBase(BaseModel):
    country: str
    state_or_province: str
    city: str
    address: Optional[str] = None  # Optional address field

class Location(LocationBase):
    location_id: int

    class Config:
        orm_mode = True

class PropertyBase(BaseModel):
    square_meters: int
    num_bedrooms: int
    num_bathrooms: int
    num_floors: int
    buy_price: float
    rent_price: float

class PropertyCreate(PropertyBase):
    user_id: int
    location_id: int

class Property(PropertyBase):
    property_id: int
    user_id: int
    location_id: int
    created_at: datetime

    class Config:
        orm_mode = True

class Feature(BaseModel):
    feature_id: int
    feature_name: str

    class Config:
        orm_mode = True

class PropertyFeature(BaseModel):
    property_id: int
    feature_id: int

    class Config:
        orm_mode = True

class Prediction(BaseModel):
    prediction_id: int
    user_id: int
    square_meters: int
    num_bedrooms: int
    num_bathrooms: int
    num_floors: int
    predicted_price: float

class PredictedPriceHistory(BaseModel):
    prediction_id: int
    user_id: int
    property_id: int
    predicted_price: float
    prediction_date: datetime

    class Config:
        orm_mode = True
        
User.update_forward_refs()
Location.update_forward_refs()
