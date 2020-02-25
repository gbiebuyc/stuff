function drawBitmapCenteredAtLocationWithRotation(
    graphic, atX, atY, withAngle) {
    ctx.save();
    ctx.translate(atX, atY);
    ctx.rotate(withAngle);
    ctx.drawImage(graphic, -graphic.width / 2, -graphic.height / 2);
    ctx.restore();
}
