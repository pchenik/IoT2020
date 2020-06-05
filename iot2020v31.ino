#include <Servo.h>
#include <LiquidCrystal.h>
Servo servo1;

int distanceThreshold = 0;
int cm = 0;
LiquidCrystal lcd(12, 11, 5, 13, 10, 9);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup() {
  
  Serial.begin(9600);
	
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  servo1.attach(8);
  lcd.print("IT WORKS!");
}

void turn() {
  lcd.clear();
  lcd.print("DANGER!CLOSE!");
  servo1.write(180); //ставим вал под 180
  delay(100); //ждем
}

void alarm() {
  lcd.clear();
  lcd.print("DANGER IS NEAR");
  //servo1.write(0); //ставим вал под 0
  //delay(10); //ждем 
}

void init_position() {
  lcd.clear();
  lcd.print("EVERYTHING IS OK");
  servo1.write(0); //ставим вал под 0
  delay(10); //ждем 
}

void loop()
{
  lcd.setCursor(0, 1);
  // set threshold distance to activate LEDs
  distanceThreshold = 350;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  // convert to inches by dividing by 2.54
  Serial.print(cm);
  Serial.print("\n");
  if (cm > distanceThreshold) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    init_position();
  }
  if (cm <= distanceThreshold && cm > distanceThreshold - 100) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    init_position();
  }
  if (cm <= distanceThreshold - 100 && cm > distanceThreshold - 250) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    alarm();
  }
  if (cm <= distanceThreshold - 250 && cm > distanceThreshold - 350) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    turn();
  }
  if (cm <= distanceThreshold - 350) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    turn();
  }
  delay(100); // Wait for 100 millisecond(s)
}
