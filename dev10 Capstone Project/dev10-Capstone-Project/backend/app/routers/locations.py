from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from typing import List
from app import models, schemas
from app.database import get_db

router = APIRouter()

@router.get("/locations/", response_model=List[schemas.Location], status_code=200)
def get_locations(db: Session = Depends(get_db)):
    # Query all locations from the database
    locations = db.query(models.Location).all()

    # Return the locations list
    return locations

@router.get("/locations/{location_id}", response_model=schemas.Location, status_code=200)
def get_location(location_id: int, db: Session = Depends(get_db)):
    # Query the location by id
    location = db.query(models.Location).filter(models.Location.location_id == location_id).first()

    # Check if the location exists
    if not location:
        raise HTTPException(status_code=404, detail="Location not found")
    
    # Return the location
    return location

@router.post("/locations/", response_model=schemas.Location, status_code=201)
def create_location(location: schemas.LocationCreate, db: Session = Depends(get_db)):
    # Check if the location already exists (optional)
    existing_location = db.query(models.Location).filter(
        models.Location.country == location.country,
        models.Location.state_or_province == location.state_or_province,
        models.Location.city == location.city,
        models.Location.address == location.address,
    ).first()
    
    if existing_location:
        raise HTTPException(status_code=400, detail="Location already exists")
    
    # Create a new Location object
    db_location = models.Location(
        country=location.country,
        state_or_province=location.state_or_province,
        city=location.city,
        address=location.address
    )

    # Add the new location to the database session
    db.add(db_location)
    db.commit()
    db.refresh(db_location)
    
    return db_location
