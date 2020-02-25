function movingWrapPositionClass() {
    this.x = 75;
    this.y = 75;

    this.reset = function () {
        this.x = gc.width / 2;
        this.y = gc.height / 2;
        this.vx = 0;
        this.vy = 0;
    }

    this.move = function () {
        this.x += this.vx;
        this.y += this.vy;
        this.handleScreenWrap();
    }

    this.handleScreenWrap = function () {
        if (this.x < 0)
            this.x = gc.width;
        else if (this.x > gc.width)
            this.x = 0;
        else if (this.y < 0)
            this.y = gc.height;
        else if (this.y > gc.height)
            this.y = 0;
    }
}
