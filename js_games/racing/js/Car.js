const GROUNDSPEED_DECAY_MULT = 0.94;
const DRIVE_POWER = 0.5;
const REVERSE_POWER = 0.2;
const TURN_RATE = 0.03
const MIN_TURN_SPEED = 0.5;

function carClass() {
    this.carX;
    this.carY;
    this.keyHeld_Gas = false;
    this.keyHeld_Reverse = false;
    this.keyHeld_TurnLeft = false;
    this.keyHeld_TurnRight = false;

    this.setupControls = function (up, down, left, right) {
        this.controlKeyForGas = up;
        this.controlKeyForReverse = down;
        this.controlKeyForTurnLeft = left;
        this.controlKeyForTurnRight = right;
    }

    this.carInit = function (carPic, carName) {
        this.carPic = carPic;
        this.carName = carName;
        this.carReset();
    }

    this.carReset = function () {
        this.carSpeed = 0;
        this.carAng = -Math.PI / 2;
        for (let i = 0; i < trackGrid.length; i++) {
            if (trackGrid[i] == TRACK_PLAYER) {
                let tileRow = Math.floor(i / TRACK_COLS);
                let tileCol = i % TRACK_COLS;
                this.homeX = (tileCol + 0.5) * TRACK_W;
                this.homeY = (tileRow + 0.5) * TRACK_H;
                trackGrid[i] = TRACK_ROAD;
                break;
            }
        }
        this.carX = this.homeX;
        this.carY = this.homeY;
    }

    this.carMove = function () {
        if (this.keyHeld_Gas)
            this.carSpeed += DRIVE_POWER;
        if (this.keyHeld_Reverse)
            this.carSpeed -= REVERSE_POWER;
        if (Math.abs(this.carSpeed) >= MIN_TURN_SPEED) {
            if (this.keyHeld_TurnLeft)
                this.carAng -= TURN_RATE * Math.PI;
            if (this.keyHeld_TurnRight)
                this.carAng += TURN_RATE * Math.PI;
        }
        let nextX = this.carX + Math.cos(this.carAng) * this.carSpeed;
        let nextY = this.carY + Math.sin(this.carAng) * this.carSpeed;
        let tiletype = getTrackAtPixelCoord(nextX, nextY);
        if (tiletype == TRACK_ROAD) {
            this.carX = nextX;
            this.carY = nextY;
        }
        else if (tiletype == TRACK_GOAL) {
            document.getElementById("debugText").innerHTML =
                this.carName + " won the race";
            p1.carReset();
            p2.carReset();
        }
        else
            this.carSpeed = 0;
        this.carSpeed *= GROUNDSPEED_DECAY_MULT;
    }

    this.drawCar = function () {
        drawBitmapCenteredAtLocationWithRotation(
            this.carPic, this.carX, this.carY, this.carAng);
    }
}