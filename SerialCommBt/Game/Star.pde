class Star {
  float xPos, yPos, starSize, speed; // variables
  boolean collision; // check for collision
  boolean show;
  boolean cc; //count collision
  int counter;
  
  // star constructor
  Star() { // initial state
    speed = random(1, 10);
    starSize = random(10, 100);
    xPos = random(0, width);
    yPos = random(100, width) * -1;
    collision = false;
    show = true;
    cc = true;
    counter = 0;
  }

  void update() {  // update star position

    yPos += speed;
 
    if (yPos > height+starSize/2) {
      reappear();
      yPos = random(100, width) * -1;
      speed = random(1, 10);
      starSize = random(10, 50);
      xPos = random(0, width);
    }
  }

  void collisionCheck(int _x, int _y, int type) { // 0 for spaceship, 1 for bullets

    int shipX = _x;
    int shipY = _y;

    float dx = shipX - xPos;
    float dy = shipY - yPos;
    float d = sqrt(sq(dx)+sq(dy)); // distance between star and ship

    if (d < starSize/2 + 10) { // if distance is less than the radius of the star & ship
      collision = !collision;  // there's a crash
      if (type == 1){      
        disappear();
      }
    }    
  }

  void render() {
    // if there's no collision
    aggregate();
    if (show){      
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
  
  
  void aggregate(){
    if (collision && cc){
      counter += 1;
      cc = false;
    }
    
    if (!collision){
      cc = true;
    }
  }
  
  int count_collisions(){
    return counter;
  }
  
  void disappear(){
    show = false;
  }
  
  void reappear(){
    show = true;
  }
}