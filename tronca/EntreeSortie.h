#ifndef EntreeSortie_h
#define EntreeSortie_h
#include "VariableGlobal.h"
#include <Arduino.h>
#include <stdlib.h>



class EntreeSortie {
  private:
    // Tableau d'input
    int *input;
    int tailleInput;
    // Tableau de sortie
    int *led;
    int tailleLed;
    int etatOld;
    int p1 = A8;
    int p2 = A9;


  public:
    Global * g;
    int etat;
    int changement;
    // Fonction de declaration

    EntreeSortie(int tabInput[], int tailleTabInput, int tabLed[], int tailleTabLed, Global * g1);

    //Remet a jour l'etat et le changement
    void tick(void);

    //Rafrashi l'etat
    void refresh();

    // Met a jour la variable changement, renvoie 1 s'il y'a eu un changement, sinon 0
    void detect_input();

    // Renvoie 1 si le bouton a était relaché et supprimer l'action de l'état
    int testBoutonReleased(int bouton);

    // Renvoie 1 si le bouton a était appuyé et supprimer l'action de l'état
    int testBoutonPressed(int bouton);

    // Renvoie 1 si l'interupteur est haut, 0 sinon
    int testInter(int inter);

    // Renvoie 1 si l'interrupteur a changé d'état
    int touchInter(int inter);

    int testEncodeur();
    int testOk();
    int testAvant();
    int testContinu();
    int testPulse();
    int testCamera();
    int testAbsolue();
    int dirrection();
    int touchContinu();
    int touchAvant();
    void mapPottar(int potar, int debut, int fin, int * valeur);
    int ledOn(int nb_led);
    int ledOff(int nb_led);
    void gestionLed();
    void etteindreLed();
};


#endif
