var express = require('express');
var router = express.Router();

/* GET display a file. */
router.get('edit/:path', function(req, res) {
    const file_body = fs.readFileSync(req.params["path"]);
    res.render('index', { title: req.params["path"], file_body: file_body });
});

/* POST save a file. */
router.post('edit/:path', function(req, res) {
    fs.writeFile(req.params["path"], req.body);
});


module.exports = router;
