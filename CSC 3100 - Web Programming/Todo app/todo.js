//Matthew Ogurkis
//todo.js
//backend of my todo app; may add more if time permits but for now it just parses and puts the data for tasks into the database and is able to output all of them.
//date started: 4/3/2024
//date completed: 4/4/2024
const express = require('express');
const cors = require('cors');
const sqlite3 = require('sqlite3').verbose();
const dbSource = "todo.db";
const db = new sqlite3.Database(dbSource);
const HTTP_PORT = 8000;


console.log("Listening on port " + HTTP_PORT);
var app = express();
app.use(cors());
app.use(express.json());

class todoTask {
    constructor(taskName, dateDue, location, instructions, taskStatus, taskId) {
        this.taskName = taskName;
        this.dateDue = dateDue;
        this.location = location;
        this.instructions = instructions;
        this.status = taskStatus;
        this.taskId = taskId;
    }
}

//creating the endpoint that will hold and put the new task into the database
app.post('/tasks', (req, res, next) => {
    let strTaskName = req.body.taskName;
    let strDueDate = req.body.dateDue;
    let strLocation = req.body.location;
    let strInstructions = req.body.instructions;
    let strStatus = req.body.status;
    let strTaskID = req.body.taskId;    
    let strCommand = "INSERT INTO tblTasks VALUES (?, ?, ?, ?, ?, ?)";
    //making sure the parameters exsist
    if(strTaskName && strDueDate && strLocation && strInstructions && strStatus && strTaskID){
        let arrParameters = [strTaskName,strDueDate,strLocation,strInstructions,strStatus,strTaskID];
        let newTask = new todoTask(strTaskName,strDueDate,strLocation,strInstructions,strStatus,strTaskID);
       
        db.run(strCommand,arrParameters, function(err,result) {
            if (err) {
                res.status(400).json({error:err.message})
                res.status(400).json({ error: "Failed to add task." });
            } else {
                res.status(201).json({
                    message:"Added a new task!",
                    todoTask:newTask
                })
            }
        }); 
    }
});

//getting all tasks here
app.get('/alltasks', (req, res, next) => {
    const strCommand = "SELECT * FROM tblTasks";
    db.all(strCommand, (err, rows) => {
        if (err) {
            console.error("Error retrieving tasks:", err.message);
            res.status(404).json({ error: "Failed to retrieve tasks." });
        } else {
            res.status(200).json(rows);
        }
    });
});

app.listen(HTTP_PORT);

