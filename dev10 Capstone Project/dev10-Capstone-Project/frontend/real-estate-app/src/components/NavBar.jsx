import React from 'react';
import { Link } from 'react-router-dom';
import UsernameDisplay from './UsernameDisplay';

const Navbar = ({ isLoggedIn, username, logoutHandler }) => {
  return (
    <nav className='navbar navbar-expand-lg'>
      <div className='container-fluid'>
        <Link className='navbar-brand' to='/'>
          Real Estate App
        </Link>
        <button
          className='navbar-toggler'
          type='button'
          data-bs-toggle='collapse'
          data-bs-target='#navbarNav'
          aria-controls='navbarNav'
          aria-expanded='false'
          aria-label='Toggle navigation'
        >
          <span className='navbar-toggler-icon'></span>
        </button>
        <div className='collapse navbar-collapse' id='navbarNav'>
          <ul className='navbar-nav me-auto'>
            <li className='nav-item'>
              <Link className='nav-link' to='/properties'>
                Properties
              </Link>
            </li>
            <li className='nav-item'>
              <Link className='nav-link' to='/predict-price'>
                Price Prediction
              </Link>
            </li>
            {isLoggedIn && (
              <li className='nav-item'>
                <Link className='nav-link' to='/predict-price-history'>
                  Price Prediction History
                </Link>
              </li>
            )}
            <li className='nav-item'>
              <Link className='nav-link' to='/about'>
                About
              </Link>
            </li>
            <li className='nav-item'>
              <Link className='nav-link' to='/contact'>
                Contact
              </Link>
            </li>
          </ul>
          {isLoggedIn && <UsernameDisplay username={username} />}{' '}
          <button
            className='btn custom-login-btn'
            type='button'
            onClick={logoutHandler} // Directly call logoutHandler
          >
            {isLoggedIn ? 'Logout' : 'Login'}
          </button>
        </div>
      </div>
    </nav>
  );
};

export default Navbar;
