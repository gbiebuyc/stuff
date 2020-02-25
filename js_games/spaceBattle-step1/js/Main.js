let gc;
let ctx;
let p1;
let ennemy;

function move() {
    p1.move();
    ennemy.move();
    p1.checkMyShipAndShotCollisionAgainst(ennemy);
}

function draw() {
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, gc.width, gc.height);
    p1.draw();
    ennemy.draw();
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
    p1 = new shipClass();
    p1.init(playerPic);
	ennemy = new UFOClass();
	ennemy.init(UFOPic);
    initInput();
    loadImages();
}
