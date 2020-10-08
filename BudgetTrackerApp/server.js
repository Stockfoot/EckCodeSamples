const express = require('express');
const mysql = require('mysql');
const session = require('express-session');
const app = express();
const {OAuth2Client} = require('google-auth-library');
const bodyParser = require('body-parser');
const request = require('request');
const cookieParser = require('cookie-parser');

const CLIENT_ID = [REDACTED];
const CLIENT_SECRET = [REDACTED];
const REDIRECT = "https://cs361group1.appspot.com/auth";
const CLIENT_REDIRECT = "https://cs361group1.appspot.com";
const CLIENT_REDIRECT_NEW = "https://cs361group1.appspot.com/register.html";
const CLIENT_ALL_BUDGETS = "https://cs361group1.appspot.com/all_budgets.html";
const CLIENT_ALL_GOALS = "https://cs361group1.appspot.com/all_goals.html";
const SCOPE = "profile email";
const RESP_TYPE = "code";
const TOKEN_URI = "https://oauth2.googleapis.com/token";
const AUTH_API = "https://accounts.google.com/o/oauth2/v2/auth";
const client = new OAuth2Client(CLIENT_ID);

app.use(session({secret: [REDACTED]}));

var state;

// configure
const PORT = process.env.PORT || 8080;
app.set("port", PORT);
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(express.static(__dirname + '/public'));
app.use(cookieParser())

//Database connection
let pool;
const createPool = async () => {
  pool = await mysql.createPool({
    user: 'root',
    password: [REDACTED],
    database: 'cs361',
    // If connecting via unix domain socket, specify the path
    socketPath: '/cloudsql/cs361group1:us-west2:budget-tracker'
});
};
createPool();


//Generate state value - used in authentication flow
function getState(){
    var add = 1;
    var max = Math.pow(10, 10 + add);
    var min = max/10;
    var num = Math.floor( Math.random() * (max - min + 1) ) + min;

    return ("" + num).substring(add);
}

//Confirm the JWT is valid and extract the account's email address
async function verify(token) {
    const ticket = await client.verifyIdToken({
        idToken: token,
        audience: CLIENT_ID
    }).catch(console.error);

    if(ticket){
        const payload = ticket.getPayload();
        return payload['email'];
    }
    else{
        return undefined;
    }
}


//Control Functions

//Authentication route - sets user session upon authentication through Google
app.get('/auth', (req, response) => {
    if(req.headers.referer == 'https://cs361group1.appspot.com/'){
        state = getState();
        response.redirect(AUTH_API + "?scope=" + SCOPE + "&redirect_uri=" + REDIRECT + "&client_id=" + CLIENT_ID + "&response_type=" + RESP_TYPE + "&state=" + state);
    }
    else if(req.query.state == state){
        const TOK_URL = TOKEN_URI + "?code=" + req.query.code + "&client_id=" + CLIENT_ID + "&client_secret=" + CLIENT_SECRET + "&redirect_uri=" + REDIRECT + "&grant_type=authorization_code";
        request.post(TOK_URL, (error, res, body) => {
            if(error){
                console.error(error);
            }
            else{
                const obj = JSON.parse(body);
                const token = obj.id_token;
                verify(token).then( (user_email) => {
                    sess=req.session;
                    sess.email = user_email; // set the email as session
                    pool.query('SELECT * FROM users WHERE email = ?', [user_email], async (err, rows, fields) => {
                      if(err){
                         console.error(err);
                     }
                     else if(rows[0]){
                         response.redirect(CLIENT_REDIRECT);
                     }
                     else{
                         response.redirect(CLIENT_REDIRECT_NEW);
                     }
                 });
                });
            }
        });
    }
});


//Create Goal Route
app.get('/creategoal', (req, res) => {
    sess = req.session;
    if(sess.email) {
        if (req.query.name == null || req.query.name == "") {
            return res.status(400).send({
                message: 'Goal name must be specified.'
            });
        }
        if (req.query.tamount == null || req.query.tamount == "" || req.query.tamount <= 0) {
            return res.status(400).send({
                message: 'Goal total amount must be specified and should be a positive number.'
            });
        }
        if (req.query.startdate == null || req.query.startdate == "") {
            return res.status(400).send({
                message: 'Goal start date must be specified.'
            });
        }
        if (req.query.camount == null || req.query.camount == "" || req.query.camount <= 0) {
            return res.status(400).send({
                message: 'Goal contribution amount must be specified and should be a positive number.'
            });
        }
        if (req.query.cfrequency == null || req.query.cfrequency == "") {
            return res.status(400).send({
                message: 'Goal contribution frequency must be specified.'
            });
        }
        // the primary key of the goals table is email + name as a composite primary key. This is because different user can have goals
        // with same name hence an email with goal name (i.e. email + name) together identifies a row in this table uniquely.
        pool.query("INSERT INTO `goals` (`email`, `name`, `tamount`, `startdate`, `camount`, `cfrequency`) VALUES (?, ?, ?, ?, ?, ?)",
            [sess.email,
            req.query.name,
            req.query.tamount,
            req.query.startdate,
            req.query.camount,
            req.query.cfrequency],
            function (err, result) {
                if (err) {
                    next(err);
                    return;
                }
                res.redirect(CLIENT_REDIRECT);
            });
    } else {
        res.status(401).send("Unauthorized: Please login first to create a goal");
    }
});

//Update Goal Route
app.get('/updateGoal', (req, res) => {
    sess = req.session;
    if(sess.email) {
        if (req.query.name == null || req.query.name == "") {
            return res.status(400).send({
                message: 'Goal name must be specified.'
            });
        }
        if (req.query.tamount == null || req.query.tamount == "" || req.query.tamount <= 0) {
            return res.status(400).send({
                message: 'Goal total amount must be specified and should be a positive number.'
            });
        }
        if (req.query.startdate == null || req.query.startdate == "") {
            return res.status(400).send({
                message: 'Goal start date must be specified.'
            });
        }
        if (req.query.camount == null || req.query.camount == "" || req.query.camount <= 0) {
            return res.status(400).send({
                message: 'Goal contribution amount must be specified and should be a positive number.'
            });
        }
        if (req.query.cfrequency == null || req.query.cfrequency == "") {
            return res.status(400).send({
                message: 'Goal contribution frequency must be specified.'
            });
        }
        // the primary key of the goals table is email + name as a composite primary key. This is because different user can have goals
        // with same name hence an email with goal name (i.e. email + name) together identifies a row in this table uniquely.
        pool.query("UPDATE goals SET name=?, tamount=?, startdate=?, camount=?, cfrequency=? WHERE email=? AND name=?",
            [req.query.name,
            req.query.tamount,
            req.query.startdate,
            req.query.camount,
            req.query.cfrequency,
			sess.email,
			req.query.orig_name],
            function (err, result) {
                if (err) {
                    next(err);
                    return;
                }
                res.redirect(CLIENT_ALL_GOALS);
            });
    } else {
        res.status(401).send("Unauthorized: Please login first to update a goal");
    }
});

//Create Budget Route
app.get('/createbudget', (req, res) => {
    sess = req.session;
    if(sess.email) {
        if (req.query.totalBudget <= 0) {
            return res.status(400).send({
                message: 'Total Budget must be greater than $0.00'
            });
        }
        if (req.query.budgetNotToExceed <= 0) {
            return res.status(400).send({
                message: 'Budget Not To Exceed must be greater than $0.00'
            });
        }
       
        pool.query("INSERT INTO `budgets` (`email`, `budgetMonth`, `totalBudget`, `budgetNotToExceed`, `budgetCategory1`, `targetBudgetCategory1`, `budgetCategory2`, `targetBudgetCategory2`, `budgetCategory3`, `targetBudgetCategory3`, `name`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
            [sess.email,
            req.query.budgetMonth,
            req.query.totalBudget,
            req.query.budgetNotToExceed,
            req.query.budgetCategory1,
            req.query.targetBudgetCategory1,
            req.query.budgetCategory2,
            req.query.targetBudgetCategory2,
            req.query.budgetCategory3,
            req.query.targetBudgetCategory3,
            req.query.name],
            function (err, result) {
                if (err) {
                    next(err);
                    return;
                }
                res.redirect(CLIENT_REDIRECT);
            });
    } else {
        res.status(401).send("Unauthorized: Please login first to create a budget");
    }
});

//Update Budget Route
app.get('/updateBudget', (req, res) => {
    sess = req.session;
    if(sess.email) {
        if (req.query.totalBudget <= 0) {
            return res.status(400).send({
                message: 'Total Budget must be greater than $0.00'
            });
        }
        if (req.query.budgetNotToExceed <= 0) {
            return res.status(400).send({
                message: 'Budget Not To Exceed must be greater than $0.00'
            });
        }
        if (req.query.budgetNotToExceed > req.query.totalBudget) {
            return res.status(400).send({
                message: 'Budget Not To Exceed cannot be greater than Total Budget'
            });
        }
        pool.query("UPDATE budgets SET budgetMonth=?, totalBudget=?, budgetNotToExceed=?, budgetCategory1=?, targetBudgetCategory1=?, budgetCategory2=?, targetBudgetCategory2=?, budgetCategory3=?, targetBudgetCategory3=?, name=? WHERE email=? and budget_id=?",
            [
            req.query.budgetMonth,
            req.query.totalBudget,
            req.query.budgetNotToExceed,
            req.query.budgetCategory1,
            req.query.targetBudgetCategory1,
            req.query.budgetCategory2,
            req.query.targetBudgetCategory2,
            req.query.budgetCategory3,
            req.query.targetBudgetCategory3,
            req.query.budgetName,
			sess.email,
			req.query.budget_id],
            function (err, result) {
                if (err) {
                    next(err);
                    return;
                }
                res.redirect(CLIENT_ALL_BUDGETS);
            });
    } else {
        res.status(401).send("Unauthorized: Please login first to update a budget");
    }
});

// Logout route -- destroys the current session
app.get('/logout', (req, res) => {
    req.session.destroy((err) => {
        if(err) {
            return console.log(err);
        }
        res.redirect(CLIENT_REDIRECT);
    });
})


// register registers a new user by storing their details in users table
app.get('/register', (req, res) => {
    sess = req.session;
    if(sess.email) {
            // some basic data checks
            if (req.query.fname == null || req.query.fname == "") {
                return res.status(400).send({
                    message: 'First name must be specified.'
                });
            }
            if (req.query.username == null || req.query.username == "") {
                return res.status(400).send({
                    message: 'Username must be specified.'
                });
            }
            if (req.query.age != null && req.query.age != "" && req.query.age <= 0) {
                return res.status(400).send({
                    message: 'A valid age must be specified.'
                });
            }
            if (req.query.zip != null && req.query.zip != "" && req.query.zip <= 0) {
                return res.status(400).send({
                    message: 'A valid zip must be specified.'
                });
            }
            pool.query("INSERT INTO `users` (`username`, `first_name`, `last_name`, `email`, `age`, `zip`) VALUES (?, ?, ?, ?, ?, ?)",
                [req.query.username,
                req.query.fname,
                req.query.lname,
                sess.email,
                req.query.age,
                req.query.zip],
                function (err, result) {
                    if (err) {
                        next(err);
                        return;
                    }
                    res.redirect(CLIENT_REDIRECT);
                });

        } else{
            res.status(401).send("Unauthorized: Please login first to create an account");
        }
    });

// allows user to update account details which includes username, age, and zip
app.get('/updateAccount', (req, res) => {
    sess = req.session;
    if(sess.email) {
            // some basic data checks
            if (req.query.username == null || req.query.username == "") {
                return res.status(400).send({
                    message: 'Username must be specified.'
                });
            }
            if (req.query.age != null && req.query.age != "" && req.query.age <= 0) {
                return res.status(400).send({
                    message: 'A valid age must be specified.'
                });
            }
            if (req.query.zip != null && req.query.zip != "" && req.query.zip <= 0) {
                return res.status(400).send({
                    message: 'A valid zip must be specified.'
                });
            }
            pool.query("UPDATE users SET username=?, first_name=?, last_name=?, email=?, age=?, zip=? WHERE user_id=?",
                [req.query.username,
                req.query.first_name,
                req.query.last_name,
                sess.email,
                req.query.age,
                req.query.zip,
                req.query.user_id],
                function (err, result) {
                    if (err) {
                        next(err);
                        return;
                    }
                    res.redirect(CLIENT_REDIRECT);
                });

        } else{
            res.status(401).send("Unauthorized: You must first create an account");
        }
    });

//Get user route - returns a JSON object containing all data belonging to the user who matches the JWT
//Requires session for user previously established
app.get('/user', (req, res) => {
    sess = req.session;
    if(sess.email) {
        pool.query('SELECT * FROM users WHERE email = ?', [sess.email], async (err, rows, fields) => {
            if(err){
               console.error(err);
            }
            else if(rows[0]){
               res.status(200).send(JSON.stringify(rows[0]));
            }
            else{
               res.status(404).send("Not found");
           }
       });
    }
    else{
        res.status(401).send("Unauthorized: No valid session");
    }
});

//Get budget route - returns a JSON object containing all data belonging to the budget designated
//Requires session for user previously established
app.get('/budget', (req, res) => {
    sess = req.session;
    if(sess.email) {
        pool.query('SELECT * FROM budgets WHERE email = ? AND name = ?', [sess.email, req.query.name], async (err, rows, fields) => {
            if(err){
               console.error(err);
            }
            else if(rows[0]){
               res.status(200).send(JSON.stringify(rows[0]));
            }
            else{
               res.status(404).send("Not found");
           }
       });
    }
    else{
        res.status(401).send("Unauthorized: No valid session");
    }
});

//Get budgets route - returns a JSON object containing the names of all budgets belonging to the specified user
//Requires session for user previously established
app.get('/budgets', (req, res) => {
    sess = req.session;
    if(sess.email) {
        pool.query('SELECT name FROM budgets WHERE email = ?', [sess.email], async (err, rows, fields) => {
            if(err){
               console.error(err);
            }
            else if(rows){
               res.status(200).send(JSON.stringify(rows));
            }
            else{
               res.status(404).send("Not found");
           }
       });
    }
    else{
        res.status(401).send("Unauthorized: No valid session");
    }
});

//Get goal route - returns a JSON object containing all data belonging to the goal designated
//Requires session for user previously established
app.get('/goal', (req, res) => {
    sess = req.session;
    if(sess.email) {
        pool.query('SELECT email, name, tamount, DATE_FORMAT(startdate, "%Y-%m-%d") AS startdate, camount, cfrequency FROM goals WHERE email = ? AND name = ?', [sess.email, req.query.name], async (err, rows, fields) => {
            if(err){
               console.error(err);
            }
            else if(rows[0]){
               res.status(200).send(JSON.stringify(rows[0]));
            }
            else{
               res.status(404).send("Not found");
           }
       });
    }
    else{
        res.status(401).send("Unauthorized: No valid session");
    }
});

//Get goals route - returns a JSON object containing the names of all goals belonging to the specified user
//Requires session for user previously established
app.get('/goals', (req, res) => {
    sess = req.session;
    if(sess.email) {
        pool.query('SELECT name FROM goals WHERE email = ?', [sess.email], async (err, rows, fields) => {
            if(err){
               console.error(err);
            }
            else if(rows){
               res.status(200).send(JSON.stringify(rows));
            }
            else{
               res.status(404).send("Not found");
           }
       });
    }
    else{
        res.status(401).send("Unauthorized: No valid session");
    }
});

app.listen(app.get("port"), function () {
    console.log(`Server listening on port ${PORT}...`);
});
