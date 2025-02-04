from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from app.database import init_db
from app.routers import auth_users, locations, properties, predictions, history

app = FastAPI()

# Allow requests from the frontend URL (http://localhost:5173 in this case)
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5173"],  # Specify your frontend URL here
    allow_credentials=True,
    allow_methods=["*"],  # Allow all HTTP methods (GET, POST, etc.)
    allow_headers=["*"],  # Allow all headers
)

# Initialize the database
init_db()

# Include routers for different endpoints
app.include_router(auth_users.router, prefix="/api")
app.include_router(locations.router, prefix="/api")
app.include_router(properties.router, prefix="/api")
app.include_router(predictions.router, prefix="/api")
app.include_router(history.router, prefix="/api")
