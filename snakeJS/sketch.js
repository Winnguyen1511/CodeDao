// import * as sn from "./snake.js";

const canvasWidth = 400
const canvasHeight = 400
const Hard = 30;
const Medium = 20;
const Easy  = 10;
var Level = Medium;
var x, y;
var s, food;

function randomFood()
{
  let x = Math.floor(Math.random()  * canvasWidth / defaultW) * defaultW;
  let y = Math.floor(Math.random()  * canvasHeight/ defaultH) * defaultH;
  let f  = new node(x, y, [255, 0, 0]);
  return f;
}

function setup() {
    createCanvas(canvasWidth, canvasHeight);
    frameRate(Level);
    x = Math.floor(Math.random()  * canvasWidth / defaultW) * defaultW;
    y = Math.floor(Math.random()  * canvasHeight/ defaultH) * defaultH;
    s = new Snake(new node(0, 0, [255, 255, 255]));
    food  = new node(x, y, [255, 0, 0]);
    
}
function keyPressed()
{
  if(keyCode == UP_ARROW)
  {
    s.move(0, -1);
  }
  else if(keyCode == DOWN_ARROW)
  {
    s.move(0, 1);
  }
  else if(keyCode == LEFT_ARROW)
  {
    s.move(-1, 0);
  }
  else if (keyCode == RIGHT_ARROW)
  {
    s.move(1, 0);
  }
}
function update()
{
  s.x = (s.x + 10) % canvasWidth;
  s.y = (s.y + 10) % canvasHeight;
}
function draw() {
    background(0, 0, 0);
    
    if(s.eat(food) == true)
    {
      food = randomFood();
      console.log("eat\n");
    }
    if(s.update() == false)
      exit();
    s.draw();
    food.draw();
    // update();
}

