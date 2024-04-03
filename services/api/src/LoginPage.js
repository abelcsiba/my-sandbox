import React, { useState } from 'react'
import axios from 'axios';

function LoginPage({ onLogin }) {
  const [username, setUsername] = useState('')
  const [password, setPassword] = useState('')

  function handleSubmit() {
    axios.get('/api/login')
		  .then(function (response) {
                    onLogin({ username, password })
		  })
	  	  .catch(function (error) {
                    console.log('Error!')
		  })
  }

  return (
    <div className={'mainContainer'}>
      <div className={'titleContainer'}>
        <div>Login</div>
      </div>
      <div className={'inputContainer'}>
        <input type="text" value={username} placeholder="Username" onChange={(e) => setUsername(e.target.value)} className={'inputBox'} />
      </div>
      <br />
      <br />
      <div className={'inputContainer'}>
        <input type="password" value={password} placeholder="Password" onChange={(e) => setPassword(e.target.value)} className={'inputBox'}/>
      </div>
      <br />
      <div className={'inputContainer'}>
        <input className={'inputButton'} type="button" onClick={handleSubmit} value={'Log in'} />
      </div>
    </div>
  )
}

export default LoginPage
