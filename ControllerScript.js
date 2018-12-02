$( document ).ready(function() {
    // Devices IP: 192.168.1.133
    var address = "192.168.1.133";
    var device = new Device(address);

    // Buttons
    $('#forward').mousedown(function () {
        console.debug(document.getElementById("mySelect").value);
        device.callFunction("forward");
    });
    $('#forward').mouseup(function () {
        device.callFunction("stop");
    });

    $('#right').mousedown(function () {
        device.callFunction("right");
    });
    $('#right').mouseup(function () {
        device.callFunction("stop");
    });

    $('#left').mousedown(function () {
        device.callFunction("left");
    });
    $('#left').mouseup(function () {
        device.callFunction("stop");
    });

    $('#backward').mousedown(function () {
        device.callFunction("backward");
    });
    $('#backward').mouseup(function () {
        device.callFunction("stop");
    });

    $('#honk').mousedown(function () {
        device.callFunction("honk");
    });


    document.addEventListener('keydown', function(event) {
        if(event.keyCode == 37) {
           device.callFunction("left");
        }
        else if(event.keyCode == 39) {
            device.callFunction("right");
        }
        else if(event.keyCode == 40) {
            device.callFunction("backward");
        }
        else if(event.keyCode == 38) {
            device.callFunction("forward");
        }
        else if(event.keyCode == 32) {
            device.callFunction("honk");
        }

    });
    document.addEventListener('keyup', function(event) {
        if(event.keyCode == 37 || event.keyCode == 38 || event.keyCode == 39 || event.keyCode == 40) {
            device.callFunction("stop");
        }
    });
});