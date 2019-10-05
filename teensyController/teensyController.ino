#include <Encoder.h>

#define PIN_PWM 20
#define PIN_LED 13

#define PITCH_OFFSET  (0)   //1024 scale
#define YAW_OFFSET    (512) //1024 scale
#define ROLL_OFFSET   (512) //1024 scale
#define PITCH_GAIN    (10)
#define YAW_GAIN      (32)
#define ROLL_GAIN     (32)

#define THROTTLE_LEFT_OFFSET            (0) //1024 scale
#define THROTTLE_RIGHT_OFFSET           (0) //1024 scale
#define THROTTLE_LEFT_GAIN_NUMERATOR    (1)
#define THROTTLE_LEFT_GAIN_DENOMINATOR  (1)
#define THROTTLE_RIGHT_GAIN_NUMERATOR   (1)
#define THROTTLE_RIGHT_GAIN_DENOMINATOR (1)

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
  

  Serial.begin(115200);
  Serial.println("OAM A3 simulator");
}

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

  int32_t newPosition;

  newPosition = (PITCH_GAIN * (pitch.read())) + PITCH_OFFSET;
  if(newPosition <= 0)
  {
    Joystick.Y(0);
  }
  else if(newPosition >= 1023)
  {
    Joystick.Y(1023);
  }
  else
  {
    Joystick.Y(newPosition);
  }

  newPosition = (ROLL_GAIN * (roll.read())) + ROLL_OFFSET;
  if(newPosition <= 0)
  {
    Joystick.X(0);
  }
  else if(newPosition >= 1023)
  {
    Joystick.X(1023);
  }
  else
  {
    Joystick.X(newPosition);
  }

  newPosition = (YAW_GAIN * (yaw.read())) + YAW_OFFSET;
  if(newPosition <= 0)
  {
    Joystick.Zrotate(0);
  }
  else if(newPosition >= 1023)
  {
    Joystick.Zrotate(1023);
  }
  else
  {
    Joystick.Zrotate(newPosition);
  }

  newPosition = ((analogRead(0) + THROTTLE_LEFT_OFFSET) * THROTTLE_LEFT_GAIN_NUMERATOR) / THROTTLE_LEFT_GAIN_DENOMINATOR;
  if(newPosition <= 0)
  {
    Joystick.sliderLeft(0);
  }
  else if(newPosition >= 1023)
  {
    Joystick.sliderLeft(1023);
  }
  else
  {
    Joystick.sliderLeft(newPosition);
  }

  newPosition = ((analogRead(1) + THROTTLE_RIGHT_OFFSET) * THROTTLE_RIGHT_GAIN_NUMERATOR) / THROTTLE_RIGHT_GAIN_DENOMINATOR;
  if(newPosition <= 0)
  {
    Joystick.sliderRight(0);
  }
  else if(newPosition >= 1023)
  {
    Joystick.sliderRight(1023);
  }
  else
  {
    Joystick.sliderRight(newPosition);
  }
  
//  Joystick.X(4 * pwm_count);
//  Joystick.Y(4 * pwm_count);
//  Joystick.Z(4 * pwm_count);
//  Joystick.Zrotate(4 * pwm_count);
//  Joystick.sliderLeft(4 * pwm_count);
//  Joystick.sliderRight(4 * pwm_count);

  Joystick.send_now();
}
