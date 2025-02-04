import React, { useState } from 'react';
import { loginUser, registerUser } from '../api/login';

const Login = ({ loginHandler }) => {
  const [isLogin, setIsLogin] = useState(true);
  const [username, setUsername] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [errorMessage, setErrorMessage] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    setErrorMessage('');

    try {
      if (isLogin) {
        const response = await loginUser({ email, password });
        localStorage.setItem('accessToken', response.access_token);
        localStorage.setItem('user', JSON.stringify(response.user));
        loginHandler(response.user, response.access_token);
      } else {
        const response = await registerUser({ username, email, password });
        localStorage.setItem('accessToken', response.access_token);
        localStorage.setItem('user', JSON.stringify(response.user));
        loginHandler(response.user, response.access_token);
      }
    } catch (error) {
      setErrorMessage(error.message || 'An error occurred. Please try again.');
    }
  };

  return (
    <div className='extra-space-div'>
      <div className='login-container'>
        <h1>{isLogin ? 'Login' : 'Register'}</h1>
        {errorMessage && (
          <div className='alert alert-danger'>{errorMessage}</div>
        )}
        <form onSubmit={handleSubmit}>
          {!isLogin && (
            <div className='form-group'>
              <label htmlFor='username'>Username</label>
              <input
                type='text'
                id='username'
                className='form-control'
                value={username}
                onChange={(e) => setUsername(e.target.value)}
              />
            </div>
          )}
          <div className='form-group'>
            <label htmlFor='email'>Email</label>
            <input
              type='email'
              id='email'
              className='form-control'
              value={email}
              onChange={(e) => setEmail(e.target.value)}
              required
            />
          </div>
          <div className='form-group'>
            <label htmlFor='password'>Password</label>
            <input
              type='password'
              id='password'
              className='form-control'
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              required
            />
          </div>
          <div className='button-group'>
            <button type='submit' className='btn btn-primary'>
              {isLogin ? 'Login' : 'Register'}
            </button>
            <div className='divider'></div>
            <button
              onClick={() => setIsLogin(!isLogin)}
              className='btn btn-secondary'
            >
              {isLogin ? 'Switch to Register' : 'Switch to Login'}
            </button>
          </div>
        </form>
      </div>
    </div>
  );
};

export default Login;
