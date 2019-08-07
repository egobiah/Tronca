#include "EntreeSortie.h"
#include <stdlib.h>
#include <arduino.h>
EntreeSortie::EntreeSortie(int tabInput[], int tailleTabInput, int tabLed[], int tailleTabLed){
   // A voir si je peux pas tout simplement remplacer par un sizeof mais vu que c'est passé en paramètre....    input = malloc(tailleTabInput * sizeof(int));
    free(led);
    led = (int *) malloc(tailleTabLed * sizeof(int));
    for(int i = 0; i < tailleTabInput; i++){
      input[i] = tabInput[i];
    }
    for(int i = 0; i < tailleTabLed; i++){
      led[i] = tabLed[i];
    }
    tailleInput = tailleTabInput;
    tailleLed = tailleTabLed;
    etat = 0;
    etatOld = 0;
    changement = 0;      
}

void EntreeSortie::tick(){
  refresh();
  detect_input();
}

//Remet a jour l'etat
void EntreeSortie::refresh(void){
   etat = 0;  
   for(int i = 0; i < tailleInput ; i++){
       if(digitalRead(input[i])){
          etat = etat | (1 << i);
       }
   }
}



void EntreeSortie::detect_input(){
    changement = 0;
    if(etat != etatOld){
       changement = etatOld ^ etat;
       if(etat & changement){
          changement = -changement;
       }
       etatOld = etat; 
    }  
 }
  

int EntreeSortie::testBoutonReleased(int bouton){
   int complement;
   int res = 0;
   if(((changement >> bouton) & 1) && changement > 0){
      res = 1 ;
      complement = 1 << bouton;
      complement = ~complement;
      changement = changement & complement;
   }
   return res;
}

int EntreeSortie::testBoutonPressed(int bouton){
  int complement;
  int a2 = ~changement+1 ;
  int res = 0;
  if(((a2 >> bouton) & 1) && changement < 0){
    res = 1 ;
    complement = 1 << bouton;
    a2 = changement + complement;
    changement = a2;
  }
  return res;
}

int EntreeSortie::testInter(int inter){
   return etat >> inter & 1;
}

int EntreeSortie::touchInter(int inter){ 
   return testBoutonPressed(inter) | testBoutonReleased(inter);
}
