#ifndef Keypad_h
#define Keypad_h

#include <Arduino.h>

class Keypad {
  private :
    int I2C_KEYPAD;

   public :
    // int adresse = adresse I2C du clavier 4*3
    Keypad(int adresse); 
    
    // Renvoie le hash de l'entier écris au clavier
    int get_code(); 

    // Traduit 
    char decode(int code);

    char get_key();
  
};

#endif
