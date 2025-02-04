import React, { useState } from 'react';

const UsernameDisplay = ({ username }) => {
  const [borderColor, setBorderColor] = useState('blue'); // Start with blue border color

  const cycleColor = () => {
    if (borderColor === 'blue') {
      setBorderColor('red'); // Change to red on next click
    } else if (borderColor === 'red') {
      setBorderColor('green'); // Change to green on next click
    } else {
      setBorderColor('blue'); // Change back to blue on next click
    }
  };

  return (
    <span
      className={`username-display ${borderColor}`}
      onClick={cycleColor} // Trigger color change on click
      style={{
        backgroundColor: 'white', // Always white
        borderRadius: '5px',
        padding: '6px 10px',
        cursor: 'pointer',
        transition: 'box-shadow 0.3s ease, border 0.3s ease', // Smooth transitions
      }}
    >
      Welcome, {username}!
    </span>
  );
};

export default UsernameDisplay;
