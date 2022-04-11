
#define LMB D1 //left motor backwards.
#define RMB D2 //right motor backwards.
#define LMF D3 //left motor fowards.
#define RMF D4 //right motor fowards.

int linesensor = A0; //line sensor.
int TRIG = D6;    //trigger pin. 
int ECHO = D7;    //echo pin.
float duration_us, distance_cm;

void setup() 
{
  // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(TRIG, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO, INPUT);
  
  pinMode(LMF, OUTPUT); //left motor fowards output
  pinMode(RMF, OUTPUT); //right motor fowards output
  pinMode(LMB, OUTPUT); //left motor backwards output
  pinMode(RMB, OUTPUT); //right motor backwards output
  //LMF = left motor fowards.
  //RMF = right motor fowards.
  //LMB = left motor backwards.
  //RMB = right motor backwards.
  delay(5000); //5 seccond start
}


void loop() {
  //10-microsecond pulse to TRIG pin
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  
 int QRE_Value = analogRead(linesensor); //line sensor QRE value.


//safty stop function if robot is off the ground.
  if(QRE_Value > 500)
  {
    Serial.print("Stopping all motors");
    digitalWrite(LMF,LOW); //setting left motor front to low.
    digitalWrite(RMF,LOW); //setting right motor front to low.
    digitalWrite(LMB,LOW); //setting left motor back to low.
    digitalWrite(RMB,LOW); //setting right motor back to low
    delay(500);            //delay of half a seccond.
  }

//locating target function.
 if ((distance_cm > 20) && (QRE_Value < 500))
  {
    Serial.println("Locating Target"); 
    digitalWrite(LMF,HIGH); //setting left motor front to high.
    digitalWrite(RMB,HIGH); //setting right motor back to high.
    delay(80);              //delay of 80 micro seccond.
    digitalWrite(LMF,LOW);  //setting left motor front to low.
    digitalWrite(RMB,LOW);  //setting right motor back to low.
    delay(80);
  }

//moving fowards when target detected function.
  if ((distance_cm < 20) && (QRE_Value < 500))
  {
    Serial.println("Moving forward"); 
    digitalWrite(LMF,HIGH); //setting left motor front to high.
    digitalWrite(RMF,HIGH); //setting right motor front to high.
    delay(80);
    digitalWrite(LMF,LOW); //setting left motor front to low.
    digitalWrite(RMF,LOW); //setting right motor front to low.
    delay(80);
    digitalWrite(RMF,HIGH); //setting right motor front to high.
    digitalWrite(LMF,HIGH); //setting left motor front to high.
    delay(80);
    digitalWrite(RMF,LOW); //setting right motor front to low.
    digitalWrite(LMF,LOW); //setting left motor front to low.
    delay(80);
   }

//-Debugging-
 //-Ultrasonic sensor-
   //Serial.print("distance: ");
   //Serial.print(distance_cm);
   //Serial.println(" cm");
 //-Line sensor-
   //Serial.print("Floor distance: ");
   //Serial.println(QRE_Value);

}
