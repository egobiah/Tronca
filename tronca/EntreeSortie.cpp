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
  mapPottar(p2,g->vitesseIpIDebut, g->vitesseIpIFin, &(g->vitesseIpI));
  gestionLed();
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

 int EntreeSortie::touchContinu(){
  return touchInter(0);
 }

 int EntreeSortie::touchAvant(){
  return touchInter(3);
 }
 
   int EntreeSortie::testPulse(){
    return testInter(2);
    
  }
 int EntreeSortie::testCamera(){
     return testInter(1);
 }

  int EntreeSortie::testAbsolue(){
     return testInter(4);
 }

 void EntreeSortie::gestionLed(){

  if(changement != 0){
    for(int i = 0; i < 10; i++){
      ledOff(led[i]);
    }
  
     // Led inter 1 ; led 0 et 1, 
     if(testContinu() && !testPulse()){
        ledOn(led[0]);
        ledOff(led[1]);
     } else {
        if(!testPulse()){
          ledOff(led[0]);
          ledOn(led[1]);
        }
     }
     
    // Led inter 2 ; led 2 et 3
     if(testCamera() && !testPulse() && !testContinu()){
        ledOn(led[2]);
        ledOff(led[3]);
     } else {
        if(!testPulse() && !testContinu()){
           ledOn(led[3]);
           ledOff(led[2]);
        
  
        }
    }
  
       // Led inter 3 ; led 4 et 5
     if(testPulse()){
        ledOn(led[4]);
        ledOff(led[5]);
     } else {
        ledOff(led[4]);
        ledOn(led[5]);
     }
  
       // Led inter 4 ; led 6 et 7
     if(testAvant()){
        ledOn(led[6]);
        ledOff(led[7]);
     } else {
        ledOff(led[6]);
        ledOn(led[7]);
     }
  
          // Led inter 4 ; led 8 et 9
     if(testAbsolue()){
        ledOn(led[8]);
        ledOff(led[9]);
     } else {
        ledOff(led[8]);
        ledOn(led[9]);
     }
  }
 }

void EntreeSortie::mapPottar(int potar, int debut, int fin, int * valeur){
    int tmpA;
    tmpA = map(analogRead(potar), 26, 1024, debut, fin);
    //Serial.println(tmpA);
   if(tmpA != *valeur){
    
    g->refreshVitesse = 1;
    *valeur = tmpA;
    Serial.println(*valeur);
   }
}

int EntreeSortie::dirrection(){
  if(testAvant()){
    return 1;  
  } else {
    return -1;
  }
}
