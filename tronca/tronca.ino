#define cs_SD 53
#include <string.h>
#include <math.h>

#include <Wire.h>
#include <string.h>


int cs_led = 48;
#include "src/LedControl.h"
LedControl lc=LedControl(44,52,48,2);




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
int i4T=28;
int i4B=29;
int i5T=30;
int i5B=31;
 
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
int rouge =12;
int led[12] = {i1T,i1B, i2T, i2B, i3T, i3B, i4T, i4B,i5T, i5B};
int input[12] = {i1, i2, i3, i4, i5, b1, b2, b3, b4, b5, b6, encodeur};
//
#include "Keypad.h"
Keypad k(0x20);

#include "VariableGlobal.h"
Global g(cs_SD);

#include "EntreeSortie.h"
EntreeSortie es(input,12,led,12); ;

#include "Menu.h"
Menu m(&g, &es, &k);

#include "Affichage.h"
Affichage aff(&g, &es, &lc);

void interuptStop(){
  Serial.println("Stop pressed interupt");

}

void setup() 
{
    Serial.begin(9600); // initialise connexion série à 9600 bauds
     attachInterrupt(digitalPinToInterrupt(b5), interuptStop, RISING);
    Serial.println("Ok, c'est parti");
    g.get_config();
    Serial.println(g.posAbsolue);
     
  g.lcd_init();
  g.lcd1.print("Initialisation");
  aff.affichage_tout();
}



void loop() 
{

es.tick();








}
