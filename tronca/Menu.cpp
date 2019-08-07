#include "Menu.h"


Menu::Menu(Global * g1, EntreeSortie * es1, Keypad * kp1){
  g = g1;
  es = es1;
  k = kp1;
}

int Menu::affichage_menu(){
  if(g->menu == 0){
      if(es->testEncodeur()){
        g->menu =1;
        g->posMenu = 0;
        affichageMenuFromPos(0);
      }
   } else if (g->subMenu == 0) {
       if(es->testEncodeur()){
          g->subMenu = 1;
          g->lcd1.clear();
          g->lcd1.setCursor (0,0);
       }
       g->lcd2.clear();
      encoder.tick();
      int dir = encoder.getDirection();
      if(dir != 0){
          g->posMenu += dir;
          if(g->posMenu < 0){
   
            g->posMenu = 0;
          }
          if(g->posMenu >= tailleMenu){
            g->posMenu = tailleMenu -1;
            //posMenu = 0;
          }
          affichageMenuFromPos(g->posMenu);
         
      } 
             
    } else {

      
  

  

  
  
  
        
      g->lcd2.clear();
      switch(g->posMenu){
        // Reglage de plage de vitese en continu
        case 0:
           return doubleMenu(&(g->vitesseContinuDebut), &(g->vitesseContinuFin),"Debut : ", "Fin : ");
        break;

      // Reglage de la plage image par image
        case 1:
          return doubleMenu(&g->vitesseIpIDebut,&g->vitesseIpIFin,"Debut : ", "Fin : ");
        break;

      //Nombre de pas moteur A
        case 2:
          return simpleMenu(&g->nbPasMoteurA, "Nb pas A :");
        break;
      // Nombre de pas moteur B
        case 3:
        return simpleMenu(&g->nbPasMoteurB, "Nb pas B :");
        break;
      //Pente accélération
        case 4:
        return simpleMenu(&g->PenteAcceleration, "Pente :");
        break;
  
      // Nb pulse apres desceleration        
        case 5:
        return simpleMenu(&g->nbPulseDesc, "Nb pulse");
        break;

      // Temps de pose        
        case 6:
        return simpleMenu(&g->tempsPose, "Tps pose");
        break;

      // Retour        
        case 7:
          g->menu = 0;
          g->subMenu =0;
          g->posMenu = 0;
          return 1;
        break;
       
      } 
      
      if(es->testEncodeur()){
         g->subMenu = 0;
         affichageMenuFromPos(g->posMenu);
      }
    }  
    return 0;                 
}


    

  void Menu::retourMenu(){
    g->subMenu = 0;
    affichageMenuFromPos(g->posMenu);
  }
  
  void Menu::affichageMenuFromPos(int p){
   g->lcd1.clear();
   g->lcd1.setCursor (0,0);
   g->lcd1.print(titreMenu[p]);
   if(p != tailleMenu){
     g->lcd1.setCursor (0,1);
     if(p != tailleMenu-1){
       g->lcd1.print("... suite .. ");
     }
  }

    
  }
  
 long  Menu::saisieClavier(LiquidCrystal_I2C mylcd, int hauteur){
    char entree;
    long saisie = 0;
    char tampon = -1;
    LiquidCrystal_I2C l = mylcd;

    while(es->testOk() == 0){
        es->tick();
        encoder.tick();
        
        if(es->testEncodeur()){
            return -1;
        }
        entree=tampon;
        tampon = k->get_key();
      // Serial.println(tampon);
       
    if(entree >= 48 && entree  <= 57 && tampon == -1){
        if(saisie > saisie % 100000000){
            saisie = saisie %100000000;
        }
        saisie = saisie * 10 + (entree - 48);
           l.setCursor(0,hauteur);
        l.print("                   ");
        l.setCursor(1,hauteur);
        l.print(saisie);
     // Serial.println(saisie);
    }
    if(entree == '*'){
        saisie = 0;
        l.setCursor(0,hauteur);
        l.print("                ");
        l.setCursor(1,hauteur);
        l.print(saisie);
     // Serial.println(saisie);
    }

   }
   return saisie;
  }

  
  int Menu::doubleMenu(int * a, int * b, String s1, String s2){ 
   long tmpA = 0;
   long tmpB = 0;
    g->lcd1.clear();
    g->lcd1.setCursor(0,0);
    g->lcd1.print(s1);
    g->lcd1.print(*a);
    tmpA = saisieClavier(g->lcd1,1);
        if(tmpA == -1){
             retourMenu();
        }
    g->lcd1.clear(); 
    g->lcd1.setCursor(0,0);
    g->lcd1.print(s2);
   g-> lcd1.print(*b);    
    tmpB = saisieClavier(g->lcd1,1); 
    if(tmpB == -1){
         retourMenu();
    }         
   if(tmpA < tmpB && tmpA != 0){    
        *a = tmpA;
        *b = tmpB;
        g->lcd1.clear();
        g->lcd1.setCursor(0,0);
        g->lcd1.print("Configuration faite");
        g->save_config();
        delay(1000);
        g->subMenu = 0;
        g->menu = 0;   
        return 1;
    } else if ( tmpA == 0){
        g->lcd1.clear();
        g->lcd1.setCursor(0,0);
        g->lcd1.print("Erreur");
        g->lcd1.setCursor(0,1);
        g->lcd1.print("Debut = 0");
        delay(1000);
       g-> lcd1.clear();
    } else {
       g-> lcd1.clear();
        g->lcd1.setCursor(0,0);
       g-> lcd1.print("Erreur");
       g-> lcd1.setCursor(0,1);
       g-> lcd1.print("Debut > fin");
        delay(1000);
       g-> lcd1.clear();    
    }
    return 0;
}

int Menu::simpleMenu(int *a, String s){
    long tmpA = 0; 
    g->lcd1.clear();
    g->lcd1.setCursor(0,0);
    g->lcd1.print(s);
    g->lcd1.print(*a);
    tmpA = saisieClavier(g->lcd1,1);
    if(tmpA == -1){
        retourMenu();
    }
    *a = tmpA;
    g->lcd1.clear();
    g->lcd1.print("Configuration fini");
    g->save_config();
    g->subMenu = 0;
    g->menu = 0;
    return 1;
}
