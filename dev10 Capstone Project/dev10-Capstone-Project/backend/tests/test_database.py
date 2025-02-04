from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from app.database import get_db
from app.models import User, Location, Property, Feature, PredictedPriceHistory
from app.security import get_password_hash
import os

DB_USER = os.getenv('TEST_DB_USER')
DB_PASSWORD = os.getenv('TEST_DB_PASSWORD')
DB_HOST = os.getenv('TEST_DB_HOST')
DB_NAME = os.getenv('TEST_DB_NAME')

SQLALCHEMY_DATABASE_URL = f"mysql+pymysql://{DB_USER}:{DB_PASSWORD}@{DB_HOST}/{DB_NAME}"

engine = create_engine(SQLALCHEMY_DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# Example test for creating a user
def test_create_user():
    db = next(get_db())
    user = User(
        username="testuser",
        email="testuser@example.com",
        password_hash=get_password_hash("password123"),
        role="user"
    )
    db.add(user)
    db.commit()
    
    db_user = db.query(User).filter(User.email == "testuser@example.com").first()
    assert db_user is not None
    assert db_user.username == "testuser"

# Example test for deleting a user
def test_delete_user():
    db = next(get_db())
    
    # Ensure the user exists before deletion
    db_user = db.query(User).filter(User.email == "testuser@example.com").first()
    assert db_user is not None
    
    # Delete the user
    db.delete(db_user)
    db.commit()
    
    # Ensure the user is deleted
    db_user = db.query(User).filter(User.email == "testuser@example.com").first()
    assert db_user is None

# Example test for creating a location
def test_create_location():
    db = next(get_db())
    location = Location(
        country="CountryExample",
        state_or_province="StateOrProvinceExample",
        city="CityExample",
        address="AddressExample at Street 123"
    )
    db.add(location)
    db.commit()

    db_location = db.query(Location).filter(Location.address == "AddressExample at Street 123").first()
    assert db_location is not None
    assert db_location.country == "CountryExample"

# Example test for deleting a location
def test_delete_location():
    db = next(get_db())
    
    # Ensure the location exists before deletion
    db_location = db.query(Location).filter(Location.address == "AddressExample at Street 123").first()
    assert db_location is not None
    
    # Delete the location
    db.delete(db_location)
    db.commit()
    
    # Ensure the location is deleted
    db_location = db.query(Location).filter(Location.address == "AddressExample at Street 123").first()
    assert db_location is None

# Example test for creating a property
def test_create_property():
    db = next(get_db())
    property = Property(
        user_id=1,
        location_id=1,
        square_meters=2000,
        num_bedrooms=3,
        num_bathrooms=2,
        num_floors=2,
        created_at="2024-01-09 00:00:00"
    )
    db.add(property)
    db.commit()

    db_property = db.query(Property).filter(Property.square_meters == 2000).first()
    assert db_property is not None
    assert db_property.num_bedrooms == 3

# Example test for deleting a property
def test_delete_property():
    db = next(get_db())
    
    # Ensure the property exists before deletion
    db_property = db.query(Property).filter(Property.square_meters == 2000).first()
    assert db_property is not None
    
    # Delete the property
    db.delete(db_property)
    db.commit()
    
    # Ensure the property is deleted
    db_property = db.query(Property).filter(Property.square_meters == 2000).first()
    assert db_property is None

# Example test for creating a feature
def test_create_feature():
    db = next(get_db())
    feature = Feature(
        feature_name="Tennis Court"
    )
    db.add(feature)
    db.commit()
    
    db_feature = db.query(Feature).filter(Feature.feature_name == "Tennis Court").first()
    assert db_feature is not None
    assert db_feature.feature_name == "Tennis Court"

# Example test for deleting a feature
def test_delete_feature():
    db = next(get_db())
    
    # Ensure the feature exists before deletion
    db_feature = db.query(Feature).filter(Feature.feature_name == "Tennis Court").first()
    assert db_feature is not None
    
    # Delete the feature
    db.delete(db_feature)
    db.commit()
    
    # Ensure the feature is deleted
    db_feature = db.query(Feature).filter(Feature.feature_name == "Tennis Court").first()
    assert db_feature is None

# Example test for creating a predicted_price_history
def test_create_predicted_price_history():
    db = next(get_db())
    predicted_price_history = PredictedPriceHistory(
        user_id=1,
        property_id=1,
        predicted_price=500000.0,
        prediction_date="2024-01-09 00:00:00"
    )
    db.add(predicted_price_history)
    db.commit()
    
    db_predicted_price_history = db.query(PredictedPriceHistory).filter(PredictedPriceHistory.predicted_price == 500000.0).first()
    assert db_predicted_price_history is not None
    assert db_predicted_price_history.predicted_price == 500000.0

# Example test for deleting a predicted_price_history
def test_delete_predicted_price_history():
    db = next(get_db())
    
    # Ensure the predicted_price_history exists before deletion
    db_predicted_price_history = db.query(PredictedPriceHistory).filter(PredictedPriceHistory.predicted_price == 500000.0).first()
    assert db_predicted_price_history is not None
    
    # Delete the predicted_price_history
    db.delete(db_predicted_price_history)
    db.commit()
    
    # Ensure the predicted_price_history is deleted
    db_predicted_price_history = db.query(PredictedPriceHistory).filter(PredictedPriceHistory.predicted_price == 500000.0).first()
    assert db_predicted_price_history is None
