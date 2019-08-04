int cmp;
int old;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pinMode(5, INPUT);
  pinMode(A0, INPUT);

}
/*
void loop() {
  //Serial.println("looping");
  if(digitalRead(5) == 1){
    Serial.println(cmp);
    
  } else {
    cmp = 0;
  }
  if(digitalRead(7) == 1){
    if(old == 0){
      cmp ++;
      old = 1;  
    }
    
  } else {
    old = 0;
  }
  // put your main code here, to run repeatedly:
  //Serial.println(cmp);
}

*/

void loop(){

  Serial.println(analogRead(A0));
}
