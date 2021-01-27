
// define front and back trig echo pins
const int trigPinF = 2; 
const int echoPinF = 3;
const int trigPinB = 4; 
const int echoPinB = 5;
// declare floats; the length of the sound wave and how far away the object is
float durationF, distanceF, durationB, distanceB, difference;

#define speedPinR 9    //  RIGHT PWM pin connect MODEL-X ENA
#define RightMotorDirPin1  12    //Right Motor direction pin 1 to MODEL-X IN1 
#define RightMotorDirPin2  11    //Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6    // Left PWM pin connect MODEL-X ENB
#define LeftMotorDirPin1  7    //Left Motor direction pin 1 to MODEL-X IN3 
#define LeftMotorDirPin2  8   //Left Motor direction pin 1 to MODEL-X IN4 

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinF, OUTPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(echoPinB, INPUT);
  Serial.begin(9600);
  
  pinMode(RightMotorDirPin1, OUTPUT);
  pinMode(RightMotorDirPin2, OUTPUT);
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT);
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
  // put your main code here, to run repeatedly:
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
  difference = distanceF - distanceB;
  Serial.println(difference);
  delay(1);
  
  while (difference > 0.3) {
    if (difference > 0) {
      analogWrite(RightMotorDirPin1, abs(difference)*50);
      analogWrite(RightMotorDirPin2, abs(difference)*50);
      analogWrite(LeftMotorDirPin1, -abs(difference)*50);
      analogWrite(LeftMotorDirPin1, -abs(difference)*50);
    } else {
      analogWrite(RightMotorDirPin1, -abs(difference)*50);
      analogWrite(RightMotorDirPin2, -abs(difference)*50);
      analogWrite(LeftMotorDirPin1, abs(difference)*50);
      analogWrite(LeftMotorDirPin1, abs(difference)*50);
    }
  }
}
