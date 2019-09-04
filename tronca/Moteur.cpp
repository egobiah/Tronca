#include "Moteur.h"
#define plafondBas g->ledMin+g->seuil
#define plafondMid (g->ledMax+g->ledMin)/2
#define plafondHaut g->ledMax-40

Moteur::Moteur(Global * g1, Affichage * a1, EntreeSortie * es1, int pinMoteur, int pinDirMoteur, int pin_swa_1, int pin_swa_2, int pin_swa_3, int pin_swa_4,  int pin_swb_1, int pin_swb_2, int pin_swb_3, int pin_swb_4, int pinCamera) {
  g = g1;
  a = a1;
  moteur = pinMoteur;
  dirMoteur = pinDirMoteur;
  es = es1;
  camera = pinCamera;
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

  pinMode(camera, OUTPUT);
  //digitalWrite(camera, LOW);


  stepper.connectToPins(moteur, dirMoteur);
  stepper.setAccelerationInStepsPerSecondPerSecond(800);   //acceleration
  stepper.setSpeedInStepsPerSecond(12800);
}
void Moteur::photos() {
  if (!es->testContinu() && es->testCamera() && g->stop == 0 ){
      // FONCTION PRENDRE PHOTOS
      digitalWrite(camera,HIGH);
      Serial.println("photos");
      delay(g->tempsPose);
      digitalWrite(camera, LOW);
  }
}

void Moteur::pulseAvant() {
  configContinu();
  stepper.moveRelativeInSteps(-2);
}

void Moteur::avant() {
  configContinu();
  stepper.moveRelativeInSteps(-g->pasParBoucle);
}

void Moteur::callageAvant() {
  configCallage();
  Serial.println("Callage");
 
  stepper.setSpeedInStepsPerSecond(-200);

  while  (analogRead(capteurLed ) >= plafondBas && g->stop == 0) {
    stepper.moveRelativeInSteps(-2);
  }


}

void Moteur::imageAvant() {
  configIpI();

  int i = 0;
  int j = 0;
  Serial.println("Une image Avant");

  stepper.moveRelativeInSteps(-(g->pasMoteurIpI/18));
  int tour = 0;
  while (!((i == 1 && analogRead(capteurLed ) < plafondMid) ) && g->stop == 0) {

    stepper.moveRelativeInSteps(-2);
    if (analogRead(capteurLed ) > plafondHaut && i == 0) {
      i = 1;
    }
  }
  callageAvant();
  es->tick();
  Serial.println("ici photos");
  photos();
  a->affichage_tout();
}

void Moteur::pulseArriere() {
  g->backwarding = 1;
  configContinu();
  stepper.moveRelativeInSteps(1);
  g->backwarding = 0;
}

void Moteur::arriere() {
  g->backwarding = 1;
  configContinu();
  stepper.moveRelativeInSteps(g->pasParBoucle);
  g->backwarding = 0;
}

void Moteur::callageArriere() {
  g->backwarding = 1;
  configCallage();
  Serial.println("Callage");
  
  stepper.setSpeedInStepsPerSecond(200);

  while (analogRead(capteurLed ) >= plafondBas && g->stop == 0) {
    stepper.moveRelativeInSteps(1);
  }

g->backwarding = 0;
}

void Moteur::imageArriere() {
  g->backwarding = 1;
  configIpI();

  int i = 0;
  int j = 0;
  Serial.println("Une image Arriere");
stepper.moveRelativeInSteps((g->pasMoteurIpI/18));
  int tour = 0;
  while (!((i == 1 && analogRead(capteurLed ) < plafondMid) ) && g->stop == 0) {



    stepper.moveRelativeInSteps(1);
    if (analogRead(capteurLed ) > plafondHaut && i == 0) {
      i = 1;
    }
  }
  callageArriere();
  es->tick();
  photos();




  
  a->affichage_tout();
  g->backwarding = 0;
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
  int i = pas / 400;
  int bin = 1;
  while (i >> bin != 0) {
    bin++;
  }


  if (sw == 0) {
    digitalWrite(swa_1 , ((bin >> 0) & 1) ^ 1  );
    digitalWrite(swa_2 , ((bin >> 1) & 1) ^ 1  );
    digitalWrite(swa_3 , ((bin >> 2) & 1) ^ 1  );
    digitalWrite(swa_4 , ((bin >> 3) & 1) ^ 1  );


  } else {

    digitalWrite(swb_1 , ((bin >> 0) & 1) ^ 1 );
    digitalWrite(swb_2 , ((bin >> 1) & 1) ^ 1 );
    digitalWrite(swb_3 , ((bin >> 2) & 1) ^ 1 );
    digitalWrite(swb_4 , ((bin >> 3) & 1) ^ 1 );
  }

}

void Moteur::calibrage() {
  int min = 1000;
  int max = 0;

  configCallage();
  for (int i = 0; i < 12800 && g->stop == 0; i++) {
    int lecture = analogRead(capteurLed );
    if (lecture < min) {

      min = lecture;
    }
    if (lecture > max) {
      max = lecture;
    }
    a->intToLed(lecture, a->lc1);
    stepper.moveRelativeInSteps(1);

    a->intToLed(max, a->lc2);
    a->lc2->setDigit(0, 7, min / 100, 0);
    a->lc2->setDigit(0, 6, (min % 100) / 10, 0);
    a->lc2->setDigit(0, 5, min % 10, 0);
  }
  g->ledMax = max;
  g-> ledMin = min;

  Serial.println("Reglage Capteur finis");
  Serial.println(g->ledMin);
  Serial.println(g->ledMax);

}

void Moteur::configContinu() {
  intToSwitch(g->pasMoteur , 0);
  intToSwitch(g->pasMoteur*2, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(g->acceleration);  //acceleration
  stepper.setSpeedInStepsPerSecond(g->stepMoteurParSec);

}

void Moteur::configIpI() {
  intToSwitch(g->pasMoteurIpI , 0);
  intToSwitch(g->pasMoteurIpI*2, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(g->accelerationIpI);  //acceleration
  stepper.setSpeedInStepsPerSecond(g->stepMoteurParSecIpI);

}

void Moteur::configCallage() {
  intToSwitch(g->pasMoteurCallage , 0);
  intToSwitch(g->pasMoteurCallage*2, 1);
  stepper.setAccelerationInStepsPerSecondPerSecond(g->accelerationCallage);  //acceleration
  stepper.setSpeedInStepsPerSecond(g->stepMoteurParSecCallage);
}
