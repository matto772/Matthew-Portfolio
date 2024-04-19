import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import '../node_modules/bootstrap/dist/css/bootstrap.min.css'
import SweetAlert2 from 'react-sweetalert2'
import './App.css'
 
 
function App() {
  const [count, setCount] = useState(0)
  const [strTaskName, setTaskName] = useState('')
  const [swalProps, setSwalProps] = useState({})
  return (
    <>
       {/* create a form that takes inputs for task name, task location, due date, and a button to add the task */}
      <div className="form">
        <div className="form-group">
          <label htmlFor="txtTaskName">Task:</label>
          <input type="text" id="txtTaskName" className="form-control" value={strTaskName} onChange={(e) => setTaskName(e.target.value)}/>
        </div>
        <div className="form-group">
          <label htmlFor="txtLocation">Location:</label>
          <input type="text" id="txtLocation" className="form-control" />
        </div>
        <div className="form-group">
          <label htmlFor="txtDueDate">Due Date:</label>
          <input  id="txtDueDate" type="date" className="form-control" />
        </div>
        <button className="btn btn-primary mt-3 col-12" onClick={() => {
                                          setSwalProps({
                                            show:true,
                                            title:'Success',
                                            icon:'success',
                                            text:`New Task Added: ${strTaskName}`,
                                          })
                                          }}>Add Task</button>
        <SweetAlert2 {...swalProps} />
      </div>
    </>
  )
}
 
export default App