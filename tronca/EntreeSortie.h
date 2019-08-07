#ifndef EntreeSortie_h
#define EntreeSortire_h 

class EntreeSortie{
  private:
    // Tableau d'input
    int *input;
    int tailleInput;
    // Tableau de sortie
    int *led;
    int tailleLed;
    int etatOld;
    

  public:
    int etat;    
    int changement;
    // Fonction de declaration  
    EntreeSortie(int tabInput[], int tailleTabInput, int tabLed[], int tailleTabLed);

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
};


#endif
