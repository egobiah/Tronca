#include "Affichage.h"
#include <math.h>
#include <Arduino.h>

Affichage::Affichage(Global * g1, EntreeSortie * es1, LedControl * lc_1, LedControl * lc_2){
  g = g1;  
  es = es1;
  lc1= lc_1;
  lc2= lc_2;
  lc1->shutdown(0,false);
  /* Set the brightness to a medium values */
  lc1->setIntensity(0,8);
  /* and clear the display */

    lc2->shutdown(0,false);
  /* Set the brightness to a medium values */
  lc2->setIntensity(0,8);
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
  intToLed(g->posAbsolue,lc1);
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
  intToLed(g->posRelatif,lc2);
  
  


  

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

void Affichage::intToLed(long num, LedControl * lc){
  lc->clearDisplay(0);
  int i = 0;
  int tmpLed = 0;
  int negatif = (num < 0);
  if(negatif){
     
    lc->setRow(0,i+1,0b00000001);
     num = -num;
  }
  
  if(num == 0){
    lc->setDigit(0,0,0,0);
  }
  while(num != 0){
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

void Affichage::affichage_lc(){
  intToLed(g->posAbsolue,lc1);
  intToLed(g->posRelatif,lc2);
}
