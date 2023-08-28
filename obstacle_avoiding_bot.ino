#define trigpin_front A5
#define echopin_front 2
#define trigpin_left A4
#define echopin_left 3
#define trigpin_right A2
#define echopin_right 5

#define ENA 10
#define ENB 11
#define motor_A_pos  6     //left wheel
#define motor_A_neg  7
#define motor_B_pos  8     //right wheel
#define motor_B_neg  9

const double threshold = 20;

double duration_front;
double distance_front;
double duration_left;
double distance_left;
double duration_right;
double distance_right;

void test_left()
{
  digitalWrite(trigpin_left,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin_left, LOW);

  duration_left = (double)(pulseIn(echopin_left, HIGH));
  distance_left = duration_left * (0.0340 / 2.0000) + 1.0000;

   Serial.println(distance_left);
}

void test_right()
{
  digitalWrite(trigpin_right,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin_right, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trigpin_right, LOW);

  duration_right = (double)(pulseIn(echopin_right, HIGH));
  distance_right = duration_right * (0.0340 / 2.0000) + 1.0000;

  Serial.println(distance_right);
  
}

void setup() {
  Serial.begin(9600);
  pinMode(trigpin_front,OUTPUT);
  pinMode(trigpin_left,OUTPUT);
  pinMode(trigpin_right,OUTPUT);
  pinMode(echopin_front,INPUT);
  pinMode(echopin_left,INPUT);
  pinMode(echopin_right,INPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(motor_A_pos,OUTPUT);
  pinMode(motor_A_neg,OUTPUT);
  pinMode(motor_B_pos,OUTPUT);
  pinMode(motor_B_neg,OUTPUT);
}

void loop() {
  digitalWrite(trigpin_front,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin_front, LOW);
  analogWrite(ENA,100);
  analogWrite(ENB,90);
 
 
  duration_front = (double)(pulseIn(echopin_front, HIGH));
  distance_front = duration_front * (0.0340 / 2.0000) + 1.0000;
  
  Serial.println(distance_front);
  test_left();
  test_right();
  
  if(distance_front>25 && distance_right>10 && distance_left>10){
    digitalWrite(motor_A_pos,HIGH);
    digitalWrite(motor_B_pos,HIGH);
    digitalWrite(motor_A_neg,LOW);
    digitalWrite(motor_B_neg,LOW);
    Serial.println("Front ");
    delay(10);
  }

  else if(distance_front>25 && distance_right<10 && distance_left>10){
    digitalWrite(motor_A_pos,LOW);
    digitalWrite(motor_B_pos,HIGH);
    digitalWrite(motor_A_neg,LOW);
    digitalWrite(motor_B_neg,LOW);
    Serial.println("Front left turn ");
    delay(250);
  }

  else if(distance_front>25 && distance_right>10 && distance_left<10){
    digitalWrite(motor_A_pos,HIGH);
    digitalWrite(motor_B_pos,LOW);
    digitalWrite(motor_A_neg,LOW);
    digitalWrite(motor_B_neg,LOW);
    Serial.println("Front right turn ");
    delay(250);
  }
  
  else{
    digitalWrite(motor_A_pos,LOW);
    digitalWrite(motor_B_pos,LOW);
    digitalWrite(motor_A_neg,LOW);
    digitalWrite(motor_B_neg,LOW);
    delay(500);
    
    if(distance_left>threshold && distance_right<threshold){
    digitalWrite(motor_A_pos,LOW);
    digitalWrite(motor_B_pos,HIGH);
    digitalWrite(motor_A_neg,LOW);
    digitalWrite(motor_B_neg,LOW);
    Serial.println("LEFT TURN 1");
    delay(500);
    }
    else if(distance_left<threshold && distance_right>threshold){
    digitalWrite(motor_B_pos,LOW);
    digitalWrite(motor_A_pos,HIGH);
    digitalWrite(motor_B_neg,LOW);
    digitalWrite(motor_A_neg,LOW);
    Serial.println("RIGHT TURN 1");
    delay(500);
    }
    else if(distance_left>threshold && distance_right>threshold){
      if(distance_left>=distance_right){
    digitalWrite(motor_A_pos,LOW);
    digitalWrite(motor_B_pos,HIGH);
    digitalWrite(motor_A_neg,LOW);
    digitalWrite(motor_B_neg,LOW);
    Serial.println("LEFT TURN 2");
    delay(500);
      }
      if(distance_left<distance_right){
    digitalWrite(motor_B_pos,LOW);
    digitalWrite(motor_A_pos,HIGH);
    digitalWrite(motor_B_neg,LOW);
    digitalWrite(motor_A_neg,LOW);
    Serial.println("RIGHT TURN 2");
    delay(500);
      }
    }
    else if(distance_left<threshold && distance_right < threshold){
    digitalWrite(motor_A_pos,LOW);
    digitalWrite(motor_B_pos,LOW);
    digitalWrite(motor_A_neg,HIGH);
    digitalWrite(motor_B_neg,HIGH);
    Serial.println("BACK");
    delay(1000);
    }
  }
}