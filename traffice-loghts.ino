#include <LiquidCrystal.h>

// -------------------------
// ULTRASONIC SENSOR
// -------------------------
const int trigPin = 9;
const int echoPin = 10;

// -------------------------
// LEDS
// -------------------------
const int greenLED = 6;
const int yellowLED = 5;
const int redLED = 4;

// -------------------------
// LCD
// RS, E, D4, D5, D6, D7
// -------------------------
LiquidCrystal lcd(12, 11, 7, 8, 2, 3);

// -------------------------
// VARIABLES
// -------------------------
long duration;
float distance;


void setup() {

  // Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LEDs
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Start LCD
  lcd.begin(16, 2);

  // Start Serial Monitor
  Serial.begin(9600);

  // Starting message
  lcd.setCursor(0, 0);
  lcd.print("Obstacle Sensor");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);

  lcd.clear();
}


void loop() {

  // ==================================
  // 1. SEND ULTRASONIC SIGNAL
  // ==================================

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);


  // ==================================
  // 2. RECEIVE THE ECHO
  // ==================================

  duration = pulseIn(echoPin, HIGH);


  // ==================================
  // 3. CALCULATE DISTANCE
  // ==================================

  distance = duration * 0.0343 / 2;


  // Show distance in Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // ==================================
  // GREEN = CLEAR
  // More than 30 cm
  // ==================================

  if (distance > 30) {

    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("STATUS:");

    lcd.setCursor(0, 1);
    lcd.print("CLEAR");
  }


  // ==================================
  // YELLOW = CAUTION
  // 15-30 cm
  // ==================================

  else if (distance > 15 && distance <= 30) {

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("STATUS:");

    lcd.setCursor(0, 1);
    lcd.print("CAUTION");
  }


  // ==================================
  // RED = STOP
  // 15 cm or less
  // ==================================

  else {

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("WARNING!");

    lcd.setCursor(0, 1);
    lcd.print("STOP!");
  }


  // Wait a little before measuring again
  delay(200);
}traffic
