#include <string.h>
#include <math.h>

#include <Wire.h>
#include <string.h>


int cs_led = 48;
#include "src/LedControl.h"
LedControl lc1 = LedControl(44, 52, 48, 2);

LedControl lc2 = LedControl(9, 52, 8, 2);




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
// Potar
int p1 = A8;
int p2 = A9;
// Jack
int vert = 11;
int rouge = 12;
int led[12] = {i1T, i1B, i2T, i2B, i3T, i3B, i4T, i4B, i5T, i5B};
int input[12] = {i1, i2, i3, i4, i5, b1, b2, b3, b4, b5, b6, encodeur};
//

int moteur = 13;
int dirMoteur = 12;

int swa_1 = A0;
int swa_2 = A1;
int swa_3 = A2;
int swa_4 = A3;

int swb_1 = A4;
int swb_2 = A5;
int swb_3 = A6;
int swb_4 = A7;

int tmpA;
int tmpB;

int opto = 3;
int opto2 = 18;
int optoAnalogue = A14;
int detecting_opto = 0;

  int capteurLed  = A15;
  
#include "Keypad.h"
Keypad k(0x20);

#include "VariableGlobal.h"
Global g(0);

#include "EntreeSortie.h"
EntreeSortie es(input, 12, led, 12, &g); ;

#include "Affichage.h"
Affichage aff(&g, &es, &lc1, &lc2);

#include "Moteur.h"
Moteur monMoteur(&g, &aff, &es, moteur, dirMoteur, swa_1, swa_2, swa_3, swa_4, swb_1, swb_2, swb_3, swb_4);


#include "Menu.h"
Menu m(&g, &es, &k, &monMoteur);

void interuptStop() {
  Serial.println("Stop pressed interupt");
  g.stop = 1;

}


void interuptOpto()
{
  detachInterrupt(digitalPinToInterrupt(opto));




  Serial.println("Detect Opto");

  g.posAbsolue += es.dirrection();
  g.posRelatif += es.dirrection();
  aff.affichage_lc();
  attachInterrupt(digitalPinToInterrupt(opto2), interuptInteruptOpto, RISING);



}

void interuptInteruptOpto() {
  detachInterrupt(digitalPinToInterrupt(opto2));
  attachInterrupt(digitalPinToInterrupt(opto), interuptOpto, RISING);
  Serial.println("Detachage d'interupt");
}

void setup()
{
  Serial.begin(9600); // initialise connexion série à 9600 bauds
  pinMode(opto, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(b5), interuptStop, RISING);
  attachInterrupt(digitalPinToInterrupt(opto), interuptOpto, RISING);
  //attachInterrupt(digitalPinToInterrupt(opto2), interuptInteruptOpto, RISING);
  Serial.println("Ok, c'est parti");
  g.get_config();
  g.lcd_init();
  g.lcd1.print("Initialisation");
  aff.affichage_tout();
  pinMode(optoAnalogue, INPUT);
  Serial.println("calibrage Led");
 // monMoteur.calibrage();
  Serial.println("Resultat calibrage");
  Serial.println(g.ledMin);
  Serial.println(g.ledMax);


}



void loop()
{
  es.tick();
  

  if (g.posAbsolueOld != g.posAbsolue) {
    g.posAbsolueOld = g.posAbsolue;
    aff.affichage_absolue();

  }

  if (g.posRelatifOld != g.posRelatif) {
    g.posRelatifOld = g.posRelatif;
    aff.affichage_relatif();
  }

  //Serial.println(analogRead(p2));
  if(g.menu == 0){
    es.gestionLed();
    handling();
  }
  

  // Serial.println(digitalRead(opto));


  aff.affichageConditionnel();
  if(m.affichage_menu() != 0){
    aff.affichage_tout();
  }

  if (g.stop != 0) {
    g.stop = 0;
    //delay(2000);
  }
}




void handling() {
  es.etteindreLed();
  
  if ( es.testInter(2) ) {
    // B1
    if (es.testBoutonPressed(5) ) {
      // PULSE ARRIERE
      Serial.println("Pulse Arriere");
    }
    // B2
    if (es.testBoutonPressed(6)) {
      // PULSE AVANT
      Serial.println("Pulse Avant");
    }
    // B3
    if (es.testBoutonPressed(7) ) {
      while (es.testBoutonReleased(7) == 0) {
        es.tick();
        Serial.println("Pulse Arriere");
      }
    }

    if (es.testBoutonPressed(8)) {
      while (es.testBoutonReleased(8) == 0) {
        es.tick();
        // PULSE AVANT
        Serial.println("Pulse AVANT");
      }
    }
    // B6
    if ( es.testBoutonPressed(10) & g.ecritureClavier == 0 ) {
      while (g.stop != 0) {
        if (es.testAvant()) {
          // PULSE AVANT
          Serial.println("Pulse Arriere");
        } else {
          // PULSE ARRIERE
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
    }
    // B2
    if (es.testBoutonPressed(6)) {
      // IMAGE AVANT
      Serial.println("IMAGE Avant");
    }
    // B3
    if (es.testBoutonPressed(7) ) {
      while (es.testBoutonReleased(7) == 0) {
        // RECULE
        es.tick();
        Serial.println("Recule");

      }
      // IMAGE ARRIERE
      
      Serial.println("IMAGE Arriere");
    }

    if (es.testBoutonPressed(8)) {
      while (es.testBoutonReleased(8) == 0) {
        es.tick();
        // AVANCE
        Serial.println("Avance");
      }
      //IMAGE ARRIERE
      Serial.println("Une image avant");
    }
    // B6
    if ( es.testBoutonPressed(10) & g.ecritureClavier == 0 ) {

      // Absolue
      if (es.testAbsolue()) {
        // GO TO ABSOLUE TARGET
        Serial.println("GO TO ABSOLUE TARGET");

      } else {
        // GO TO RELATIF POSITION
        Serial.println("Go to relatif target");

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
      g.targetAbsolue = tmpA;
    } else {
      Serial.println("Relatif");
      g.lcd2.setCursor(0, 1);
      g.lcd2.print("Attente saisie        ");
      tmpA = m.saisieClavier(g.lcd2, 1);
      g.targetRelatif = tmpA;
    }
    Serial.println(tmpA);
    g.refresh = 1;
    g.ecritureClavier = 0;

  }

  if (g.tamponK == -1 && g.codeK == '*' && g.ecritureClavier == 0 ) {
    g.save_config();
    Serial.println("Saving config");
  }
 es.gestionLed();


}
