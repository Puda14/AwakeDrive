#include <SoftwareSerial.h>

int soundPin = 12;

void setup() {
  Serial.begin(57600);
}

void play(int freqz, int time=1){
  if (freqz == 0) {
    noTone(soundPin);
    return ;
  }
  int i = 0;
  while (i<=time*800) {
    int t = 1000/freqz;
    tone(soundPin, 60);
    delay(t);
    noTone(soundPin);
    delay(t);
    i+=2*t;
  }
  return ;
}

// int predict_freqz(int t, int n, int min, int max){
//   if (t = 0) {
//     return 0;
//   }
//   return min + t;
// }

int count = 0;
int m[10];
int val = 0;

void loop() {
  int freqz = 0;
  while (Serial.available()>0) {
    char s = Serial.read();
    if (s !='\n'){
      int num = 1- (s - 48);
      val = val - m[count] + num;
      m[count] = num;
      count = (count + 1) % 10;
      if (val == 0){
        freqz = 0;
      }
      else {
        freqz = 15 + val;
      }
    // Serial.println(freqz);  
    }
  }
  if(freqz != 0 ) freqz = 15;
  play(freqz, 1);
}