#include "Moteur.h"
#define plafondBas g->ledMin+seuil
#define plafondMid (g->ledMax+g->ledMin)/2
#define plafondHaut g->ledMax-40

Moteur::Moteur(Global * g1, Affichage * a1, EntreeSortie * es1, int pinMoteur, int pinDirMoteur, int pin_swa_1, int pin_swa_2, int pin_swa_3, int pin_swa_4,  int pin_swb_1, int pin_swb_2, int pin_swb_3, int pin_swb_4) {
  g = g1;
  a = a1;
  moteur = pinMoteur;
  dirMoteur = pinDirMoteur;
  es = es1;

  swa_1 = pin_swa_1;
  swa_2 = pin_swa_2;
  swa_3 = pin_swa_3;
  swa_4 = pin_swa_4;

  swb_1 = pin_swb_1;
  swb_2 = pin_swb_2;
  swb_3 = pin_swb_3;
  swb_4 = pin_swb_4;

  pinMode( pin_swa_1, OUTPUT);
  pinMode(pin_swa_2 , OUTPUT);
  pinMode( pin_swa_3, OUTPUT);
  pinMode(pin_swa_4 , OUTPUT);

  pinMode(pin_swb_1 , OUTPUT);
  pinMode( pin_swb_2, OUTPUT);
  pinMode(pin_swb_3 , OUTPUT);
  pinMode( pin_swb_4, OUTPUT);



  stepper.connectToPins(moteur, dirMoteur);
  stepper.setAccelerationInStepsPerSecondPerSecond(800);   //acceleration
  stepper.setSpeedInStepsPerSecond(12800);
}
void Moteur::pulseAvant() {
  Serial.println("1 pulse Avant");
}
void Moteur::pulseArriere() {
  Serial.println("1 pulse Arrière");
}

void Moteur::callageAvant() {
  Serial.println("Callage");
  intToSwitch(12800, 0);
  intToSwitch(25600, 1);
  stepper.setSpeedInStepsPerSecond(200);

  while (analogRead(capteurLed ) >= plafondBas && g->stop == 0) {
    stepper.moveRelativeInSteps(1);
  }
  Serial.println("Photos!");
  
}

void Moteur::callageArriere() {
  Serial.println("Callage");
  intToSwitch(12800, 0);
  intToSwitch(25600, 1);

  while (analogRead(capteurLed ) >= plafondBas) {
    stepper.moveRelativeInSteps(-2);
  }
  Serial.println("Photos!");
  
}

void Moteur::avant() {
  intToSwitch(800, 0);
  intToSwitch(400, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(1600);  //acceleration
  stepper.setSpeedInStepsPerSecond(400);
  stepper.moveRelativeInSteps(80);

}

void Moteur::arriere() {
  intToSwitch(800, 0);
  intToSwitch(400, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(1600);  //acceleration
  stepper.setSpeedInStepsPerSecond(400);
  stepper.moveRelativeInSteps(-80);

}

void Moteur::imageAvant() {
  int i = 0;
  int j = 0;
  Serial.println("Une image Avant");
  intToSwitch(800, 0);
  intToSwitch(400, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(3200);  //acceleration
  stepper.setSpeedInStepsPerSecond(800);
  int tour = 0;
  while (!(i == 1 && analogRead(capteurLed ) < plafondMid && g->stop == 0)) {
    
    stepper.moveRelativeInSteps(1);
    if (analogRead(capteurLed ) > plafondHaut && i == 0) {      
      i = 1;
    }
  }
  callageAvant();
  delay(2000);





  delay(g->tempsPose);
  a->affichage_tout();
}


void Moteur::imageArriere() {
  int i = 0;
  int j = 0;
  Serial.println("Une Arriere");
  intToSwitch(800, 0);
  intToSwitch(400, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(800);  //acceleration
  stepper.setSpeedInStepsPerSecond(400);
  while (!(i == 1 && analogRead(capteurLed ) < plafondMid)) {
    stepper.moveRelativeInSteps(-2);
    if (analogRead(capteurLed ) > plafondHaut && i == 0) {      
      i = 1;
    }
  }
  callageArriere();
  delay(2000);




  delay(g->tempsPose);
  a->affichage_tout();
}



void Moteur::goToAbsolue() {
  Serial.println("C'est parti pour aller en absolue: ");
  Serial.println(g->targetAbsolue);
  while (g->targetAbsolue != g->posAbsolue && g->stop == 0) {
    if ( (g->targetAbsolue - g->posAbsolue) > 0 ) {
      imageAvant();

    } else {
      imageArriere();
    }


  }
}
void Moteur::goToRelatif() {
  Serial.println("C'est parti pour aller en relatif :");
  Serial.println(g->targetRelatif);
  int i = 0;
  if (!es->testAvant()) {

    //i = -i;
    Serial.println("Goto Arriere");
    Serial.println(i);
  }
  while (g->targetRelatif  != i  && g->stop == 0) {

    if ( (i - g->targetRelatif ) < 0 ) {
      imageAvant();
      i++;

    } else {
      imageArriere();
      i--;
    }
  }

}

void Moteur::intToSwitch(int pas, int sw) {
  int i = pas/400;
  int bin = 1;
  while(i >> bin != 0){
    bin++;
  }

  
  if (sw == 0) {
    digitalWrite(swa_1 , ((bin >> 0) &1) ^1  );
    digitalWrite(swa_2 , ((bin >> 1) &1) ^1  );
    digitalWrite(swa_3 , ((bin >> 2) &1) ^1  );
    digitalWrite(swa_4 , ((bin >> 3) &1) ^1  );

 
  } else {

    digitalWrite(swb_1 , ((bin >> 0) &1) ^1 );
    digitalWrite(swb_2 , ((bin >> 1) &1) ^1 );
    digitalWrite(swb_3 , ((bin >> 2) &1) ^1 );
    digitalWrite(swb_4 , ((bin >> 3) &1) ^1 );
  }
 
}

void Moteur::calibrage(){
  int min = g->ledMin;
  int max = g->ledMax;
 
  intToSwitch(12800, 0);
  intToSwitch(25600, 1);
  stepper.setSpeedInStepsPerSecond(6400);
  for(int i = 0; i < 12800 && g->stop == 0; i++){
    int lecture = analogRead(capteurLed );
    if(lecture < min){
     
      min = lecture;
    }
    if(lecture > max){
      max = lecture;
    }
    a->intToLed(lecture,a->lc1);
     stepper.moveRelativeInSteps(1);
    g->ledMin = min;
    g->ledMax = max;
    a->intToLed(g->ledMax,a->lc2);
  a->lc2->setDigit(0,7,g->ledMin/100,0);
  a->lc2->setDigit(0,6,(g->ledMin%100)/10,0);
  a->lc2->setDigit(0,5,g->ledMin%10,0);
  }
  

  Serial.println("Reglage Capteur finis");
  Serial.println(g->ledMin);
  Serial.println(g->ledMax);
  
}
