const UFO_SPEED = 1.9;
const UFO_TIME_BETWEEN_CHANGE_DIR = 85;
const UFO_COLLISION_RADIUS = 22;

UFOClass.prototype = new movingWrapPositionClass();

function UFOClass() {
	this.x = 75;
	this.y = 75;

	this.init = function (pic) {
		this.playerPic = pic;
		this.reset();
	}

	this.superclassReset = this.reset;
	this.reset = function () {
		this.superclassReset();
		this.cyclesTilDirectionChange = 0;
		this.x = Math.random() * gc.width;
		this.y = Math.random() * gc.height;
	}

	this.superclassMove = this.move;
	this.move = function () {
		this.superclassMove();
		this.cyclesTilDirectionChange--;
		if (this.cyclesTilDirectionChange <= 0) {
			let randAng = Math.random() * 2 * Math.PI;
			this.vx = Math.cos(randAng) * UFO_SPEED;
			this.vy = Math.sin(randAng) * UFO_SPEED;
			this.cyclesTilDirectionChange =
				UFO_TIME_BETWEEN_CHANGE_DIR;
		}
	}

	this.draw = function () {
		drawBitmapCenteredAtLocationWithRotation(
			this.playerPic, this.x, this.y, 0);
	}

	this.isOverlappingPoint = function (x, y) {
		let dx = x - this.x;
		let dy = y - this.y;
		let dist = Math.sqrt((dx * dx) + (dy * dy));
		return (dist <= UFO_COLLISION_RADIUS);
	}
}
