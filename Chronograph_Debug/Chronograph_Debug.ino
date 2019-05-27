/*
 This is debugging code for the cronography and allows for viewing false positives and time values.
 Feel free to modify it with improvements and please share your results!
 */
 
const int PhotoPin_1 = 2;
const int PhotoPin_2 = 3;
volatile unsigned long time1 = 0;
volatile unsigned long time2 = 0;
unsigned long time1_aux = 0;
unsigned long time2_aux = 0;
volatile int pass = 0;
double bulletspeed = 0;

void setup() {
Serial.begin(9600); //initialize serial port
attachInterrupt(digitalPinToInterrupt(PhotoPin_1),timer1,FALLING);
attachInterrupt(digitalPinToInterrupt(PhotoPin_2),timer2,FALLING);
}

void loop() {
 //first take the interrupt values and place them in new variables
 noInterrupts();
 time1_aux = time1;
 time2_aux = time2;
 interrupts();
 //Calculate the speed based on 3in sensor distance
 bulletspeed = (0.25/(time2_aux-time1_aux))*1000000;
 //output the bulletspeed and sensor timings for debugging
 //if there is no reading troubleshoot as described in the Instructable with AnalogReadSerial
 Serial.println(bulletspeed); 
  Serial.println(time1_aux); 
  Serial.println(time2_aux);
 delay(100);

}

void timer1() {
  time1 = micros();
  pass++;
}  
void timer2() {
  time2 = micros();
}
