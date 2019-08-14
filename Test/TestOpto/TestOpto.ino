    
//Permet de contrôler le driver d'un moteur pas à pas en manipulant les switchs par le biais de 4 optatocoupleurs PC815.
#include <Arduino.h>
#include <FlexyStepper.h>
#define plafond 160
const int moteurA = 13;
const int moteurA_direction = 12;



int opto = A15;

int sw5_a = A0;
int sw6_a = A1;
int sw7_a = A2;
int sw8_a = A3;

int sw5_b = A4;
int sw6_b = A5;
int sw7_b = A6;
int sw8_b = A7;
FlexyStepper stepper1;
FlexyStepper stepper2; 
int tmpH = 0;
int tmpL = 0;
int val;


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
  pinMode (sw5_a, OUTPUT);
  pinMode (sw6_a, OUTPUT);
  pinMode (sw7_a, OUTPUT);
  pinMode (sw8_a, OUTPUT);
    pinMode (sw5_b, OUTPUT);
  pinMode (sw6_b, OUTPUT);
  pinMode (sw7_b, OUTPUT);
  pinMode (sw8_b, OUTPUT);
  

  pinMode (moteurA, OUTPUT);                    // moteurs A en mouvement PULLUP à installer? pin9
  pinMode (moteurA_direction, OUTPUT);



    stepper1.connectToPins(moteurA, moteurA_direction); //stepper1 connecté aux pins 9 et 4.



    Serial.println("Init");
   intToSwitch(12800, 0);
   intToSwitch(25600, 1);


  
    stepper1.setAccelerationInStepsPerSecondPerSecond(800);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);  

pinMode (opto, INPUT);
 

}

void loop() 
{
 // Serial.println("AHA");
  
    stepper1.moveRelativeInSteps(1);
    val = analogRead(opto);
    if(val <= plafond && tmpH == 0){
      tmpH = 4;
      Serial.println("C'est dans la boite");
      // Prendre photos ici
      delay(4000);
         intToSwitch(400, 0);
        intToSwitch(800, 1);
    }
 

    if(val > plafond +25 && tmpH == 4){
      tmpH = 3;
 
    }

   if(val > plafond +200 && tmpH == 3){
      tmpH = 2;
  
    }

    if(val < plafond + 190 && tmpH == 2){
      tmpH = 0;
        intToSwitch(12800, 0);
        intToSwitch(25600, 1);
    }
    

    stepper1.moveRelativeInSteps(1);
  Serial.println(analogRead(opto));
  

  
}
/*
   digitalWrite (sw5_a, LOW);
  digitalWrite (sw6_a, HIGH);
  digitalWrite (sw7_a, HIGH);
  digitalWrite (sw8_a, HIGH);

  digitalWrite (sw5_b, LOW);
  digitalWrite (sw6_b, HIGH);
  digitalWrite (sw7_b, HIGH);
  digitalWrite (sw8_b, HIGH);

  */

void intToSwitch(int pas, int sw) {
  int i = pas/400;
  int bin = 1;
  while(i >> bin != 0){
    bin++;
  }

  Serial.println(bin);
  if (sw == 0) {
    digitalWrite(sw5_a , ((bin >> 0) &1) ^1  );
    digitalWrite(sw6_a , ((bin >> 1) &1) ^1  );
    digitalWrite(sw7_a , ((bin >> 2) &1) ^1  );
    digitalWrite(sw8_a , ((bin >> 3) &1) ^1  );

 
  } else {

    digitalWrite(sw5_b , ((bin >> 0) &1) ^1 );
    digitalWrite(sw6_b , ((bin >> 1) &1) ^1 );
    digitalWrite(sw7_b , ((bin >> 2) &1) ^1 );
    digitalWrite(sw8_b , ((bin >> 3) &1) ^1 );
  }
  Serial.println("init switch");
}
