import processing.serial.*; 
Serial myPort; // create instance of serial lib
String sensorValue;

int starNum = 20;
Star[] stars;
Ship[] ships;
ArrayList<Bullet> bullets;
int [][] changes;

int SHIP_COUNT = 2;
int increment = 1; // variable to change the rate of movement
//int total_collision = 0;

void setup() {

  //print(Serial.list());
  myPort = new Serial(this, Serial.list()[4], 9600); // instatiate the object

  // generate a serialEvent() when you get a newline character:
  myPort.bufferUntil('\n');

  size(800, 600);
  
  ships = new Ship[2];
  stars = new Star[starNum]; 
  bullets = new ArrayList<Bullet>();
  
  changes = new int[SHIP_COUNT][4];
  for (int i=0; i<SHIP_COUNT; i++){
    for (int j=0; j<4; j++){
      changes[i][j] = 0;
    }
  }

  for (int x=0; x<starNum; x++) {
    stars[x] = new Star();
  }
  
  for (int i=0; i<SHIP_COUNT; i++){
    ships[i] = new Ship(i);
  }
}

void draw() {
  
  background(255); // clear the background
  
  // loop through all the stars
  for (int x=0; x < starNum; x++) {
    stars[x].update(); // update their position
    for (int i=0; i<SHIP_COUNT; i++){
      stars[x].collisionCheck(ships[i].xPos, ships[i].yPos, 0);
    }
    if (bullets.size() > 0){   
      for (int i=0; i<bullets.size(); i++){
        stars[x].collisionCheck(bullets.get(i).xPos, bullets.get(i).yPos, 1);
      }
    }
    stars[x].render(); // draw the stars
    //total_collision += stars[x].count_collisions();
  }

  //if (total_collision > 10){
  // ships[0].disappear();
  //}
  for (int i=0; i<SHIP_COUNT; i++){
    ships[i].update(changes[i]);
    ships[i].render();
  }
  
  for (int i=0; i<bullets.size(); i++){
    bullets.get(i).update(5);
    bullets.get(i).render();
  }
}


void serialEvent(Serial myPort) {
  // get the ASCII string by reading from the port until a newline char is reached
  String inString = myPort.readStringUntil('\n');
  int speed = 0;
  
  if (inString != null) { // if you have stuff in the string
    // trim off any whitespace:
    inString = trim(inString);
    sensorValue = inString;
    
    int shipNo = int(sensorValue.substring(0, 1));
    String type = sensorValue.substring(1,2);
    
    if (sensorValue.length() > 2){
      speed = int(sensorValue.substring(2));
    }
    
    if (shipNo == 0){
      bullets.add(new Bullet(ships[1].xPos+30, ships[1].yPos));
    }
    else{
      // indicating which ship we are changing specs for
      changes[shipNo-1][0] = 1;
      
      if (type.equals("u")) {
        changes[shipNo-1][2] = increment * -1;
      } else if (type.equals("d")) {
        changes[shipNo-1][2] = increment;
      } else if (type.equals("l")) {
        changes[shipNo-1][1] = increment * -1;
      } else if (type.equals("r")) {
        changes[shipNo-1][1] = increment;
      } else if (type.equals("s")){
        increment = speed/128 + 1;
        int xChange = changes[shipNo-1][1];
        int yChange = changes[shipNo-1][2];
        if ( xChange != 0) {
          changes[shipNo-1][1] = abs(xChange)/xChange * increment;
        }
        if (yChange != 0) {
          changes[shipNo-1][2] = abs(yChange)/yChange * increment;
        }
      }
    }
  }
  myPort.write("A");  //ask for more game data
}