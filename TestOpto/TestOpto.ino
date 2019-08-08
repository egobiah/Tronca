    
//Permet de contrôler le driver d'un moteur pas à pas en manipulant les switchs par le biais de 4 optatocoupleurs PC815.

#include <FlexyStepper.h>
#define plafond 60
const int moteurA = 9;
const int moteurA_direction = 4;



int opto = A0;

int sw5_A = 10;
int sw6_A = 11;
int sw7_A = 12;
int sw8_A = 13;
FlexyStepper stepper1;
FlexyStepper stepper2; 
int tmpH = 0;
int tmpL = 0;
int val;


void setup() {
  // put your setup code here, to run once:

  pinMode (sw5_A, OUTPUT);
  pinMode (sw6_A, OUTPUT);
  pinMode (sw7_A, OUTPUT);
  pinMode (sw8_A, OUTPUT);
  

  pinMode (moteurA, OUTPUT);                    // moteurs A en mouvement PULLUP à installer? pin9
  pinMode (moteurA_direction, OUTPUT);



    stepper1.connectToPins(moteurA, moteurA_direction); //stepper1 connecté aux pins 9 et 4.



    vingt_cinq_mille_six_cent; //------------------------------------------------------------Super----
    stepper1.setAccelerationInStepsPerSecondPerSecond(800);   //acceleration
    stepper1.setSpeedInStepsPerSecond(12800);  

Serial.begin(9600);
pinMode (opto, INPUT);
 

}

void loop() 
{
  
    stepper1.moveRelativeInSteps(1);
    val = analogRead(opto);
    if(val <= plafond && tmpH == 0){
      tmpH = 2;
      Serial.println("C'est dans la boite");
      // Prendre photos ici
      delay(4000);
    }
    if(val > plafond &&  tmpH == 2){
      tmpH = 1;
    }

    if(val > plafond +200 && tmpH == 1){
      tmpH = 0;
    }
  Serial.println(analogRead(opto));

  
}

void quatre_cent () //off on on on
{
  digitalWrite (sw5_A, LOW);
  digitalWrite (sw6_A, HIGH);
  digitalWrite (sw7_A, HIGH);
  digitalWrite (sw8_A, HIGH);
}

void huit_cent () //off on on on
{
  digitalWrite (sw5_A, HIGH);
  digitalWrite (sw6_A, LOW);
  digitalWrite (sw7_A, HIGH);
  digitalWrite (sw8_A, HIGH);
}

void mille_six_cent () //off on on on
{
  digitalWrite (sw5_A, LOW);
  digitalWrite (sw6_A, LOW);
  digitalWrite (sw7_A, HIGH);
  digitalWrite (sw8_A, HIGH);
}

void trois_mille_deux_cent () //off on on on
{
  digitalWrite (sw5_A, HIGH);
  digitalWrite (sw6_A, HIGH);
  digitalWrite (sw7_A, LOW);
  digitalWrite (sw8_A, HIGH);
}

void six_mille_quatre_cent () //off on on on
{
  digitalWrite (sw5_A, LOW);
  digitalWrite (sw6_A, HIGH);
  digitalWrite (sw7_A, LOW);
  digitalWrite (sw8_A, HIGH);
}

void douze_mille_huit_cent () 
{
  digitalWrite (sw5_A, HIGH);
  digitalWrite (sw6_A, LOW);
  digitalWrite (sw7_A, LOW);
  digitalWrite (sw8_A, HIGH);
}

void vingt_cinq_mille_six_cent () 
{
  digitalWrite (sw5_A, LOW);
  digitalWrite (sw6_A, LOW);
  digitalWrite (sw7_A, LOW);
  digitalWrite (sw8_A, HIGH);
}


void test_serie_A() {
  
  quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    huit_cent(); //---------------------------------------------OK pour DEPLACEMENT--------------------------------------------------
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    mille_six_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    trois_mille_deux_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    six_mille_quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    douze_mille_huit_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    vingt_cinq_mille_six_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);
}

//-----------------------------------------------SERIE B--------------------------------------------------------------------

void test_serie_B() {
  
    quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(50);
  delay (500);

    huit_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(100);
  delay (500);

    mille_six_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(200);
  delay (500);

    trois_mille_deux_cent(); //---------------------------------------ok pour image par image---------------------------------------
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(400);
  delay (500);

    six_mille_quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(800);
  delay (500);

    douze_mille_huit_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(1600);
  delay (500);

    vingt_cinq_mille_six_cent(); //-----------------------------------ok pour calage----------------------------------------------
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(400);      
    stepper1.moveRelativeInSteps(3200);
  delay (500);
}


void  deplacement_rapide_A() //-------------------bien
{
     quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(400);   //acceleration
    stepper1.setSpeedInStepsPerSecond(800);      
    stepper1.moveRelativeInSteps(50*100);
  delay (500);

    huit_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(800);   //acceleration
    stepper1.setSpeedInStepsPerSecond(3200);      
    stepper1.moveRelativeInSteps(100*100);
  delay (500);

    mille_six_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(6400);      
    stepper1.moveRelativeInSteps(200*100);
  delay (500); 
}

void  deplacement_rapide_B() //-------------------
{
     quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(800);   //acceleration
    stepper1.setSpeedInStepsPerSecond(800);      
    stepper1.moveRelativeInSteps(50*100);
  delay (500);

    huit_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(3200);      
    stepper1.moveRelativeInSteps(100*100);
  delay (500);

    mille_six_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(3200);   //acceleration
    stepper1.setSpeedInStepsPerSecond(6400);      
    stepper1.moveRelativeInSteps(200*100);
  delay (500); 
}

void  deplacement_rapide_C() //-------------------OK
{
    quatre_cent();
    stepper1.setAccelerationInStepsPerSecondPerSecond(1600);   //acceleration
    stepper1.setSpeedInStepsPerSecond(800);      
    stepper1.moveRelativeInSteps(50*100);
  delay (1000);

    huit_cent(); //------------------------------------------------------------Super----
    stepper1.setAccelerationInStepsPerSecondPerSecond(3200);   //acceleration
    stepper1.setSpeedInStepsPerSecond(6400);      
    stepper1.moveRelativeInSteps(50000);
  delay (5000);

    mille_six_cent(); //-------------------------------------------------------Super aussi!----
    stepper1.setAccelerationInStepsPerSecondPerSecond(6400);   //acceleration
    stepper1.setSpeedInStepsPerSecond(6400);      
    stepper1.moveRelativeInSteps(200*100);
  delay (1000); 
}
