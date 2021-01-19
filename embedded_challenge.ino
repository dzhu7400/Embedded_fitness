#include <Adafruit_CircuitPlayground.h>

float X,Y,Z;
bool rightButton;
bool startExercise = false;
float pushup, situp, jumpingjack, squat = 0;
float situp_z = 8; //starting z acceleration for situps

void stop() {
  while(1);    //loop to end the program when exercise has been done
}

void exercise_finish() {  //light up all the neopixels a different color
  CircuitPlayground.setPixelColor(0, 255,  0,  0);
  CircuitPlayground.setPixelColor(1, 128, 128,  0);
  CircuitPlayground.setPixelColor(2,  0, 255,  0);
  CircuitPlayground.setPixelColor(3,  0, 128, 128);
  CircuitPlayground.setPixelColor(4,  0,  0, 255);
  CircuitPlayground.setPixelColor(5, 0xFF0000);
  CircuitPlayground.setPixelColor(6, 0x808000);
  CircuitPlayground.setPixelColor(7, 0x00FF00);
  CircuitPlayground.setPixelColor(8, 0x008080);
  CircuitPlayground.setPixelColor(9, 0x0000FF);
  stop();
}

void do_pushups() {       //push-ups exercise
  pushup = pushup + 1;
  delay(400);
  CircuitPlayground.setPixelColor(0, 128, 128,  0);  //turn on neopixels yellow
  CircuitPlayground.setPixelColor(1, 128, 128,  0);
  CircuitPlayground.setPixelColor(2, 128, 128,  0);
  CircuitPlayground.setPixelColor(3, 128, 128,  0);
  CircuitPlayground.setPixelColor(4, 128, 128,  0);
  CircuitPlayground.setPixelColor(5, 128, 128,  0);
  CircuitPlayground.setPixelColor(6, 128, 128,  0);
  CircuitPlayground.setPixelColor(7, 128, 128,  0);
  CircuitPlayground.setPixelColor(8, 128, 128,  0);
  CircuitPlayground.setPixelColor(9, 128, 128,  0); 
  CircuitPlayground.playTone(1000,100);
  Serial.print("Push-ups: ");
  Serial.println(pushup);
}

void do_jumpingjacks() {    //jumping jacks exercise
  jumpingjack = jumpingjack + 1;
  delay(700);
  CircuitPlayground.setPixelColor(0, 0, 255, 0); //turn all neopixels green
  CircuitPlayground.setPixelColor(1, 0, 255, 0); 
  CircuitPlayground.setPixelColor(2, 0, 255, 0);
  CircuitPlayground.setPixelColor(3, 0, 255, 0);
  CircuitPlayground.setPixelColor(4, 0, 255, 0);
  CircuitPlayground.setPixelColor(5, 0, 255, 0);
  CircuitPlayground.setPixelColor(6, 0, 255, 0);
  CircuitPlayground.setPixelColor(7, 0, 255, 0);
  CircuitPlayground.setPixelColor(8, 0, 255, 0);
  CircuitPlayground.setPixelColor(9, 0, 255, 0);
  CircuitPlayground.playTone(700, 100);
  Serial.print("Jumping jacks: ");
  Serial.println(jumpingjack);
}

void do_situps() {          //situps exercise
  situp = situp + 1;
  delay(500);
  CircuitPlayground.setPixelColor(0,  0,  0, 255);  //turn all neopixels blue
  CircuitPlayground.setPixelColor(1,  0,  0, 255);
  CircuitPlayground.setPixelColor(2,  0,  0, 255);
  CircuitPlayground.setPixelColor(3,  0,  0, 255);
  CircuitPlayground.setPixelColor(4,  0,  0, 255);
  CircuitPlayground.setPixelColor(5,  0,  0, 255);
  CircuitPlayground.setPixelColor(6,  0,  0, 255);
  CircuitPlayground.setPixelColor(7,  0,  0, 255);
  CircuitPlayground.setPixelColor(8,  0,  0, 255);
  CircuitPlayground.setPixelColor(9,  0,  0, 255);
  CircuitPlayground.playTone(1250, 100);
  Serial.print("Situps: ");
  Serial.println(situp);
}

void do_squats() {              //squats exercise
  squat = squat + 1;
  delay(300);
  CircuitPlayground.setPixelColor(0, 255,  0,  0);   //turn all neopixels red
  CircuitPlayground.setPixelColor(1, 255,  0,  0);
  CircuitPlayground.setPixelColor(2, 255,  0,  0);
  CircuitPlayground.setPixelColor(3, 255,  0,  0);
  CircuitPlayground.setPixelColor(4, 255,  0,  0);
  CircuitPlayground.setPixelColor(5, 255,  0,  0);
  CircuitPlayground.setPixelColor(6, 255,  0,  0);
  CircuitPlayground.setPixelColor(7, 255,  0,  0);
  CircuitPlayground.setPixelColor(8, 255,  0,  0);
  CircuitPlayground.setPixelColor(9, 255,  0,  0);
  CircuitPlayground.playTone(1500, 100);
  Serial.print("Squats: ");
  Serial.println(squat);
}

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
}

void loop() {
  CircuitPlayground.clearPixels();
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.println(Z);
  
 
  rightButton = CircuitPlayground.rightButton();

  if (rightButton) {   //press the right button to start the program; user can then start to exercise
    CircuitPlayground.setPixelColor(9, 0, 64, 0);
    CircuitPlayground.playTone(500, 100);
    startExercise = true;
  }

  if (startExercise) {
    if (Z < -12 && X < 0 && X > -6 && situp == 0 && squat == 0 && jumpingjack == 0) { //pushups
      do_pushups();
      if (pushup == 10) {
          exercise_finish();
      }
    }
    if (X < -15 && Z > 0 && situp == 0 && squat == 0 && pushup == 0) { //jumping jacks
      do_jumpingjacks();
      if (jumpingjack == 10) {
          exercise_finish();   
      }
    }

    if (Z < -2.5 && Z > -10 && X < -12 && situp == 0 && jumpingjack == 0 && pushup == 0) { //squats
      do_squats();
      if (squat == 10) {
          exercise_finish();
      } 
    }

   
    if (X < -8 && X > -10 && abs(Z - situp_z) > 6.5 && Y < 0 && squat == 0 && jumpingjack == 0 && pushup == 0) { //situps
      do_situps();
      if (situp == 10) {
          exercise_finish();
       }
      }
 
  }
  delay(100);
}
