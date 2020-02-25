const SHOT_SPEED = 6.0;
const SHOT_LIFE = 30;
const SHOT_DISPLAY_RADIUS = 2.0;

shotClass.prototype = new movingWrapPositionClass();

function shotClass() {
    this.x = 75;
    this.y = 75;

	this.superclassReset = this.reset;
    this.reset = function () {
		this.superclassReset();
        this.shotLife = 0;
    }

	this.superclassMove = this.move;
    this.move = function () {
		if (this.shotLife > 0) {
			this.shotLife--;
			this.superclassMove();
		}
	}

	this.draw = function () {
		if (this.shotLife)
			colorCircle(this.x, this.y,
				SHOT_DISPLAY_RADIUS, 'white');
	}

	this.isShotReadyToFire = function () {
		return (this.shotLife <= 0);
	}

	this.shootFrom = function (shipFiring) {
		this.x = shipFiring.x;
		this.y = shipFiring.y;
		this.vx = Math.cos(shipFiring.ang) *
			SHOT_SPEED + shipFiring.vx;
		this.vy = Math.sin(shipFiring.ang) *
			SHOT_SPEED + shipFiring.vy;
		this.shotLife = SHOT_LIFE;
	}

	this.hitTest = function (ennemy) {
		if (this.shotLife <= 0)
			return false;
		return ennemy.isOverlappingPoint(this.x, this.y);
	}
}
