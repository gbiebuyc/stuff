const KEY_UP_ARROW = 38;
const KEY_DOWN_ARROW = 40;
const KEY_LEFT_ARROW = 37;
const KEY_RIGHT_ARROW = 39;
const KEY_LETTER_Z = 90;
const KEY_LETTER_Q = 81;
const KEY_LETTER_S = 83;
const KEY_LETTER_D = 68;

function setKeyHoldState(key, player, setTo) {
    // document.getElementById("debugText").innerHTML =
    //     "KeyCode Pressed: " + key;
    if (key == player.controlKeyForNorth)
        player.keyHeld_North = setTo;
    else if (key == player.controlKeyForSouth)
        player.keyHeld_South = setTo;
    else if (key == player.controlKeyForWest)
        player.keyHeld_West = setTo;
    else if (key == player.controlKeyForEast)
        player.keyHeld_East = setTo;
}

function keyPressed(evt) {
    setKeyHoldState(evt.keyCode, p1, true);
}

function keyReleased(evt) {
    setKeyHoldState(evt.keyCode, p1, false);
}

function initInput() {
    document.addEventListener("keydown", keyPressed);
    document.addEventListener("keyup", keyReleased);
    p1.setupControls(KEY_UP_ARROW, KEY_DOWN_ARROW,
        KEY_LEFT_ARROW, KEY_RIGHT_ARROW);
}