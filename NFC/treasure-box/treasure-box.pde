import processing.serial.*; 
Serial myPort; // create instance of serial lib

PFont myFont;
PImage closedChest;
PImage openChest;
String second = "";
int counter = 11;
int time;

boolean open = false;
void setup(){

  frameRate(1);
  size(1000, 600);
  
  openChest = loadImage("open.png");
  closedChest = loadImage("closed.png");
  
  myPort = new Serial(this, Serial.list()[3], 115200); // instatiate the object

  // generate a serialEvent() when you get a newline character:
  //myPort.bufferUntil('\n');
  
  //create and load font
  myFont = createFont("DS-Digital", 128);
  textFont(myFont);
  background(0);

}

void draw(){
  //time = millis();
  //checktime(time);
    background(0);

   if (counter > 0 && open == false){
     image(closedChest, width/2, 300);
     counter--;
     second = str(counter);
    textAlign(CENTER, CENTER);
    fill(255);
    text(second, width/2, 100);
   }else if(counter <= 0 && open == false){
     textSize(72); 
     text("YOU'RE A LOSER!", width/2, 100);
     image(closedChest, width/2, 300);
   } else if( counter > 0 && open == true){
     textSize(72);
     text("YOU'RE AMAZING! YOU WIN!", width/2, 100);
     image(openChest, width/2, 300);
   }
   

    //println(millis());
}

void serialEvent(Serial myPort) {
  // get the ASCII string by reading from the port until a newline char is reached
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) { // if you have stuff in the string
    // trim off any whitespace:
    inString = trim(inString);
    
    if (inString.equals("A")){
      //do something
      counter +=5;
    }else if(inString.equals("B")){
      //do something
      counter -= 5;
    }else if(inString.equals("C")){
      //do something
      open = true;
    }
  }
  myPort.write("A");  //ask for more  data
}

//void checktime(int time){
//     if (time % 1000 == 0){
//     counter--;
//   }
//}