from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from typing import List
from app import models, schemas
from app.database import get_db

router = APIRouter()

@router.get("/properties/", response_model=List[schemas.Property], status_code=200)
def get_properties(db: Session = Depends(get_db)):
    # Query all properties from the database
    properties = db.query(models.Property).all()

    if not properties:
        raise HTTPException(status_code=404, detail="No properties found")
    
    # Return the properties list
    return properties

@router.get("/properties/{property_id}", response_model=schemas.Property, status_code=200)
def get_property(property_id: int, db: Session = Depends(get_db)):
    #Query the property by the provided property_id
    property = db.query(models.Property).filter(models.Property.property_id == property_id).first()

    if not property:
        raise HTTPException(status_code=404, detail="Property not found")

    return property

@router.post("/properties/", response_model=schemas.Property, status_code=201)
def create_property(property: schemas.PropertyCreate, db: Session = Depends(get_db)):
    # Check if the location exists
    db_location = db.query(models.Location).filter(models.Location.location_id == property.location_id).first()
    if not db_location:
        raise HTTPException(status_code=404, detail="Location not found")

    # Check if the user exists
    db_user = db.query(models.User).filter(models.User.user_id == property.user_id).first()
    if not db_user:
        raise HTTPException(status_code=404, detail="User not found")

    # Create the property record, including num_bathrooms and num_floors
    db_property = models.Property(
        user_id=property.user_id,
        location_id=property.location_id,
        square_meters=property.square_meters,
        num_bedrooms=property.num_bedrooms,
        num_bathrooms=property.num_bathrooms,
        num_floors=property.num_floors,
        buy_price=property.buy_price,          # Ensure the buy_price is provided
        rent_price=property.rent_price,        # Ensure the rent_price is provided
    )

    db.add(db_property)
    db.commit()
    db.refresh(db_property)

    # Return the created property
    return db_property
