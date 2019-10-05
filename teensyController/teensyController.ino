#include <Encoder.h>

#define PIN_PWM 20
#define PIN_LED 13

#define PITCH_OFFSET  0
#define YAW_OFFSET    16
#define ROLL_OFFSET   16
#define PITCH_GAIN    10
#define YAW_GAIN      32
#define ROLL_GAIN     32

int pwm_count = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

Encoder pitch(3, 2);
Encoder roll(4, 5);
Encoder yaw(6, 7);

// the setup routine runs once when you press reset:
void setup() {
  
//   // declare pin 9 to be an output:
//   pinMode(PIN_PWM, OUTPUT);
//   analogWriteFrequency(PIN_PWM, 10000);
//   analogWrite(PIN_PWM, pwm_count);
// //  analogWrite(PIN_PWM, 40);

// //  while(1);

  Joystick.useManualSend(true);

  Joystick.X(512);
  Joystick.Y(512);
  Joystick.Z(512);
  Joystick.Zrotate(512);
  Joystick.sliderLeft(0);
  Joystick.sliderRight(0);
  Joystick.send_now();
  

  Serial.begin(9600);
//  Serial.println("OAM A6 simulator");
}

long oldPitchPosition  = -999;
long oldRollPosition  = -999;
long oldYawPosition  = -999;

// the loop routine runs over and over again forever:
void loop() {
//   // set the brightness of pin 9:
//   analogWrite(PIN_PWM, pwm_count);

//   // change the brightness for next time through the loop:
//   pwm_count = pwm_count + fadeAmount;

//   // reverse the direction of the fading at the ends of the fade:
// //  if (pwm_count <= 0 || pwm_count >= 255) {
// //  if (pwm_count <= 50 || pwm_count >= 205) {
// //  if (pwm_count <= 0 || pwm_count >= 95) {
//   if (pwm_count <= 0 || pwm_count >= 45) {
//     fadeAmount = -fadeAmount;
//   }
//   // wait for 30 milliseconds to see the dimming effect
//   delay(100);
// //  delay(300);

// //  analogWrite(PIN_PWM, 245);
// //  delay(1000);
// //  analogWrite(PIN_PWM, 10);
// //  delay(1000);

  long newPitchPosition = pitch.read() + PITCH_OFFSET;
  if (newPitchPosition != oldPitchPosition) {
    oldPitchPosition = newPitchPosition;
    // Serial.println(newPitchPosition);
  }

  long newRollPosition = roll.read() + ROLL_OFFSET;
  if (newRollPosition != oldRollPosition) {
    oldRollPosition = newRollPosition;
  }

  long newYawPosition = yaw.read() + YAW_OFFSET;
  if (newYawPosition != oldYawPosition) {
    oldYawPosition = newYawPosition;
  }


  
  newPitchPosition *= PITCH_GAIN;
  if(newPitchPosition <= 0)
  {
    Joystick.Y(0);
  }
  else if(newPitchPosition >= 1023)
  {
    Joystick.Y(1023);
  }
  else
  {
    Joystick.Y(newPitchPosition);
  }


  newRollPosition *= ROLL_GAIN;
  if(newRollPosition <= 0)
  {
    Joystick.X(0);
  }
  else if(newRollPosition >= 1023)
  {
    Joystick.X(1023);
  }
  else
  {
    Joystick.X(newRollPosition);
  }


  newYawPosition *= YAW_GAIN;
  if(newYawPosition <= 0)
  {
    Joystick.Zrotate(0);
  }
  else if(newYawPosition >= 1023)
  {
    Joystick.Zrotate(1023);
  }
  else
  {
    Joystick.Zrotate(newYawPosition);
  }
  
//  Joystick.X(4 * pwm_count);
//  Joystick.Y(4 * pwm_count);
//  Joystick.Z(4 * pwm_count);
//  Joystick.Zrotate(4 * pwm_count);
//  Joystick.sliderLeft(4 * pwm_count);
//  Joystick.sliderRight(4 * pwm_count);

  Joystick.send_now();

  
}
