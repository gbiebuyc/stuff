const KEY_UP_ARROW = 38;
const KEY_DOWN_ARROW = 40;
const KEY_LEFT_ARROW = 37;
const KEY_RIGHT_ARROW = 39;
const KEY_LETTER_Z = 90;
const KEY_LETTER_Q = 81;
const KEY_LETTER_S = 83;
const KEY_LETTER_D = 68;
const KEY_SPACEBAR = 32;

function setKeyHoldState(key, ship, setTo) {
    // document.getElementById("debugText").innerHTML =
    //     "KeyCode Pressed: " + key;
    if (key == ship.controlKeyForGas)
        ship.keyHeld_Gas = setTo;
    else if (key == ship.controlKeyForReverse)
        ship.keyHeld_Reverse = setTo;
    else if (key == ship.controlKeyForTurnLeft)
        ship.keyHeld_TurnLeft = setTo;
    else if (key == ship.controlKeyForTurnRight)
        ship.keyHeld_TurnRight = setTo;
}

function keyPressed(evt) {
    if (evt.keyCode == p1.controlKeyForShotFire)
        p1.cannonFire();
    else
        setKeyHoldState(evt.keyCode, p1, true);
}

function keyReleased(evt) {
    setKeyHoldState(evt.keyCode, p1, false);
}

function initInput() {
    document.addEventListener("keydown", keyPressed);
    document.addEventListener("keyup", keyReleased);
    p1.setupControls(KEY_UP_ARROW, KEY_LEFT_ARROW,
        KEY_RIGHT_ARROW, KEY_SPACEBAR);
}