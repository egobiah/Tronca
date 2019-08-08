#include "Moteur.h"

  Moteur::Moteur(Global * g1, Affichage * a1, EntreeSortie * es1, int pinMoteur, int pinDirMoteur, int pin_swa_1, int pin_swa_2, int pin_swa_3, int pin_swa_4,  int pin_swb_1, int pin_swb_2, int pin_swb_3, int pin_swb_4){
      g = g1;
      a = a1;
      moteur =pinMoteur;
      dirMoteur = pinDirMoteur;
      es = es1;
    
      swa_1 = pin_swa_1;
      swa_2 = pin_swa_2;
      swa_3 = pin_swa_3;
      swa_4 = pin_swa_4;
    
      swb_1 = pin_swb_1;
      swb_2= pin_swb_2;
      swb_3 = pin_swb_3;
      swb_4 = pin_swb_4;
  }
  void Moteur::pulseAvant(){
    Serial.println("1 pulse Avant");
  }
  void Moteur::pulseArriere(){
    Serial.println("1 pulse Arrière");
  }

  void Moteur::callage(){
    Serial.println("Callage");
  }

  void Moteur::imageAvant(){
    Serial.println("Une image Avant");
    g->posRelatif++;
    g->posAbsolue++;
    callage();
    delay(g->tempsPose);
    a->affichage_tout();
  }
  void Moteur::imageArriere(){
    Serial.println("Une image Arriere");
    g->posRelatif--;
    g->posAbsolue--;
    if(g->posAbsolue < 0){
      g->posAbsolue = 0;
      
    } 
      callage();
      a->affichage_tout();
     delay(g->tempsPose);
  }
  
  void Moteur::goToAbsolue(){
    Serial.println("C'est parti pour aller en absolue: ");
    Serial.println(g->targetAbsolue);
    while(g->targetAbsolue != g->posAbsolue && g->stop == 0){
        if( (g->targetAbsolue - g->posAbsolue) > 0 ){
          imageAvant();
          
        } else {
          imageArriere();
        }
        
           
    }
  }
  void Moteur::goToRelatif(){
    Serial.println("C'est parti pour aller en relatif :");
    Serial.println(g->targetRelatif);
    int i = 0;
    if(!es->testAvant()){
      
      //i = -i;
      Serial.println("Goto Arriere");
      Serial.println(i);
    }
    while(g->targetRelatif  != i  && g->stop == 0){
      
      if( (i - g->targetRelatif ) < 0 ){
          imageAvant();
          i++;
          
        } else {
          imageArriere();
          i--;
        }
    }
    
  }
