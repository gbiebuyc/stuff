const SPACESPEED_DECAY_MULT = 0.99;
const THRUST_POWER = 0.15;
const TURN_RATE = 0.03

shipClass.prototype = new movingWrapPositionClass();

function shipClass() {
	this.x = 75;
	this.y = 75;
	this.keyHeld_Gas = false;
	this.keyHeld_TurnLeft = false;
	this.keyHeld_TurnRight = false;

	this.setupControls = function (up, left, right, shot) {
		this.controlKeyForGas = up;
		this.controlKeyForTurnLeft = left;
		this.controlKeyForTurnRight = right;
		this.controlKeyForShotFire = shot;
	}

	this.init = function (playerPic) {
		this.myShot = new shotClass();
		this.playerPic = playerPic;
		this.reset();
	}

	this.superclassReset = this.reset;
	this.reset = function () {
		this.superclassReset();
		this.ang = -Math.PI / 2;
		this.myShot.reset();
	}

	this.superclassMove = this.move;
	this.move = function () {
		if (this.keyHeld_Gas) {
			this.vx += Math.cos(this.ang) * THRUST_POWER;
			this.vy += Math.sin(this.ang) * THRUST_POWER;
		}
		if (this.keyHeld_TurnLeft)
			this.ang -= TURN_RATE * Math.PI;
		if (this.keyHeld_TurnRight)
			this.ang += TURN_RATE * Math.PI;
		this.superclassMove();
		this.vx *= SPACESPEED_DECAY_MULT;
		this.vy *= SPACESPEED_DECAY_MULT;
		this.myShot.move();
	}

	this.draw = function () {
		this.myShot.draw();
		drawBitmapCenteredAtLocationWithRotation(
			this.playerPic, this.x, this.y, this.ang);
	}

	this.cannonFire = function () {
		if (this.myShot.isShotReadyToFire())
			this.myShot.shootFrom(this);
	}

	this.checkMyShipAndShotCollisionAgainst = function (ennemy) {
		if (ennemy.isOverlappingPoint(this.x, this.y)) {
			this.reset();
			document.getElementById("debugText").innerHTML = "Player Crashed!";
		}
		if (this.myShot.hitTest(ennemy)) {
			ennemy.reset();
			this.myShot.reset();
			document.getElementById("debugText").innerHTML = "Ennemy Blasted!";
		}
	}
}
