// footer message fade out
function showMessage(str) {
    $("#foot_msg").html(str);
    $("#foot_msg").show();

    setTimeout(() => {
        $("#foot_msg").fadeOut();
    }, 1000);
}

// enter to submit a password
function enablePassword() {
    $("#password").keypress(function(e) {
        let code = e.which || e.keyCode;
        if(code == 13) { // enter
            $.post(window.location.href,
                { password : $("#password").val() },
                (d) => {
                    $("#password").val("");
                    showMessage(d.foot_msg);
                }
            );
        }
    });
}

enablePassword();
