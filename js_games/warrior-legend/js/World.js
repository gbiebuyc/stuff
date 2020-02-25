const TILE_W = 50;
const TILE_H = 50;
const ROOM_COLS = 16;
const ROOM_ROWS = 12;
var roomGrid =
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 5, 0, 1, 1, 1, 1,
        1, 0, 4, 0, 4, 0, 1, 0, 2, 0, 1, 0, 1, 4, 4, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 5, 1, 5, 1, 1,
        1, 1, 1, 5, 1, 1, 1, 0, 4, 0, 1, 0, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 0, 1, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1,
        1, 0, 5, 0, 5, 0, 5, 0, 3, 0, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];
const TILE_GROUND = 0;
const TILE_WALL = 1;
const TILE_PLAYER = 2;
const TILE_GOAL = 3;
const TILE_KEY = 4;
const TILE_DOOR = 5;

function tileTypeHasTransparency(tileType) {
    return (tileType == TILE_GOAL ||
        tileType == TILE_KEY ||
        tileType == TILE_DOOR);
}

function drawRoom() {
    let i = 0;
    let y = 0;
    for (let row = 0; row < ROOM_ROWS; row++) {
        let x = 0;
        for (let col = 0; col < ROOM_COLS; col++) {
            let tileType = roomGrid[i++];
            if (tileTypeHasTransparency(tileType))
                ctx.drawImage(tilePics[TILE_GROUND], x, y);
            ctx.drawImage(tilePics[tileType], x, y)
            x += TILE_W;
        }
        y += TILE_H;
    }
}

function getTileIndexAtPixelCoord(x, y) {
    let col = Math.floor(x / TILE_W);
    let row = Math.floor(y / TILE_H);
    if (col < 0 || col >= ROOM_COLS ||
        row < 0 || row >= ROOM_ROWS)
        return undefined;
    let i = roomTileToIndex(col, row);
    return (i);
}

function isWallAtTileCoord(col, row) {
    return (roomGrid[col + row * ROOM_COLS] == TILE_WALL);
}

function roomTileToIndex(x, y) {
    return (x + y * ROOM_COLS);
}