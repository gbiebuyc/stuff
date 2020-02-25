let gc;
let ctx;
let p1;
let p2;

function move() {
    p1.carMove();
    p2.carMove();
}

function draw() {
    drawTracks();
    p1.drawCar();
    p2.drawCar();
}

function loadingDoneSoStartGame() {
    setInterval(function () {
        move();
        draw();
    }, 1000 / 30);
}

window.onload = function () {
    gc = document.getElementById('gc');
    ctx = gc.getContext('2d');
    p1 = new carClass();
    p2 = new carClass();
    p2.carInit(car2Pic, "Red Car");
    p1.carInit(carPic, "Blue Car");
    initInput();
    loadImages();
}