let playerPic = document.createElement("img");
let UFOPic = document.createElement("img");
var trackPics = [];
let picsToLoad = 0;

function loadImages() {
	var imageList = [
		{varName: playerPic, theFile: "player1.png"},
		{varName: UFOPic, theFile: "ufo.png"},
	];
	picsToLoad = imageList.length;
	for (var i = 0; i < imageList.length; i++) {
		if (imageList[i].trackType != undefined) {
			loadImageForTrackCode(imageList[i].trackType, imageList[i].theFile);
		} else {
			beginLoadingImage(imageList[i].varName, imageList[i].theFile);
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

function loadImageForTrackCode(trackCode, fileName) {
	trackPics[trackCode] = document.createElement("img");
	beginLoadingImage(trackPics[trackCode], fileName);
}
