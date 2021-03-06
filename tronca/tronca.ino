#include <string.h>
#include <math.h>

#include <Wire.h>
#include <string.h>


int cs_led = 48;
#include "src/LedControl.h"
LedControl lc1 = LedControl(44, 52, 48, 2);

LedControl lc2 = LedControl(9, 52, 8, 2);
int currentInterupt = 0;



//-------------------variables globales

char c1 = -1;
char c2 = -1;
// Déclaration des les d'interupteurs

int i1T = 32;
int i1B = 33;
int i2T = 34;
int i2B = 35;
int i3T = 36;
int i3B = 37;
int i4T = 28;
int i4B = 29;
int i5T = 30;
int i5B = 31;

// Déclaration des interupteurs
int i1 = 49;
int i2 = 40;
int i3 = 41;
int i4 = 38;
int i5 = 39;
// Declaration de l'encodeur
int encodeur = 45;
// Declaration des boutons
int b5 = 2;
int b1 = 22;
int b2 = 23;
int b3 = 24;
int b4 = 25;
int b6 = 26;
int b7 = 19;
int b8 = 42;

// Potar
int p1 = A8;
int p2 = A9;
// Jack

int led[12] = {i1T, i1B, i2T, i2B, i3T, i3B, i4T, i4B, i5T, i5B};
int input[14] = {i1, i2, i3, i4, i5, b1, b2, b3, b4, b5, b6, encodeur, b7, b8};
//

int moteur = 13;
int dirMoteur = 12;

int swa_5 = A0; //5
int swa_6 = A1; //6
int swa_7 = A2;  //
int swa_8 = A3;

int swb_5 = A4;
int swb_6 = A5;
int swb_7 = A6;
int swb_8 = A7;

int tmpA;
int tmpB;

int opto = 3;
int opto2 = 18;

int detecting_opto = 0;

int capteurLed  = A15;

int camera = 27;

#include "Keypad.h"
Keypad k(0x20);

#include "VariableGlobal.h"
Global g(0);

#include "EntreeSortie.h"
EntreeSortie es(input, 14, led, 12, &g); ;

#include "Affichage.h"
Affichage aff(&g, &es, &lc1, &lc2);

#include "Moteur.h"
Moteur monMoteur(&g, &aff, &es, moteur, dirMoteur, swa_5, swa_6, swa_7, swa_8, swb_5, swb_6, swb_7, swb_8, camera);


#include "Menu.h"
Menu m(&g, &es, &k, &monMoteur);

void interuptStop() {
  Serial.println("Stop pressed interupt");
  g.stop = 1;
  noInterrupts();
  monMoteur.stepper.stop = 1;
 // monMoteur.stepper.moveRelativeInSteps(0);

  interrupts();
}

void interuptArret() {
  Serial.println("Arret pressed interupt");
  g.arret = 1;
}

void interuptResetRelatif(){
    noInterrupts();
    g.posRelatif = 0;
    Serial.println("Reset Relatif");
    interrupts();
}

void interuptOpto()
{
  detachInterrupt(digitalPinToInterrupt(opto));
  



  Serial.println("Detect Opto");

  g.posAbsolue += es.dirrection();
   /*if(g.posAbsolue < 0){
      g.posAbsolue = 0;
    }*/
  g.posRelatif += es.dirrection();
  aff.affichage_lc();
  currentInterupt = 1;
  attachInterrupt(digitalPinToInterrupt(opto2), interuptInteruptOpto, RISING);

}

void interuptInteruptOpto() {
  detachInterrupt(digitalPinToInterrupt(opto2));
  currentInterupt = 0;
  attachInterrupt(digitalPinToInterrupt(opto), interuptOpto, RISING);
  Serial.println("Detachage d'interupt");
}

void interuptPhotos(){
  monMoteur.photos();
  Serial.println("Prendre photos manuellement");
}


void setup()
{
  Serial.begin(9600); // initialise connexion série à 9600 bauds
  pinMode(opto, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(b5), interuptArret, RISING);
  // BOUTON STOP A  DEFINIR
  // attachInterrupt(digitalPinToInterrupt(b5), interuptStop, RISING);
  attachInterrupt(digitalPinToInterrupt(opto), interuptOpto, RISING);
  attachInterrupt(digitalPinToInterrupt(b8), interuptResetRelatif, RISING);
  
  
  Serial.println("Ok, c'est parti");
  g.get_config();
  g.lcd_init();
  g.lcd1.print("Initialisation");
  aff.affichage_tout();
  
  Serial.println("calibrage Led");
  // monMoteur.calibrage();
  Serial.println("Resultat calibrage");
  Serial.println(g.ledMin);
  Serial.println(g.ledMax);
 // attachInterrupt(digitalPinToInterrupt(b7), interuptPhotos, RISING);
 // attachInterrupt(digitalPinToInterrupt(b8), interuptResetRelatif, RISING);



}



void loop()
{
  es.tick();
 if(es.touchInter(3)){
  aff.affichage_relatif();
 }


  if (g.posAbsolueOld != g.posAbsolue) {
   
    g.posAbsolueOld = g.posAbsolue;
    aff.affichage_absolue();

  }

  if (g.posRelatifOld != g.posRelatif) {
    g.posRelatifOld = g.posRelatif;
    aff.affichage_relatif();
  }

  //Serial.println(analogRead(p2));
  if (g.menu == 0) {
    es.gestionLed();
    handling();
  }


  // Serial.println(digitalRead(opto));


  aff.affichageConditionnel();
  if (m.affichage_menu() != 0) {
    aff.affichage_tout();
  }

  if (g.stop != 0) {
    g.stop = 0;
    //delay(2000);
  }

  if(g.arret != 0){
    g.arret = 0;
  }
}




void handling() {
  es.etteindreLed();
  // Test PULSE

   if (es.testBoutonPressed(12) ) {
      // Bouton photos
      if(monMoteur.photos()){
        return;
      }
     
    }

     if (es.testBoutonPressed(13) ) {
        g.posRelatif = 0;
        Serial.println("Reset du relatif");
     }
     
   
    
  if ( es.testInter(2) ) {
    // B1
    if (es.testBoutonPressed(5) ) {
      // PULSE ARRIERE
      monMoteur.pulseArriere();
      Serial.println("Pulse Arriere");
    }
    // B2
    if (es.testBoutonPressed(6)) {
      // PULSE AVANT
      Serial.println("Pulse Avant");
      monMoteur.pulseAvant();
    }
    // B3
    if (es.testBoutonPressed(7) ) {
      while (es.testBoutonReleased(7) == 0 && g.stop == 0 && g.arret == 0) {
        es.tick();
        monMoteur.pulseArriere();
        Serial.println("Pulse One Arriere");
      }
    }

    if (es.testBoutonPressed(8)) {
      while (es.testBoutonReleased(8) == 0 && g.stop == 0 && g.arret == 0) {
        es.tick();
        // PULSE AVANT
        monMoteur.pulseAvant();
        Serial.println("Pulse One AVANT");
      }
    }
    // B6
    if ( es.testBoutonPressed(10) & g.ecritureClavier == 0 ) {
      while (g.stop != 0) {
        es.tick();
        if (es.testAvant()) {
          // PULSE AVANT
          Serial.println("Pulse Arriere");
          monMoteur.pulseAvant();
        } else {
          // PULSE ARRIERE
          monMoteur.pulseArriere();
          Serial.println("Pulse Arriere");
        }
      }
    }


    ////
    ////
    ////
  } else {
    // Mode pas pulse
    // B1
    if (es.testBoutonPressed(5) ) {
      // IMAGE ARRIERE
      Serial.println("IMAGE Arriere");
      monMoteur.imageArriere();
    }
    // B2
    if (es.testBoutonPressed(6)) {
      // IMAGE AVANT
      monMoteur.imageAvant();
      Serial.println("IMAGE Avant");
    }
    // B3
    if (es.testBoutonPressed(7) ) {
      while (es.testBoutonReleased(7) == 0 && g.stop == 0) {
        // RECULE BOUTON BLEU
        es.tick();
        monMoteur.arriere();
        Serial.println("Recule");

      }
      // IMAGE ARRIERE
      monMoteur.imageArriere();

      Serial.println("IMAGE Arriere");
    }

    if (es.testBoutonPressed(8)) {
      while (es.testBoutonReleased(8) == 0 && g.stop == 0) {
        es.tick();
        // AVANCE BOUTON BLEU
        monMoteur.avant();
        Serial.println("Avance");
      }
      //IMAGE AVANCE
      Serial.println("Une image avant");
      monMoteur.imageAvant();
    }
    // B6
    if ( es.testBoutonPressed(10) & g.ecritureClavier == -0 ) {
      Serial.println("Go");
      // Absolue
      
      if (es.testAbsolue() ) {
        g.target = g.targetAbsolue - g.posAbsolue + g.posRelatif;
      } else {
        if (!es.testAvant()) {
        g.target = g.posRelatif - g.targetRelatif;
        } else {
         g.target = g.posRelatif + g.targetRelatif;
        }
      }

    // Bouton rouge direct
      if(g.target == g.posRelatif){
        if(es.testContinu()){
        monMoteur.configContinu();
        if(es.testAvant()){
           monMoteur.stepper.setTargetPositionRelativeInSteps(-320000);
          while(!g.arret && !monMoteur.stepper.processMovement());
            ;
          monMoteur.stepper.setTargetPositionToStop();
          
          while(!monMoteur.stepper.processMovement() && !g.stop)
            ;   
         monMoteur.imageAvant();
            
        } else {
          g.backwarding = 1;
           monMoteur.stepper.setTargetPositionRelativeInSteps(320000);
          while(!g.arret && !monMoteur.stepper.processMovement());
            ;
          monMoteur.stepper.setTargetPositionToStop();
          
          while(!monMoteur.stepper.processMovement() && !g.stop)
            ;   
                      g.backwarding = 0;
         monMoteur.imageArriere();
          
        }
        
        } else {
          if(es.testAvant()){
            while(!g.arret){
              monMoteur.imageAvant();
            }
          } else {
              
        while(!g.arret){
              monMoteur.imageArriere();
            }
          }
        }
       
      } else {
    
     Serial.println("Target");
      Serial.println(g.target);
      while ( ( abs(g.posRelatif - g.target ) > 2   )  && g.stop == 0 && g.arret == 0) {
        Serial.println(g.posRelatif - g.target );
        if (es.testContinu()) {
          // En continu
          es.tick();
          if (g.posRelatif - g.target < 0) {
            monMoteur.configContinu();
          
            monMoteur.stepper.moveRelativeInSteps( (g.posRelatif - g.target - 1) * g.pasMoteur / 16 );
           // monMoteur.avant();
          } else {
            monMoteur.configContinu();
            g.backwarding = 1;
            monMoteur.stepper.moveRelativeInSteps( (g.posRelatif - (g.target) - 1) * g.pasMoteur / 16 );
         //   monMoteur.arriere();
            g.backwarding = 0;
            
          }
        } else {
          // En image par image
          if (g.posRelatif - g.target < 0) {
            monMoteur.imageAvant();
          } else {
            monMoteur.imageArriere();
          }
        }
      }

      while ( ( (g.posRelatif - g.target != 0)  )  && g.stop == 0 && g.arret == 0) {
        if (g.posRelatif - g.target < 0) {
            monMoteur.imageAvant();
          } else {
            monMoteur.imageArriere();
          }
      }
      g.targetRelatif = 0;
      g.targetAbsolue = 0;

      // GO TO ABSOLUE TARGET

      aff.affichage_tout();
      }
    }
    
  }





  g.codeK = g.tamponK;
  g.tamponK = k.get_key();

  if ( g.tamponK == -1 && g.codeK == '#') {
    int entreeClavier;
    long tmpA;
    g.ecritureClavier = 1;
    if (es.testAbsolue()) {
      Serial.println("absolu");
      g.lcd1.setCursor(0, 1);
      g.lcd1.print("Attente saisie        ");
      tmpA = m.saisieClavier(g.lcd1, 1);
      if(tmpA == -1){
        g.targetAbsolue = 0;
      }
      g.targetAbsolue = tmpA;
    } else {
      Serial.println("Relatif");
      g.lcd2.setCursor(0, 1);
      g.lcd2.print("Attente saisie        ");
      tmpA = m.saisieClavier(g.lcd2, 1);
       if(tmpA == -1){
        g.targetRelatif = 0;
      }
      g.targetRelatif = tmpA;
    }
    Serial.println(tmpA);
    g.refresh = 1;
    g.ecritureClavier = 0;

  }

  if (g.tamponK == -1 && g.codeK == '*' && g.ecritureClavier == 0 ) {
    g.save_config();
    Serial.println("Saving config");
    for(int i = 0; i <= 5; i++){
    es.gestionLed();
    delay(200);
    es.etteindreLed();
    delay(200);
    }
  }


  
  es.gestionLed();


}
