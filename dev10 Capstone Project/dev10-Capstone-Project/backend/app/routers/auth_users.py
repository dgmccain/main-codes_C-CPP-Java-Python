from fastapi import APIRouter, HTTPException, Depends
from sqlalchemy.orm import Session
from app import models, schemas
from app.database import get_db
from app.security import get_password_hash, verify_password, create_access_token
from datetime import timedelta

router = APIRouter()

@router.post("/register/", response_model=schemas.TokenWithUser, status_code=201)
def register_user(user: schemas.UserCreate, db: Session = Depends(get_db)):
    if db.query(models.User).filter(models.User.username == user.username).first():
        raise HTTPException(status_code=400, detail="Username already registered")

    if db.query(models.User).filter(models.User.email == user.email).first():
        raise HTTPException(status_code=400, detail="Email already registered")

    try:
        hashed_password = get_password_hash(user.password)
        new_user = models.User(
            username=user.username,
            email=user.email,
            password_hash=hashed_password,
            role="user"
        )
        db.add(new_user)
        db.commit()
        db.refresh(new_user)

        access_token = create_access_token(
            data={"sub": new_user.email, "user_id": new_user.user_id},
            expires_delta=timedelta(hours=1)
        )
        
        return {"access_token": access_token, "token_type": "bearer", "user": new_user}
    except Exception as e:
        print("Error during user registration:", str(e))
        db.rollback()
        raise HTTPException(status_code=500, detail="Internal Server Error")

@router.post("/login/", response_model=schemas.TokenWithUser, status_code=200)
def login_user(login_form: schemas.LoginForm, db: Session = Depends(get_db)):
    user = db.query(models.User).filter(models.User.email == login_form.email).first()
    if user is None or not verify_password(login_form.password, user.password_hash):
        raise HTTPException(status_code=401, detail="Invalid credentials")

    access_token = create_access_token(
        data={"sub": user.email, "user_id": user.user_id},
        expires_delta=timedelta(hours=1)
    )
    return {"access_token": access_token, "token_type": "bearer", "user": user}
