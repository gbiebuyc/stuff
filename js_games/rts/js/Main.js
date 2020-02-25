let gc;
let ctx;
const PLAYER_START_UNITS = 8;
let playerUnits = Array(PLAYER_START_UNITS).fill();
var selectedUnits = [];
var lassoX1 = 0;
var lassoY1 = 0;
var lassoX2 = 0;
var lassoY2 = 0;
var isMouseDragging = false;
const MIN_DIST_TO_COUNT_DRAG = 10;

function move() {
    playerUnits.forEach(e => e.move());
}

function draw() {
    colorRect(0, 0, gc.width, gc.height, 'black');
    playerUnits.forEach(e => e.draw());
    selectedUnits.forEach(e => e.drawSelectionBox());
    if (isMouseDragging)
        coloredOutlineRectCornerToCorner(
            lassoX1, lassoY1, lassoX2, lassoY2, 'yellow');
}

function calculateMousePos(e) {
    let x = e.clientX - gc.getBoundingClientRect().left;
    let y = e.clientY - gc.getBoundingClientRect().top;
    return { x: x, y: y };
}

function mouseMovedEnoughToTreatAsDrag() {
    var deltaX = lassoX1 - lassoX2;
    var deltaY = lassoY1 - lassoY2;
    var dragDist = Math.sqrt(deltaX * deltaX + deltaY * deltaY);
    return (dragDist > MIN_DIST_TO_COUNT_DRAG);
}

window.onload = function () {
    gc = document.getElementById("gc");
    ctx = gc.getContext('2d');
    setInterval(function () {
        move();
        draw();
    }, 1000 / 30);
    gc.addEventListener('mousemove', function (e) {
        p = calculateMousePos(e);
        // document.getElementById('debugText').innerHTML =
        //     p.x + ", " + p.y;
        if (isMouseDragging) {
            lassoX2 = p.x;
            lassoY2 = p.y;
        }
    });
    gc.addEventListener('mousedown', function (e) {
        p = calculateMousePos(e);
        lassoX1 = p.x;
        lassoY1 = p.y;
        lassoX2 = p.x;
        lassoY2 = p.y;
        isMouseDragging = true;
    });
    gc.addEventListener('mouseup', function (e) {
        isMouseDragging = false;

        if (mouseMovedEnoughToTreatAsDrag()) {
            selectedUnits = [];
            for (var i = 0; i < playerUnits.length; i++) {
                if (playerUnits[i].isInBox(lassoX1, lassoY1, lassoX2, lassoY2)) {
                    selectedUnits.push(playerUnits[i]);
                }
            }
            document.getElementById("debugText").innerHTML =
            "Selected " + selectedUnits.length + " units";
        }
        else {
            p = calculateMousePos(e);
            selectedUnits.forEach(e => e.gotoNear(p.x, p.y));
            document.getElementById("debugText").innerHTML =
                "Moving to " + p.x + ", " + p.y;
        }
    });
    playerUnits.forEach((e, i, a) => a[i] = new unitClass());
    playerUnits.forEach(e => e.reset());
}