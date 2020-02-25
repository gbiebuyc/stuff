const PLAYER_MOVE_SPEED = 3.0;

function warriorClass() {
    this.x = 100;
    this.y = 100;
    this.keyHeld_North = false;
    this.keyHeld_South = false;
    this.keyHeld_West = false;
    this.keyHeld_East = false;

    this.setupControls = function (up, down, left, right) {
        this.controlKeyForNorth = up;
        this.controlKeyForSouth = down;
        this.controlKeyForWest = left;
        this.controlKeyForEast = right;
    }

    this.init = function (playerPic, name) {
        this.playerPic = playerPic;
        this.name = name;
        this.reset();
    }

    this.reset = function () {
        this.keysHeld = 0;
        for (let i = 0; i < roomGrid.length; i++) {
            if (roomGrid[i] == TILE_PLAYER) {
                let tileRow = Math.floor(i / ROOM_COLS);
                let tileCol = i % ROOM_COLS;
                this.homeX = (tileCol + 0.5) * TILE_W;
                this.homeY = (tileRow + 0.5) * TILE_H;
                roomGrid[i] = TILE_GROUND;
                break;
            }
        }
        this.x = this.homeX;
        this.y = this.homeY;
    }

    this.move = function () {
        let nextX = this.x;
        let nextY = this.y;
        if (this.keyHeld_North)
            nextY -= PLAYER_MOVE_SPEED;
        if (this.keyHeld_South)
            nextY += PLAYER_MOVE_SPEED;
        if (this.keyHeld_West)
            nextX -= PLAYER_MOVE_SPEED;
        if (this.keyHeld_East)
            nextX += PLAYER_MOVE_SPEED;
        let tileIndex = getTileIndexAtPixelCoord(nextX, nextY);
        let tileType = TILE_WALL;
        if (tileIndex != undefined)
            tileType = roomGrid[tileIndex];
        switch (tileType) {
            case TILE_GROUND:
                this.x = nextX;
                this.y = nextY;
                break;
            case TILE_GOAL:
                document.getElementById("debugText").innerHTML =
                    this.name + " won";
                this.reset();
                break;
            case TILE_DOOR:
                if (this.keysHeld > 0) {
                    this.keysHeld--;
                    document.getElementById("debugText").innerHTML =
                        "Keys: " + this.keysHeld;
                    roomGrid[tileIndex] = TILE_GROUND;
                }
                break;
            case TILE_KEY:
                this.keysHeld++;
                document.getElementById("debugText").innerHTML =
                    "Keys: " + this.keysHeld;
                roomGrid[tileIndex] = TILE_GROUND;
                break;
            case TILE_WALL:
            default:
                break;
        }
    }

    this.draw = function () {
        drawBitmapCenteredAtLocationWithRotation(
            this.playerPic, this.x, this.y, 0);
    }
}