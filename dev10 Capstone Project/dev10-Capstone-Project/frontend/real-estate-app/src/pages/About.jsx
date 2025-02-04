import React from 'react';

const About = () => {
  return (
    <div className='extra-space-div'>
      <div className='about-container'>
        <h1>About Us</h1>
        <div className='about-text'>
          <h2>Welcome to Real Estate Insights</h2>
          <p>
            At Real Estate Insights, we are dedicated to transforming the way
            you explore, analyze, and purchase real estate. Our mission is to
            empower homeowners, investors, and real estate enthusiasts with
            cutting-edge tools that simplify the decision-making process.
          </p>
          <p>
            Using the latest advancements in artificial intelligence, our
            platform provides accurate property price predictions and detailed
            analytics tailored to your unique needs. Whether you're searching
            for your dream home, comparing market trends, or evaluating
            potential investments, we've got you covered.
          </p>
          <h2 className='about-h2'>Key Features of Real Estate Insights:</h2>
          <ul className='bullet-points'>
            <li>
              <strong>AI-Powered Price Predictions:</strong> Get an accurate
              estimate for any property based on location, features, and market
              trends.
            </li>
            <li>
              <strong>Customizable Property Search:</strong> Filter and sort
              properties by price, size, amenities, and more to find your
              perfect match.
            </li>
            <li>
              <strong>User-Friendly Interface:</strong> Our seamless design
              ensures you have all the information you need, right at your
              fingertips.
            </li>
          </ul>
          <p>
            We’re passionate about real estate and technology and believe in
            making informed decisions accessible to everyone. Join us as we
            revolutionize the real estate experience!
          </p>
          <div style={{ display: 'flex', justifyContent: 'center' }}>
            <img
              src='src/assets/house_logo.png'
              alt='Real Estate'
              style={{ marginTop: '8px' }}
            />
          </div>
        </div>
      </div>
    </div>
  );
};

export default About;
