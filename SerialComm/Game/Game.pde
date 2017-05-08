//Serial Communication
import processing.serial.*;   // import serial lib
Serial myPort; // create instance of serial lib
String sensorValue;

Ship myShip1; // create a spaceship
Ship myShip2; // create another spaceship

int xChange, yChange; // variables for the ship1
int increment = 1; // variable to change the rate of movement

Star[] stars; // array of stars
int starNum = 20; // number of stars

void setup() {

  //serial communication
  myPort = new Serial(this, Serial.list()[0], 9600); // instatiate the object
  // new serial object (named "myPort") that will run in this" sketch, which is physicallon on port X
  // and communicates at 9600 baud

  // generate a serialEvent() when you get a newline character:
  myPort.bufferUntil('\n');

  size(800, 600);

  
  myShip1 = new Ship(); // instantiate the ship
  myShip2 = new Ship();
  
  stars = new Star[starNum]; // new array of stars

  for (int x=0; x<starNum; x++) {
    stars[x] = new Star(); // instantiate the stars
  }
}

void draw() {
  background(0); // clear the background

  // directions
  String words = "use the arrows to move, 1-9 for ship speed";
  fill(255);
  text(words, 10, 30);

  // loop through all the stars
  for (int x=0; x< starNum; x++) {
    stars[x].update(); // update their position
    stars[x].collisionCheck(myShip1.xPos, myShip1.yPos); // check if colliding with the ship
    stars[x].collisionCheck(myShip2.xPos, myShip2.yPos);
    stars[x].render(); // draw the stars
  }

  myShip1.update(x1Change, y1Change); // update the ship's position & shield size
  myShip1.render(); // render the ship

}


void serialEvent(Serial myPort) {
  // get the ASCII string by reading from the port until a newline char is reached
  String inString = myPort.readStringUntil('\n');

  if (inString != null) { // if you have stuff in the string
    // trim off any whitespace:
    inString = trim(inString);
    sensorValue = inString;

    // split the string at the commas and convert the
    // resulting substrings into your array:

    if (sensorValue.equals("u")) {
      yChange = increment * -1;
    } else if (sensorValue.equals("d")) {
      yChange = increment;
    } else if (sensorValue.equals("l")) {
      xChange = increment * -1;
    } else if (sensorValue.equals("r")) {
      xChange = increment;
    } else {
      increment = int(sensorValue)/128 + 1;
      if (xChange != 0) {
        xChange = abs(xChange)/xChange * increment;
      }
      if (yChange != 0) {
        yChange = abs(yChange)/yChange * increment;
      }
    }
  }
  myPort.write("A");  //ask for more game data
}


//************** Star class
class Star {
  float xPos, yPos, starSize, speed; // variables
  boolean collision; // check for collision

  // star constructor
  Star() { // initial state
    speed = random(1, 10);
    starSize = random(10, 100);
    xPos = random(0, width);
    yPos = random(100, width) * -1;
    collision = false;
  }

  void update() {  // update star position

    yPos += speed;

    if (yPos > height+starSize/2) {
      yPos = random(100, width) * -1;
      speed = random(1, 10);
      starSize = random(10, 50);
      xPos = random(0, width);
    }
  }

  void collisionCheck(int _x, int _y) { // check for a collision

    int shipX = _x;
    int shipY = _y;

    float dx = shipX - xPos;
    float dy = shipY - yPos;
    float d = sqrt(sq(dx)+sq(dy)); // distance between star and ship

    if (d < starSize/2 + 10) { // if distance is less than the radius of the star & ship
      collision = !collision;  // there's a crash
    }
  }

  void render() {
    // if there's no collision
    if (!collision) {
      noStroke();
      fill(220, 160, 0);
      ellipse(xPos, yPos, starSize, starSize);
    } else { // if there is a colliison, supernova
      strokeWeight(5);
      stroke(255);
      fill(220, 100, 0);
      ellipse(xPos, yPos, starSize*1.5, starSize*1.5);
      collision = !collision; // reset the collison state for the next iteration
    }
  }
}



//************** Ship class
class Ship {
  int xPos;
  int yPos;
  int shieldSize;

  Ship() { // ship constructor
    xPos = width/2;
    yPos = height - 100;
    shieldSize = 0;
  }

  void update(int _xDelta, int _yDelta) {
    xPos += _xDelta;
    yPos += _yDelta;
  }

  void render() {
    if (yPos > height-10) {
      yPos = height-10;
    }
    if (yPos < height-500) {
      yPos = height-500;
    }

    if (xPos > width-10) {
      xPos = width-10;
    }
    if (xPos < 10) {
      xPos = 10;
    }

    noStroke();
    fill(180, 10, 200);
    rectMode(CENTER);
    rect(xPos, yPos, 20, 20);
  }
}