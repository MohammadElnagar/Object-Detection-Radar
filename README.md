# Object Detection Radar

An Arduino radar that sweeps an ultrasonic sensor left and right on a servo. When something comes closer than 30 cm, the servo stops and points at it, the screen shows a warning, the red LEDs blink and the buzzer beeps. When nothing is close, the green LEDs stay on and the screen says all clear.

## Parts
- Elegoo UNO R3 (Arduino Uno)
- HC-SR04 ultrasonic sensor
- SG90 micro servo
- LCD1602 screen (16 pins, no I2C)
- 2 red LEDs and 2 green LEDs
- 4 resistors, 220 ohm
- Passive buzzer
- Breadboard and male-to-male jumper wires

## Wiring

| Part | Pin | Connects to |
|---|---|---|
| Ultrasonic sensor | VCC | + rail (5V) |
| | Trig | Arduino 9 |
| | Echo | Arduino 10 |
| | GND | - rail |
| Servo | Orange | Arduino 11 |
| | Red | + rail (5V) |
| | Brown | - rail |
| LCD | VSS, RW, V0, K | - rail |
| | VDD, A | + rail (5V) |
| | RS | Arduino 7 |
| | E | Arduino 8 |
| | D4 | Arduino 2 |
| | D5 | Arduino 3 |
| | D6 | Arduino 4 |
| | D7 | Arduino 5 |
| Green LEDs | Long leg via resistor | A0 and A1 |
| Red LEDs | Long leg via resistor | A2 and A3 |
| Buzzer | + leg | Arduino 6 |
| All LEDs and buzzer | Short leg | - rail |

Connect the + rail to the Arduino 5V and the - rail to an Arduino GND. The LEDs and buzzer have their own - rail on the bottom of the breadboard, so it needs its own wire to GND too.

## How to run
1. Open `object_detector/object_detector.ino` in the Arduino IDE.
2. Select Arduino Uno and the right port.
3. Click Upload.

## Settings
- `DETECT_CM` sets how close something must be to trigger the alarm.
- Change the four text lines at the top to edit the screen messages (16 characters max per line).
- The buzzer is passive, so the code uses `tone()`. For an active buzzer, use `digitalWrite` instead.
