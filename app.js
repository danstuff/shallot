var createError = require('http-errors');
var express = require('express');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var fs = require('fs');
var path = require('path');

const settings = JSON.parse(fs.readFileSync("./settings.json"));

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser(settings.secret));
app.use(express.static(path.join(__dirname, 'public')));

function protect(local_path) {
    let file_path = path.join(settings.working_dir, local_path);
    let relative = path.relative(settings.working_dir, file_path);

    if(relative &&
        !relative.startsWith("..") &&
        !path.isAbsolute(relative)) {
        
        return file_path;

    } else {
        return "";
    }
}

function renderError(err, req, res) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');

}

function routeEditor(req, res) {
    let file_path = protect(req.url);

    if(req.body.data) {
        fs.writeFile(file_path, req.body.data, 'utf8', (err) => {});

    } else {
        fs.readFile(file_path, 'utf8', (err, data) => {
            if(err) {
                renderError(err, req, res);
            } else {
                res.render('index',
                    { title: req.url, file_body: data }
                );
            }
        });
    }
}

function routeLogin(req, res) {
    if(req.body.password == settings.password) {
        res.cookie("shallot-auth", settings.handshake, { signed: true });
        res.json({ foot_msg : "Login OK" });

    } else if(req.body.password){
        res.json({ foot_msg : "Login Failed" });

    } else {
        res.render("login");
    }
}

app.use('/', function(req, res, next) {
    if(req.signedCookies[settings.cookie] == settings.handshake) {
        routeEditor(req, res);
    } else {
        routeLogin(req, res);
    }
});

// error handler
app.use(function(err, req, res, next) {
    renderError(err, req, res);
});

module.exports = app;
