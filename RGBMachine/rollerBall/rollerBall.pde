import processing.serial.*; 
Serial group3Port;
Serial myPort; // create instance of serial lib
PImage img;

int cx=0; //x-coordinate of bouncing ball
int cy=10; //y-coordinate of bouncing ball
int r=60; //radius of bouncing ball
int vx=2; //bouncing ball's direction on the x-axis
int vy=3; //bouncing ball's direction on the y-axis

//Set up variable for speed of ellipse moving around sketch edge.
int speed=1;

boolean start = false;

//Allows ellipse moving around sketch edge to change direction depending on position.
int state=0;

boolean reachRight = false;

void setup() {

  print(Serial.list());
  myPort = new Serial(this, Serial.list()[7], 9600); // instatiate the object
  group3Port = new Serial(this, Serial.list()[6], 9600);
  //// generate a serialEvent() when you get a newline character:
  group3Port.bufferUntil('\n');

  size(700, 500);
  smooth();
  
  img = loadImage("ball.png");

}

void draw() {
  //background(85,26,139);
  background(255);
  noStroke();
  //Fill bouncing ball as black.
  fill(255,255,255);
  //Change ellipse mode.
  ellipseMode(CENTER);
  //Draw bouncing ball with variables.
  image(img, cx, cy, r+10, r);
  //ellipse(cx, cy, r, r);
  if (start){
    
    //Set cy variable to move across the sketch
    cy = cy + vy;
    
    //Set condition to bounce ball once it reaches sketch edge.
    if((cy>height-40)||(cy<0)){
      vy = vy * -1;
    }
    //Set cx variable to bouncing ball move across the sketch.
    cx = cx + vx;
    
    //Set condition to bounce ball once it reaches sketch edge.
    if((cx > width - 10)||(cx < 0)){
      vx = vx * -1;
    }
    
    
    if (cx > width-r){
      cx = width;
      vy = 0;
      reachRight = true;
    }
    
    if (reachRight){
      myPort.write("A");
    }
  }
  
}

void serialEvent(Serial gp3Port){
  String inString = gp3Port.readStringUntil('\n');
  if (inString != null){
    inString = trim(inString);
    print(inString);
    if (inString.equals("1")){
      start = false;
    }
  }
}