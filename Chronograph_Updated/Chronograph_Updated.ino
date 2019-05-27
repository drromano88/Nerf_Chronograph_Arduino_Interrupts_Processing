/*
This is the most up to date chronography code.
Version 1.0
Update Notes:
Only outputs values once per reading (fps)
Outputs rate of fire between past two shots (rps)
 */
 
const int PhotoPin_1 = 2;
const int PhotoPin_2 = 3;
volatile unsigned long time1 = 0;
volatile unsigned long time2 = 0;
unsigned long time1_aux = 0;
unsigned long time1_aux_prev = 0;
unsigned long time2_aux = 0;
volatile int pass = 0;
int pass_aux = 0;
int pass_pass = 0;
double bulletspeed = 0;
double shottime = 0;
double rps_calc = 0;

void setup() {
Serial.begin(9600); //initialize serial port
attachInterrupt(digitalPinToInterrupt(PhotoPin_1),timer1,FALLING);
attachInterrupt(digitalPinToInterrupt(PhotoPin_2),timer2,FALLING);
}

void loop() {
 //first take the interrupt values and place them in new variables
 noInterrupts();
 if (time1>time1_aux){
 time1_aux_prev = time1_aux;
 }
 time1_aux = time1;
 time2_aux = time2;
 pass_aux = pass;
 interrupts();
 
 if (pass_aux > pass_pass) {
  bulletspeed = (0.25/(time2_aux-time1_aux))*1000000;
  shottime = (time1_aux-time1_aux_prev);
  rps_calc = 1/(shottime/1000000);
  Serial.print(bulletspeed); 
  Serial.print(",");
  Serial.println(rps_calc);
  pass_pass++;
 }
 }


void timer1() {
  time1 = micros();
}  
void timer2() {
  time2 = micros();
  pass++;
}
