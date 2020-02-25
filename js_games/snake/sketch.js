let GRID_SIZE = 20;
let SQUARE_SIZE = 20;
let CANVAS_SIZE = GRID_SIZE * SQUARE_SIZE;
let snake;
let move;
let fruit;
let hasEaten;
let speed;

function resetSketch() {
  snake = [];
  move = {x: 1, y: 0};
  fruit = newFruit();
  hasEaten = false;
  speed = 4;
  frameRate(speed);
  center = Math.floor(GRID_SIZE / 2);
  snake.push({x: center, y: center});
}

function setup() {
  createCanvas(CANVAS_SIZE, CANVAS_SIZE);
  resetSketch();
}

function newFruit() {
  let x = Math.floor(Math.random() * GRID_SIZE);
  let y = Math.floor(Math.random() * GRID_SIZE);
  return {x: x, y: y};
}

function checkFruit() {
  if (snake[snake.length - 1].x != fruit.x ||
      snake[snake.length - 1].y != fruit.y)
    return;
  hasEaten = true;
  fruit = newFruit();
  speed += 0.5;
  frameRate(speed);
}

function drawSquare(x, y) {
  square(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE);
}

function advanceSnake() {
  let x = snake[snake.length - 1].x + move.x;
  let y = snake[snake.length - 1].y + move.y;
  x = ((x % GRID_SIZE) + GRID_SIZE) % GRID_SIZE;
  y = ((y % GRID_SIZE) + GRID_SIZE) % GRID_SIZE;
  if (snake.some(elem => elem.x == x && elem.y == y)) {
    console.log('Game over');
    resetSketch();
  }
  if (!hasEaten)
    snake.shift();
  snake.push({x: x, y: y});
  hasEaten = false;
}

function keyPressed() {
  if (keyCode === LEFT_ARROW) {
    move = {x: -1, y:  0};
  } else if (keyCode === RIGHT_ARROW) {
    move = {x:  1, y:  0};
  } else if (keyCode === UP_ARROW) {
    move = {x:  0, y: -1};
  } else if (keyCode === DOWN_ARROW) {
    move = {x:  0, y:  1};
  }
}

function draw() {
  background(220);
  advanceSnake();
  checkFruit();
  fill('white');
  snake.forEach(elem => {
    drawSquare(elem.x, elem.y);
  });
  fill('red');
  drawSquare(fruit.x, fruit.y);
}