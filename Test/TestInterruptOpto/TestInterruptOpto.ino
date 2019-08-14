#include <Arduino.h>

int opto = 3;
int b5 = 2;

void interuptOpto() {
  Serial.println("Detect Opto");
  
 //  aff.affichage_tout();
}

void interuptTest() {
  Serial.println("Detect test");
  
 //  aff.affichage_tout();
}
void setup() {
  // put your setup code here, to run once:
  pinMode(opto, INPUT);
  pinMode(b5, INPUT);
  pinMode(A15, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(b5), interuptTest, RISING);
  attachInterrupt(digitalPinToInterrupt(opto), interuptOpto, RISING);
  
 
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(A15));
  delay(200);
}
