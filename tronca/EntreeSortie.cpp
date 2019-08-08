#include "EntreeSortie.h"



EntreeSortie::EntreeSortie(int tabInput[], int tailleTabInput, int tabLed[], int tailleTabLed, Global * g1){
   // A voir si je peux pas tout simplement remplacer par un sizeof mais vu que c'est passé en paramètre....    input = malloc(tailleTabInput * sizeof(int));
 
    //free(led);
    g = g1;
    led = (int *) malloc(tailleTabLed * sizeof(int));
    input = (int *) malloc(tailleTabInput * sizeof(int));
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

      for(int i = 0; i < tailleLed ; i++){
        pinMode(led[i], OUTPUT);
         
    }

      for(int i = 0; i < tailleInput; i++){
        pinMode(input[i], INPUT); 
    }
    // Initialisation de l'encodeur
    digitalWrite(45,true);
}

void EntreeSortie::tick(){
  refresh();
  detect_input();
  mapPottar(p1,g->vitesseContinuDebut, g->vitesseContinuFin, &(g->vitesseContinu));
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

int EntreeSortie::testEncodeur(){
   return testBoutonReleased(11);
}

int EntreeSortie::testOk(){
   return  testBoutonPressed(10);
}

int EntreeSortie::ledOn(int nb_led){
  digitalWrite (nb_led, HIGH);
}

int EntreeSortie::ledOff(int nb_led){
  digitalWrite (nb_led, LOW);
}

  int EntreeSortie::testAvant(){
    return testInter(3);
    
  }
    int EntreeSortie::testContinu(){
        return testInter(0);

      
    }

void EntreeSortie::mapPottar(int potar, int debut, int fin, int * valeur){
    int tmpA;
    tmpA = map(analogRead(potar), 26, 1024, debut, fin);
   if(tmpA != *valeur){
    Serial.println(*valeur);
    g->refreshVitesse = 1;
    *valeur = tmpA;
   }
}
