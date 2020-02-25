let gc;
let ctx;
let p1;
let p2;

function move() {
    p1.move();
}

function draw() {
    drawRoom();
    p1.draw();
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
    p1 = new warriorClass();
    p1.init(playerPic, "player 1");
    initInput();
    loadImages();
}