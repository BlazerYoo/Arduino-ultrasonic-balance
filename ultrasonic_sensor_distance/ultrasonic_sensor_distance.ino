/**
 * Get distance from HC-SR04 ultrasonic sensor 
 * Credits:
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 */

// define the pins that Trig and Echo
const int trigPin = 2; 
const int echoPin = 3;
// declare floats; the length of the sound wave and how far away the object is
float duration, distance;

/*
 * declare the Trig pin as an output,
 * the Echo pin as an input,
 * and start Serial communication
 */
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 
 duration = pulseIn(echoPin, HIGH);
 distance = (duration*0.0343)/2; // speed of sound: .0343 c/μS, 2 sound travels to and back

 Serial.print("Distance: ");
 Serial.print(distance);
 Serial.println(" cm");
 delay(1);
}
