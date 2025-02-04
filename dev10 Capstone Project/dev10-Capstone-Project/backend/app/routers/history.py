from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from typing import List
from .. import models, schemas, security
from ..database import get_db

router = APIRouter()

@router.get("/predict-price-history/{user_id}/", response_model=List[schemas.PredictedPriceHistory])
def get_price_prediction_history(user_id: int, db: Session = Depends(get_db), current_user: models.User = Depends(security.get_current_user)):
    if user_id != current_user.user_id:
        raise HTTPException(status_code=403, detail="Not authorized to access this user's history")
    history = db.query(models.PredictedPriceHistory).filter(models.PredictedPriceHistory.user_id == user_id).all()
    if not history:
        raise HTTPException(status_code=204, detail="No history found for the user")
    return history
