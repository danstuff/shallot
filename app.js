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

function pathRemove(path, sym) {
    path = path.replace(sym+"/", "");
    path = path.replace(sym, "");
    return path;
}

function protect(local_path) {
    if(local_path) {
        let file_path = path.join(settings.working_dir, local_path);
        file_path = pathRemove(file_path, "..");
        file_path = pathRemove(file_path, "~");

        let relative = path.relative(settings.working_dir, file_path);

        if(relative && !path.isAbsolute(relative)) {
            
            return file_path;

        } else {
            return "";
        }
    } else {
        return settings.working_dir;
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

function routeDirectory(dir_path, req, res) {
    let dir_str = "";

    fs.readdir(dir_path, (err, files) => {
        if(err) {
            console.log(err);
        } else {

            for(let i = 0; i < files.length; i++) {

                dir_str += files[i];

                if(fs.lstatSync(
                        path.join(dir_path, files[i])
                    ).isDirectory()) {
                    dir_str += "/";
                }

                if (i < files.length-1) {
                    dir_str += "\n";
                }
            }
        }

        res.render('index',
            { title: dir_path, file_body: dir_str, is_directory: true }
        );
    });

}

function routeEditor(file_path, req, res) {
    if(req.body.data) {
        fs.writeFile(file_path, req.body.data, 'utf8', (err) => {});

    } else {
        fs.readFile(file_path, 'utf8', (err, data) => {
            if(err) {
                renderError(err, req, res);
            } else {
                res.render('index',
                    { title: file_path, file_body: data, is_file: true }
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


app.use('/edit/*', function(req, res, next) {
    let file_path = protect(req.params[0]);
    
    if(req.signedCookies[settings.cookie] == settings.handshake) {
        if(fs.lstatSync(file_path).isDirectory()) {
            routeDirectory(file_path, req, res);

        } else {
            routeEditor(file_path, req, res);
        }
    } else {
        routeLogin(req, res);
    }
});

app.use('/complete/:phrase', function(req, res, next) {
    if(req.signedCookies[settings.cookie] == settings.handshake) {
        routeCompletion(req, res);
    } else {
        routeLogin(req, res);
    }
});

app.use('/dictionary/', function(req, res, next) {
    console.log(req.body.dictionary);
});

app.use('/', function(req, res, next) {
    routeLogin(req, res);
});

// error handler
app.use(function(err, req, res, next) {
    renderError(err, req, res);
});

module.exports = app;
