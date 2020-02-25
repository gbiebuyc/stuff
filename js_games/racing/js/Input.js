const KEY_UP_ARROW = 38;
const KEY_DOWN_ARROW = 40;
const KEY_LEFT_ARROW = 37;
const KEY_RIGHT_ARROW = 39;
const KEY_LETTER_Z = 90;
const KEY_LETTER_Q = 81;
const KEY_LETTER_S = 83;
const KEY_LETTER_D = 68;

function setKeyHoldState(key, car, setTo) {
    // document.getElementById("debugText").innerHTML =
    //     "KeyCode Pressed: " + key;
    if (key == car.controlKeyForGas)
        car.keyHeld_Gas = setTo;
    else if (key == car.controlKeyForReverse)
        car.keyHeld_Reverse = setTo;
    else if (key == car.controlKeyForTurnLeft)
        car.keyHeld_TurnLeft = setTo;
    else if (key == car.controlKeyForTurnRight)
        car.keyHeld_TurnRight = setTo;
}

function keyPressed(evt) {
    setKeyHoldState(evt.keyCode, p1, true);
    setKeyHoldState(evt.keyCode, p2, true);
}

function keyReleased(evt) {
    setKeyHoldState(evt.keyCode, p1, false);
    setKeyHoldState(evt.keyCode, p2, false);
}

function initInput() {
    document.addEventListener("keydown", keyPressed);
    document.addEventListener("keyup", keyReleased);
    p1.setupControls(KEY_UP_ARROW, KEY_DOWN_ARROW,
        KEY_LEFT_ARROW, KEY_RIGHT_ARROW);
    p2.setupControls(KEY_LETTER_Z, KEY_LETTER_S,
        KEY_LETTER_Q, KEY_LETTER_D);
}