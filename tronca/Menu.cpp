#include "Menu.h"


Menu::Menu(Global * g1, EntreeSortie * es1, Keypad * kp1, Moteur * m1) {
  g = g1;
  es = es1;
  k = kp1;
  m = m1;

}






int  Menu::retourMenu() {
  g->subMenu = 0;
  affichageMenuFromPos(g->posMenu);
  return -1;
}

void Menu::affichageMenuFromPos(int p) {
  g->lcd1.clear();
  g->lcd1.setCursor (0, 0);
  g->lcd1.print(titreMenu[p]);
}

long  Menu::saisieClavier(LiquidCrystal_I2C mylcd, int hauteur) {
  char entree;
  long saisie = 0;
  char tampon = -1;
  LiquidCrystal_I2C l = mylcd;

  while (es->testOk() == 0 && g->stop == 0) {
    es->tick();
    encoder.tick();

    if (es->testEncodeur()) {
      return -1;
    }
    entree = tampon;
    tampon = k->get_key();
    // Serial.println(tampon);

    if (entree >= 48 && entree  <= 57 && tampon == -1) {
      if (saisie > saisie % 100000000) {
        saisie = saisie % 100000000;
      }
      saisie = saisie * 10 + (entree - 48);
      l.setCursor(0, hauteur);
      l.print("                   ");
      l.setCursor(1, hauteur);
      l.print(saisie);
      Serial.println(saisie);
      // Serial.println(saisie);
    }
    if (entree == '*') {
      saisie = 0;
      l.setCursor(0, hauteur);
      l.print("                ");
      l.setCursor(1, hauteur);
      l.print(saisie);
      // Serial.println(saisie);
    }

  }
  if (g->stop == 1) {
    return -1;
  }
  return saisie;
}


int Menu::doubleMenu(int * a, int * b, String s1, String s2) {
  long tmpA = 0;
  long tmpB = 0;
  g->lcd1.clear();
  g->lcd1.setCursor(0, 0);
  g->lcd1.print(s1);
  g->lcd1.setCursor(0, 1);
  g->lcd1.print(*a);
  tmpA = saisieClavier(g->lcd1, 1);
  if (tmpA == -1) {
    return retourMenu();
  }
  if (tmpA != 0) {
    *a = tmpA;
  }
  g->lcd1.clear();
  g->lcd1.setCursor(0, 0);
  g->lcd1.print(s2);
  g->lcd1.setCursor(0, 1);
  g-> lcd1.print(*b);
  tmpB = saisieClavier(g->lcd1, 1);
  if (tmpB == -1) {
    return retourMenu();
  }
  if (tmpB != 0) {
    *a = tmpA;
  }
  if (tmpA < tmpB && tmpA != 0 ) {
    *a = tmpA;
    *b = tmpB;
    g->lcd1.clear();
    g->lcd1.setCursor(0, 0);
    g->lcd1.print("Configuration faite");
    //g->save_config();


    return 1;
  } else if ( tmpA == 0) {
    g->lcd1.clear();
    g->lcd1.setCursor(0, 0);
    g->lcd1.print("Erreur");
    g->lcd1.setCursor(0, 1);
    g->lcd1.print("Debut = 0");
    delay(1000);
    g-> lcd1.clear();
  } else {
    g-> lcd1.clear();
    g->lcd1.setCursor(0, 0);
    g-> lcd1.print("Erreur");
    g-> lcd1.setCursor(0, 1);
    g-> lcd1.print("Debut > fin");
    delay(1000);
    g-> lcd1.clear();
  }
  return 0;
}

int Menu::simpleMenu(int *a, String s) {
  long tmpA = 0;
  g->lcd1.clear();
  g->lcd1.setCursor(0, 0);
  g->lcd1.print(s);
  g->lcd1.setCursor(0, 1);
  g->lcd1.print(*a);
  tmpA = saisieClavier(g->lcd1, 1);
  if (tmpA == -1) {
    return retourMenu();
  }
  if (tmpA != 0) {
    *a = tmpA;
  }
  if (g->stop == 1) {
    return 0;
  }

  g->lcd1.clear();
  g->lcd1.print("Configuration fini");
  g->refresh = 1;
  //g->save_config();

  return 1;
}


int Menu::longSimpleMenu(long * a, String s) {
  long tmpA = 0;
  g->lcd1.clear();
  g->lcd1.setCursor(0, 0);
  g->lcd1.print(s);
  g->lcd1.setCursor(0, 1);
  g->lcd1.print(*a);
  tmpA = saisieClavier(g->lcd1, 1);
  if (tmpA == -1) {
    return retourMenu();
  }
  if (tmpA != 0) {
    *a = tmpA;
  }

  g->lcd1.clear();
  g->lcd1.print("Configuration fini");
  g->refresh = 1;
  //g->save_config();

  return 1;
}

int Menu::simpleEncodeur(int nbChoix, int choix[], int * valeur, String s) {
  int posEncodeur = 0;
  int posEncodeurOld = 0;
  g->lcd1.clear();
  g->lcd1.setCursor(0, 0);
  g->lcd1.print(s);
  g->lcd1.setCursor(0, 1);
  g->lcd1.print(*valeur);


  int i = *valeur / 400;
  int bin = 0;
  int dec = 0;
  while (i >> bin != 0) {
    bin++;
  }

  posEncodeur = bin-1;
  while (g->stop == 0 && es->testEncodeur() == 0) {
    es->tick();
    encoder.tick();
    posEncodeur += encoder.getDirection();
    if (posEncodeur < 0) {
      posEncodeur = 0;
    }

    if (posEncodeur >= nbChoix) {
      posEncodeur = nbChoix - 1;
    }

    if (posEncodeur != posEncodeurOld) {
      posEncodeurOld = posEncodeur;
      g->lcd1.clear();
      g->lcd1.setCursor(0, 0);
      g->lcd1.print(s);
      g->lcd1.setCursor(0, 1);
      g->lcd1.print(choix[posEncodeur]);

    }


  }
  if (g->stop == 1) {
    g->subMenu = 0;
    g->menu = 0;
    return -1;
  }
  *valeur = choix[posEncodeur];
  Serial.println("Le choix est fait");
  Serial.println(choix[posEncodeur]);
  return 0;
}

int Menu::affichage_menu() {
  if (g->menu == 0 ) {
    if (es->testEncodeur()) {
      g->menu = 1;
      g->posMenu = 0;
      affichageMenuFromPos(0);
      es->etteindreLed();
    }
  } else if (g->subMenu == 0 ) {
    if (g->stop == 1 || es->testBoutonPressed(9)) {
      g->menu = 0;
      return -1;
    }

    if (es->testEncodeur()) {
      g->subMenu = 1;
      g->lcd1.clear();
      g->lcd1.setCursor (0, 0);
    }
    g->lcd2.clear();
    encoder.tick();
    int dir = encoder.getDirection();
    if (dir != 0) {
      g->posMenu += dir;
      if (g->posMenu < 0) {

        g->posMenu = 0;
      }
      if (g->posMenu >= tailleMenu) {
        g->posMenu = tailleMenu - 1;
        //posMenu = 0;
      }
      affichageMenuFromPos(g->posMenu);

    }

  } else {
    int res = 0;










    g->lcd2.clear();
    int valRetour = 0;
    switch (g->posMenu) {
      // Reglage de plage de vitese en continu
      
      case 0:
        // Reglage temps de pose
        res = simpleMenu(&g->tempsPose, "Temps pose en ms");

        break;
      // Calibrage Led OPTO
      case 1:
        m->calibrage();
        g->menu = 0;
        g->subMenu = 0;
        g->posMenu = 0;
        g->refresh = 1;
        break;

      // Reglage capteur
      case 2:
        res = doubleMenu(&g->ledMin, &g->ledMax, "Valeur Min", "Valeur Max");
        break;

      // Seuil
      case 3:
        res = simpleMenu(&g->seuil, "Seuil");
        break;
      // ¨Position Absolue
      case 4:
        res = longSimpleMenu(&g->posAbsolue, "Val Abs");
        break;

      case 5:

        // Reglage moteur continu

        // ¨Pas moteur
        valRetour = simpleEncodeur( sizeof(g->pasMoteurTab) / sizeof(g->pasMoteurTab[0]), g->pasMoteurTab , &g->pasMoteur, "Pas/tour");
        if (valRetour == -1) {
          return -1;
        }
        res += valRetour;
        // Vitesse Moteur
        valRetour = longSimpleMenu(&g->stepMoteurParSec, "Step Moteur/sec");
        if (valRetour == -1) {
          return -1;
        }
        res += valRetour;
        // Acceleration
        valRetour = longSimpleMenu(&g->acceleration, "Acceleration");
        if (valRetour == -1) {
          return -1;
        } 
        res += valRetour;
        // NB pas / boucle
        valRetour = simpleMenu(&g->pasParBoucle, "Pas par boucle");
        if (valRetour == -1) {
          return -1;
        } 
        res += valRetour;
        

        break;
      // Retour
      default:
        // PEtit tricks pour depasse le maximum de 8 case d'un switch
        switch (g->posMenu) {
          case 6:

            // Reglage moteur continu
            // "Position Absolue", "Moteur Continu", "Moteur IpI", "Moteur callage"};
            // ¨Pas moteur
            valRetour = simpleEncodeur( sizeof(g->pasMoteurTab) / sizeof(g->pasMoteurTab[0]), g->pasMoteurTab , &g->pasMoteurIpI, "Pas/tour IPI");
            if (valRetour == -1) {
              return -1;
            }
            res += valRetour;
            // Vitesse Moteur
            valRetour = longSimpleMenu(&g->stepMoteurParSecIpI, "Step Moteur/sec IPI");
            if (valRetour == -1) {
              return -1;
            }
            res += valRetour;
            // Acceleration
            valRetour = longSimpleMenu(&g->accelerationIpI, "Acceleration");
            if (valRetour == -1) {
              return -1;
            }
            if (valRetour == -1) {
              return -1;
            }
            res += valRetour;
            break;

          case 7:
            int valRetour = 0;
            // Reglage moteur callage
            // ¨Pas moteur
            valRetour = simpleEncodeur( sizeof(g->pasMoteurTab) / sizeof(g->pasMoteurTab[0]), g->pasMoteurTab , &g->pasMoteurCallage, "Pas/tour Callage");
            if (valRetour == -1) {
              return -1;
            }
            res += valRetour;
            // Vitesse Moteur
            valRetour = longSimpleMenu(&g->stepMoteurParSecCallage, "Step Moteur/sec Callage");
            if (valRetour == -1) {
              return -1;
            }
            res += valRetour;
            // Acceleration
            valRetour = longSimpleMenu(&g->accelerationCallage, "Acceleration");
            if (valRetour == -1) {
              return -1;
            }
            if (valRetour == -1) {
              return -1;
            }
            res += valRetour;
            break;

        }
    }

    if (es->testEncodeur()) {
      g->subMenu = 0;
      affichageMenuFromPos(g->posMenu);
    }
    delay(1000);
    g->subMenu = 0;
    g->menu = 0;
    g->refresh = 1;
    return res;

  }
  return 0;
}
