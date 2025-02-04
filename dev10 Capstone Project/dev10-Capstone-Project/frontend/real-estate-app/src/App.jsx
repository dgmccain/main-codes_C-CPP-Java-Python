import React, { useState } from 'react';
import { Route, Routes, useNavigate } from 'react-router-dom'; // Import useNavigate
import Navbar from './components/NavBar';
import Footer from './components/Footer';
import Home from './pages/Home';
import PropertiesList from './pages/PropertiesList';
import PricePrediction from './pages/PricePrediction';
import About from './pages/About';
import Contact from './pages/Contact';
import Login from './pages/Login';
import PriceHistory from './pages/PriceHistory';

const App = () => {
  const [isLoggedIn, setIsLoggedIn] = useState(false); // Track user login state
  const [token, setToken] = useState(''); // Track access token
  const [username, setUsername] = useState(''); // Track username
  const [userId, setUserId] = useState(''); // Track user ID
  const navigate = useNavigate(); // Get the navigate function from useNavigate

  const loginHandler = (user, token) => {
    if (!user || !user.username || !user.user_id) {
      console.error('Login - Invalid user object:', user);
      return;
    }

    setIsLoggedIn(true);
    setUsername(user.username); // Update username state
    setUserId(user.user_id); // Update user ID state
    setToken(token); // Update access token state
    navigate('/'); // Redirect to home page after login
  };

  const logoutHandler = () => {
    setIsLoggedIn(false); // Set login state to false after logout
    setUsername(''); // Clear username
    setUserId(''); // Clear user ID
    setToken(''); // Clear token
    navigate('/login'); // Redirect to login page after logout
  };

  return (
    <>
      <Navbar
        isLoggedIn={isLoggedIn}
        username={username} // Pass the username to Navbar
        userId={userId} // Pass the user ID to Navbar
        logoutHandler={logoutHandler}
      />
      <div className='main-content'>
        <Routes>
          <Route path='/' element={<Home />} />
          <Route
            path='/login'
            element={<Login loginHandler={loginHandler} />}
          />
          <Route path='/properties' element={<PropertiesList />} />
          <Route
            path='/predict-price'
            element={<PricePrediction userId={userId} token={token} />}
          />
          {isLoggedIn && (
            <Route
              path='/predict-price-history'
              element={<PriceHistory userId={userId} token={token} />}
            />
          )}
          <Route path='/about' element={<About />} />
          <Route path='/contact' element={<Contact />} />
        </Routes>
      </div>
      <Footer />
    </>
  );
};

export default App;
