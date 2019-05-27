import processing.serial.*; //import library for serial communication
Serial myPort; //set up serial object and variables
PFont font;
String Input;
String FPS;
String RPS;
Float MaxFPS = 0.0; //initialize values at zero
Float MaxRPS = 0.0;
String data[];

void setup(){
  fullScreen(); //set the program as fullscreen
  String portName = Serial.list()[0]; //this is where you might need to change the 0 to a different port
  myPort = new Serial(this,portName,9600);
  font = createFont("Unispace", 120, true); //if you don't have Unispace use "Arial" instead
  myPort.clear();
  println(myPort.available());
  Input = "0.0,0.0 "; //initialize readings as 0;
  data = split(Input, ','); 
}

void draw()
{
  //get the data from the serial port
  if(myPort.available() > 0) {
  Input = myPort.readStringUntil(10); //reads the string until a new line is used
  data = split(Input, ','); //splits the string
  }
  
  FPS = data[0]; //sets teh FPS and RPS as parts of data
  RPS = data[1];
  background(0); //sets background to black
  textFont(font);
  textAlign(CENTER); //centers text
  text("Chronograph V1.0", width/2, height*.18); //outputs title
  fill(0,255,0); // sets text color to green
  //outputs readings for FPS and RPS
  if (FPS!= null){
    FPS = FPS.replace("\n", " ");
    textAlign(CENTER);
    text(FPS + " FPS", width/2, height*.36);
  }
  if (RPS!= null){
    RPS = RPS.replace("\n", " ");
    textAlign(CENTER);
    text(RPS + "RPS", width/2, height*.54);
  }
textAlign(CENTER);
    text("MAX FPS", .2*width, height*.72);
    textAlign(CENTER);
    text("MAX RPS", .8*width, height*.72);
if (float(RPS) > MaxRPS){
  MaxRPS = float(RPS);
}
if (float(FPS) > MaxFPS){
  MaxFPS = float(FPS);
}
//outputs the Max values, important mostly for RPS. This value was found to be erratic if the darts are off center.
textAlign(CENTER);
    text(str(MaxFPS), .2*width, height*.9);
    textAlign(CENTER);
    text(str(MaxRPS), .8*width, height*.9);
}
//Allows reset with spacebar
void keyPressed() {
if (key == ' '){
MaxFPS = 0.0;
MaxRPS = 0.0;
Input = "0.0,0.0 ";
  data = split(Input, ',');  
}
}
