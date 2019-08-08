#include "Affichage.h"
#include <math.h>
#include <Arduino.h>

Affichage::Affichage(Global * g1, EntreeSortie * es1, LedControl * lc1){
  g = g1;  
  es = es1;
  lc= lc1;
  lc->shutdown(0,false);
  /* Set the brightness to a medium values */
  lc->setIntensity(0,8);
  /* and clear the display */
}

void Affichage::affichage_absolue(){
  if(g->menu == 0){
    g->lcd1.clear();
    g->lcd1.setCursor(0,0);
    g->lcd1.print("@");
    g->lcd1.print(g->posAbsolue);
    g->lcd1.setCursor(0,1);
    g->lcd1.print(g->targetAbsolue);
  }
  intToLed(g->posAbsolue);
  g->refreshAbsolue = 0;
  
  
}

void Affichage::affichage_vitesse(){
      int * vitesse = g->vitesse[es->testContinu()];
      g->lcd2.setCursor(9,0);
      g->lcd2.print("     ");
      if(*vitesse == 1){
         g->lcd2.setCursor(13,0);
         g-> lcd2.print("1ms");
    } else {
      g->lcd2.setCursor(14-ceil(log10(*vitesse)),0);
      g->lcd2.print(*vitesse);
      g->lcd2.print("ms");
  }

  
  g->refreshVitesse = 0;
}

void Affichage::affichage_relatif(){
  
    
  
  
  g->lcd2.clear();
  g->lcd2.setCursor(0,0);
  g->lcd2.print("R");
  g->lcd2.print(g->posRelatif);
  
  


  

  affichage_vitesse();
  g->lcd2.setCursor(0,1);
  g->lcd2.setCursor(0,1);
  if(!es->testAvant()){
    g->lcd2.print("-");
  } else {
    g->lcd2.print("+");
  }
  g->lcd2.setCursor(1,1);
  g->lcd2.print(g->targetRelatif);
  g->refreshRelatif = 0;
}

void Affichage::intToLed(long num){
  lc->clearDisplay(0);
  int i = 0;
  int tmpLed = 0;
  if(num == 0){
    lc->setDigit(0,0,0,0);
  }
  while(num > 0){
    tmpLed = num%10;
    lc->setDigit(0,i,tmpLed,0);
    num = num/10;
    i++;
  }

}

void Affichage::affichage_tout(){
  affichage_absolue();
  affichage_relatif();
}  

void Affichage::affichageConditionnel(){
  if(g->refresh){
    affichage_tout();
    g->refresh = 0;
  }

  if(g->refreshVitesse){
    affichage_vitesse();
    g->refreshVitesse = 0;
  }

  if(g->refreshAbsolue){
    affichage_absolue();
    g->refreshAbsolue = 0;
  }

  if(g->refreshRelatif){
    affichage_relatif();
    g->refreshRelatif = 0;
  }
  
}
