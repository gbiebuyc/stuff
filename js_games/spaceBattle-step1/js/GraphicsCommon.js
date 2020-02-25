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