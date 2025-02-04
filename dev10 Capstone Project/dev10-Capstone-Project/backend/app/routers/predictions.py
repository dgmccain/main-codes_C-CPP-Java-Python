from fastapi import APIRouter
from app import schemas

router = APIRouter()

@router.post("/save-price-prediction/", response_model=schemas.Prediction)
def save_price_prediction(prediction: schemas.Prediction):
    # TODO: Save the prediction to the database
    # NOTE: issue currently is that the prediction does not have a property_id and I do not want
    # to add it to the properties table. I may have to add property_id and prediction_date to schema
    # because they are required for the PredictedPriceHistory schema
    return prediction
