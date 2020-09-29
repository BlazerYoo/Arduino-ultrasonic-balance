/**
 * Display difference in front and back ultrasonic sensor distances
 */

// define front and bacn trig echo pins
const int trigPinF = 2; 
const int echoPinF = 3;
const int trigPinB = 4; 
const int echoPinB = 5;
// declare floats; the length of the sound wave and how far away the object is
float durationF, distanceF, durationB, distanceB, difference;

/*
 * declare the trig pins as an output,
 * the echo pins as an input,
 * and start Serial communication
 */
void setup() {
  pinMode(trigPinF, OUTPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(echoPinB, INPUT);
  Serial.begin(9600);
}

/* 
 * set trigPin for 2 μS to ensure that pins is low first
 * set high for 10 μS (send out 8 cycle sonic burst)
 * set to low again
 * wait for the pin to go to starting state, starts timing, and then stops timing when it switches to the other state
 * start timing when the Echo pin goes high
 * store the time (μS) in the duration variable
 */
void loop() { 
 digitalWrite(trigPinF, LOW);
 digitalWrite(trigPinB, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPinF, HIGH);
 digitalWrite(trigPinB, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinF, LOW);
 digitalWrite(trigPinB, LOW);
 
 durationF = pulseIn(echoPinF, HIGH);
 durationB = pulseIn(echoPinB, HIGH);
 
 distanceF = (durationF*0.0343)/2; // speed of sound: .0343 c/μS, 2 sound travels to and back
 distanceB = (durationB*0.0343)/2;

 difference = distanceF - distanceB
 Serial.println(difference);
 delay(1);
}
