function numkeyCheck(e) {
    var event = e || window.event;
    var keyVALUE;
    if (event.keyCode > 47 && event.keyCode < 58) {
        keyVALUE = event.target.value + String.fromCharCode((event.keyCode));
        if (0 > keyVALUE || 100 < keyVALUE) {
            e.preventDefault();
            return false;
        }
    }
}

function setCirclePercentage(color, value) {
    if (value > 100)
        value = 100;
    else if (value < 0)
        value = 0;

    $(".circular-chart." + color + " .circle").attr('stroke-dasharray', value + ", 100");
    $("#" + color).text(value + '%');
}

function calcAngleDegrees(x, y) {
    var degree = Math.atan2(y, x) * (180.0 / 3.14159265359) + 180.0;

    if (degree >= 90)
        return Math.atan2(y, x) * (180.0 / 3.14159265359) + 90.0/*180.0 - 90.0*/;
    else
        return Math.atan2(y, x) * (180.0 / 3.14159265359) + 450.0/*180.0 + 260.0*/;
}