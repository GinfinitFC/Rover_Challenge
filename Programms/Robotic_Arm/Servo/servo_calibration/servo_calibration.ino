//Control servo motor MG90S
//Giancarlo Franco Carrillo

//library
#include<Servo.h>

//create object (can be many)
Servo myServo;
int angle;

Servo myServo2;
int angle2;
////////////////////////////////

void setup() {
  //calibrate motor sequence
  //conection to myServo to digital pin 3 arduino
  myServo.attach(3);
  myServo2.attach(4);
  //set home
  myServo.write(0);
  myServo2.write(0);
  delay(2000);
  //set to middle
  myServo.write(90);
  myServo2.write(90);
  delay(2000);
  //set to end
  myServo.write(180);
  myServo2.write(180);
  delay(5000);

  Serial.begin(9600);
}

void loop() {
  //move servo1 edge from 0 to 180 while the other moves mirror 
  for(angle=0, angle2=180; angle<=180,angle2>=0; angle+=2,angle2-=2){
    myServo.write(angle);
    myServo2.write(angle2);
    Serial.println(myServo.read());//print to serial position
    delay(20);//debounce
  }

   //move servo1 edge from 180 to 0 while second moves mirror
  for(angle=180,angle2=0; angle>=0,angle2<=180; angle-=2,angle2+=2){
    myServo.write(angle);
    myServo2.write(angle2);
    Serial.println(myServo.read());//print to serial position
    delay(20);//debounce
  }

}
