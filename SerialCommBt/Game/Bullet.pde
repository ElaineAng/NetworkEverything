class Bullet{
  int xPos;
  int yPos;
  boolean show;
  
  Bullet(int x_pos, int y_pos){
    xPos = x_pos;
    yPos = y_pos;
    show = true;
  }
  
  void update(int _deltY){
    yPos -= _deltY;
  }
  
  void disappear(){
    show = false;
  }
  
  void render(){
    if (show){
      fill(0);
      ellipse(xPos, yPos, 5, 5);     
     }
  }  
}