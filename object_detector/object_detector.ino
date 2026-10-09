#include <Servo.h>
#include <LiquidCrystal.h>
#include <string.h>

// ----- EDIT YOUR SCREEN TEXT HERE (max 16 characters per line) -----
const char* DETECTED_LINE1 = "WARNING!!";
const char* DETECTED_LINE2 = "FOREIGN BODY";
const char* CLEAR_LINE1    = "ALL CLEAR";
const char* CLEAR_LINE2    = "NO OBJECT";
// --------------------------------------------------------------------

const int TRIG = 9;
const int ECHO = 10;
const int SERVO_PIN = 11;
const int BUZZER = 6;
const int GREEN1 = A0, GREEN2 = A1;
const int RED1 = A2, RED2 = A3;

const int DETECT_CM = 30;   // closer than this = object detected

Servo servo;
LiquidCrystal lcd(7, 8, 2, 3, 4, 5);  // RS, E, D4, D5, D6, D7

int angle = 15;
int step = 5;
bool lastDetected = false;
bool firstRun = true;

// prints text in the middle of the chosen row (0 = top, 1 = bottom)
void printCentered(const char* text, int row) {
  int len = strlen(text);
  if (len > 16) len = 16;
  int col = (16 - len) / 2;
  lcd.setCursor(col, row);
  lcd.print(text);
}

long readDistanceCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH, 25000);
  if (duration == 0) return 999;   // no echo = nothing close
  return duration * 0.034 / 2;
}

void showClear() {
  digitalWrite(GREEN1, HIGH);
  digitalWrite(GREEN2, HIGH);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, LOW);
  noTone(BUZZER);
  lcd.clear();
  printCentered(CLEAR_LINE1, 0);
  printCentered(CLEAR_LINE2, 1);
}

void showDetected() {
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  lcd.clear();
  printCentered(DETECTED_LINE1, 0);
  printCentered(DETECTED_LINE2, 1);
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);
  servo.attach(SERVO_PIN);
  lcd.begin(16, 2);
  showClear();
}

void loop() {
  servo.write(angle);
  delay(40);

  long cm = readDistanceCm();
  bool detected = (cm < DETECT_CM);

  if (detected) {
    if (!lastDetected || firstRun) showDetected();
    // servo stays still: blink red lights and beep
    digitalWrite(RED1, HIGH);
    digitalWrite(RED2, HIGH);
    tone(BUZZER, 2000);
    delay(60);
    digitalWrite(RED1, LOW);
    digitalWrite(RED2, LOW);
    noTone(BUZZER);
    delay(60);
  } else {
    if (lastDetected || firstRun) showClear();

    // only sweep when nothing is detected
    angle += step;
    if (angle >= 165 || angle <= 15) step = -step;
  }

  lastDetected = detected;
  firstRun = false;
}
