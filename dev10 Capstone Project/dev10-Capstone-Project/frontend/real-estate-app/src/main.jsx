import React from 'react';
import { createRoot } from 'react-dom/client';
import { BrowserRouter } from 'react-router-dom'; // Wrap App with BrowserRouter
import App from './App';
import './styles/index.css'; // Include global styles
import 'bootstrap/dist/css/bootstrap.min.css'; // Include Bootstrap CSS

const container = document.getElementById('root');
const root = createRoot(container);

root.render(
  <React.StrictMode>
    <BrowserRouter>
      <App />
    </BrowserRouter>
  </React.StrictMode>
);
