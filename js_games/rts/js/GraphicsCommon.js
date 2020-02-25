function drawBitmapCenteredAtLocationWithRotation(
    graphic, atX, atY, withAngle) {
    ctx.save();
    ctx.translate(atX, atY);
    ctx.rotate(withAngle);
    ctx.drawImage(graphic, -graphic.width / 2, -graphic.height / 2);
    ctx.restore();
}

function colorCircle(x, y, r, c) {
    ctx.fillStyle = c;
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2, true);
    ctx.fill();
}

function colorRect(x, y, w, h, c) {
    ctx.fillStyle = c;
    ctx.fillRect(x, y, w, h);
}

function coloredOutlineRectCornerToCorner(corner1X, corner1Y, corner2X, corner2Y, lineColor) {
    ctx.strokeStyle = lineColor;
    ctx.beginPath();
    ctx.rect(corner1X, corner1Y, corner2X - corner1X, corner2Y - corner1Y);
    ctx.stroke();
}