#define MotorFR 2
#define SpeedFR 3

#define MotorFL 4 
#define SpeedFL 5

#define MotorBR 7 
#define SpeedBR 6

#define MotorBL 8
#define SpeedBL 9

#include <math.h>

float rad;
float maxV;
float v1;
float v2;

// Adjust for desired maximum speed
float maxSpeed = 75; 
float frequency = 0.20;

int speed=35;
int count =0;

void setup(){
  pinMode(MotorFR, OUTPUT);
  pinMode(SpeedFR, OUTPUT);

  pinMode(MotorFL, OUTPUT);
  pinMode(SpeedFL, OUTPUT);

  pinMode(MotorBR, OUTPUT);
  pinMode(SpeedBR, OUTPUT);

  pinMode(MotorBL, OUTPUT);
  pinMode(SpeedBL, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  
  if(Serial.available() > 0){ 
    t = Serial.read(); 
    Serial.println(t);
    //adjustSpeed();
    if(t=='J'){
      adjustSpeed();
    }
    if(t=='F'){ 
      forward();
    }
    if(t=='G'){ 
      backward();
    }
    if(t=='L'){ 
      left();
    }
    if(t=='R'){ 
      right();
    }
    if(t=='X'){ 
      stop();
    }
    if(t=='Y'){ 

    while (t !='X'){
    for (int i = 90; i >=0; i-=10) {
    moveSineWave(i);}
    for (int i = 360; i >=270; i-=10) {
    moveSineWave(i);
    }
    }
    for (int i = 270; i <=360; i+=5) {
    moveSineWave(i);}
    for (int i = 0; i <=90; i+=5) {
    moveSineWave(i);}
    }
   
    if (t == 'N') {
      if (count == 0) {
        rotateL();
        count = 1;
      } 
      else {
        stop();
        count = 0;
      }
    }
    if (t == 'M') {
      if (count == 0) {
        rotateR();
        count = 1;
      } 
      else {
        stop();
        count = 0;
      }
    }
  }
  } 

// The Back-Left motor is connected opposite to convention, hence the code was modified accordingly

void forward(){
  analogWrite(SpeedFR,speed);
  analogWrite(SpeedFL,speed);
  analogWrite(SpeedBR,speed);
  analogWrite(SpeedBL,speed);

  digitalWrite(MotorFR,LOW);
  digitalWrite(MotorFL,LOW);
  digitalWrite(MotorBR,LOW);
  digitalWrite(MotorBL,HIGH);

  delay(1000);
  }


void backward(){
  analogWrite(SpeedFR,speed);
  analogWrite(SpeedFL,speed);
  analogWrite(SpeedBR,speed);
  analogWrite(SpeedBL,speed);

  digitalWrite(MotorFR,HIGH);
  digitalWrite(MotorFL,HIGH);
  digitalWrite(MotorBR,HIGH);
  digitalWrite(MotorBL,LOW);

  delay(1000);
  }


void left(){
  analogWrite(SpeedFR,speed);
  analogWrite(SpeedFL,speed);
  analogWrite(SpeedBR,speed);
  analogWrite(SpeedBL,speed);

  digitalWrite(MotorFR,LOW);
  digitalWrite(MotorFL,HIGH);
  digitalWrite(MotorBR,HIGH);
  digitalWrite(MotorBL,HIGH);

  delay(1000);
  }


void right(){
  analogWrite(SpeedFR,speed);
  analogWrite(SpeedFL,speed);
  analogWrite(SpeedBR,speed);
  analogWrite(SpeedBL,speed);

  digitalWrite(MotorFR,HIGH);
  digitalWrite(MotorFL,LOW);
  digitalWrite(MotorBR,LOW);
  digitalWrite(MotorBL,LOW);

  delay(1000);
  }


void rotateR(){
  analogWrite(SpeedFR,speed);
  analogWrite(SpeedFL,speed);
  analogWrite(SpeedBR,speed);
  analogWrite(SpeedBL,speed);

  digitalWrite(MotorFR,HIGH);
  digitalWrite(MotorFL,LOW);
  digitalWrite(MotorBR,HIGH);
  digitalWrite(MotorBL,HIGH);

  delay(200);
  }


void rotateL(){
  analogWrite(SpeedFR,speed);
  analogWrite(SpeedFL,speed);
  analogWrite(SpeedBR,speed);
  analogWrite(SpeedBL,speed);

  digitalWrite(MotorFR,LOW);
  digitalWrite(MotorFL,HIGH);
  digitalWrite(MotorBR,LOW);
  digitalWrite(MotorBL,LOW);
  }


void stop(){
  analogWrite(SpeedFR,0);
  analogWrite(SpeedFL,0);
  analogWrite(SpeedBR,0);
  analogWrite(SpeedBL,0);
}



void anyangle(float angle){

  rad = angle * M_PI / 180.0;
  maxV= 75;
  v1 = maxV *(sin(rad)+cos(rad))/2.0;
  v2 = maxV *(sin(rad)-cos(rad))/2.0;

  analogWrite(SpeedFR,abs(v2));
  analogWrite(SpeedFL,abs(v1));
  analogWrite(SpeedBR,abs(v1));
  analogWrite(SpeedBL,abs(v2));

  
  //to determine direction/ quadrant corresponding to angle 

  if ((angle>0.0 and angle < 45.0) or (angle>315.0 and angle<360.0)){
  digitalWrite(MotorFR,HIGH);
  digitalWrite(MotorFL,LOW);
  digitalWrite(MotorBR,LOW);
  digitalWrite(MotorBL,LOW);
  }

  if (angle > 45.0 and angle <135.0){
  digitalWrite(MotorFR,LOW);
  digitalWrite(MotorFL,LOW);
  digitalWrite(MotorBR,LOW);
  digitalWrite(MotorBL,HIGH);
  }


  if (angle > 135.0 and angle <225.0){
  digitalWrite(MotorFR,LOW);
  digitalWrite(MotorFL,HIGH);
  digitalWrite(MotorBR,HIGH);
  digitalWrite(MotorBL,HIGH);
  }
  
  if (angle > 225.0 and angle <315.0){
  digitalWrite(MotorFR,HIGH);
  digitalWrite(MotorFL,HIGH);
  digitalWrite(MotorBR,HIGH);
  digitalWrite(MotorBL,LOW);
  }
 
  }

  void moveSineWave(float amplitude, float freq) {
  unsigned long currentTime = millis();
  float angle = currentTime * 2 * PI * freq / 1000.0; // Convert milliseconds to seconds

  // Calculate sine wave components for each wheel (considering mechanum wheel directions)
  float v1 = amplitude * (sin(angle) + cos(angle)) / 2.0;
  float v2 = amplitude * (sin(angle) - cos(angle)) / 2.0;

  // Set motor speeds and directions based on calculated components
  analogWrite(SpeedFR, abs(v2));
  analogWrite(SpeedFL, abs(v1));
  analogWrite(SpeedBR, abs(v1));
  analogWrite(SpeedBL, abs(v2));
  
  // Determine direction of rotation of wheel based on sign of velocity
  digitalWrite(MotorFR, v2 > 0 ? LOW : HIGH);
  digitalWrite(MotorFL, v1 > 0 ? LOW : HIGH);
  digitalWrite(MotorBR, v1 > 0 ? HIGH : LOW);
  digitalWrite(MotorBL, v2 > 0 ? LOW : HIGH);
  delay(500);
}