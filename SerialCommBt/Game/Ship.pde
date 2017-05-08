class Ship {
  int xPos;
  int yPos;
  int shipNo;

  int shieldSize;
  PImage img;
  boolean show;

  Ship(int no) { // ship constructor
    shipNo = no+1;
    xPos = width/2;
    yPos = height - 100;
    img = loadImage("spaceship.png");
    shieldSize = 0;
    show = true;
  }

  void update(int[] delta) {
    if (delta[0] == 1){      
      xPos += delta[1];
      yPos += delta[2];
  }
}

  void render() {
    if (show){   
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
  
      image(img, xPos, yPos, 30*shipNo, 30*shipNo);
    }
  }
  
  void disappear(){
    show = false;
  }
}