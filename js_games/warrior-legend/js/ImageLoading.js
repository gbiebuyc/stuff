let playerPic = document.createElement("img");
var tilePics = [];
let picsToLoad = 0;

function loadImages() {
    var imageList = [
        { varName: playerPic, theFile: "warrior.png" },

        { trackType: TILE_GROUND, theFile: "world_ground.png" },
        { trackType: TILE_WALL, theFile: "world_wall.png" },
        { trackType: TILE_GOAL, theFile: "world_goal.png" },
        { trackType: TILE_KEY, theFile: "world_key.png" },
        { trackType: TILE_DOOR, theFile: "world_door.png" }
    ];
    picsToLoad = imageList.length;
    for (var i = 0; i < imageList.length; i++) {
        if (imageList[i].trackType != undefined) {
            loadImageForTileCode(imageList[i].trackType,
                imageList[i].theFile);
        } else {
            beginLoadingImage(imageList[i].varName,
                imageList[i].theFile);
        }
    }
}

function beginLoadingImage(imgVar, filename) {
    imgVar.onload = countLoadedImageAndLaunchIfReady;
    imgVar.src = "images/" + filename;
}

function countLoadedImageAndLaunchIfReady() {
    picsToLoad--;
    if (picsToLoad == 0)
        loadingDoneSoStartGame();
}

function loadImageForTileCode(tileCode, fileName) {
    tilePics[tileCode] = document.createElement("img");
    beginLoadingImage(tilePics[tileCode], fileName);
}