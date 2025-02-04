import React from 'react';

const Contact = () => {
  return (
    <div className='extra-space-div'>
      <div className='contact-container'>
        <div className='contact-form'>
          <h1>Contact Us</h1>
          <div style={{ display: 'flex', justifyContent: 'center' }}>
            <img
              src='src/assets/houseAndKeysLogo.jpg'
              alt='Real Estate'
              style={{
                marginTop: '16px',
                marginBottom: '24px',
                width: '18rem',
              }}
            />
          </div>
          <h2>We’d Love to Hear From You!</h2>
          <p>
            Have questions, feedback, or need assistance? Our team is here to
            help. Feel free to reach out to us using the contact information
            below.
          </p>

          <div className='contact-info'>
            <p>
              <strong>Email:</strong> support@realestateinsights.com
            </p>
            <p>
              <strong>Phone:</strong> +1-800-555-REAL (7325)
            </p>
            <p>
              <strong>Address:</strong> 123 Property Lane, Suite 456, Real
              Estate City, RE 78901
            </p>
          </div>

          <p>
            Or, use the form below to send us a message directly. We’ll get back
            to you as soon as possible.
          </p>

          <form>
            <div className='form-group'>
              <label htmlFor='name' className='form-label'>
                Name
              </label>
              <input
                type='text'
                id='name'
                name='name'
                required
                className='form-control'
              />
            </div>

            <div className='form-group'>
              <label htmlFor='email' className='form-label'>
                Email
              </label>
              <input
                type='email'
                id='email'
                name='email'
                required
                className='form-control'
              />
            </div>

            <div className='form-group'>
              <label htmlFor='subject' className='form-label'>
                Subject
              </label>
              <input
                type='text'
                id='subject'
                name='subject'
                required
                className='form-control'
              />
            </div>

            <div className='form-group'>
              <label htmlFor='message' className='form-label'>
                Message
              </label>
              <textarea
                id='message'
                name='message'
                required
                className='form-control'
              ></textarea>
            </div>

            <button type='submit' className='btn-primary'>
              Send Message
            </button>
          </form>
        </div>
      </div>
    </div>
  );
};

export default Contact;
