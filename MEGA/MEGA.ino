

//-------------------librairies
#include <string.h>
#include <math.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
LiquidCrystal_I2C lcd1(0x21, 16, 2);      //adresse,16 caractères, 2 lignes.
LiquidCrystal_I2C lcd2(0x22, 16, 2);

#include <RotaryEncoder.h>
RotaryEncoder encoder(46, 47);

int adresse = 0;
int adresseCible = 0;

int avanceRelatif = 0;
int indexAvanceRelatif = 0;

int menu = 0;
int subMenu = 0;
int posMenu;
#define tailleMenu 8
char titreMenu[8][256] = {"Plage vitesse Continu", "plage image par image", "Nb pas moteur A", "Nb pas moteur B", "Pente acceleration", "nb pulse apres desc", "temps de pose", "retour <--"};
int changement;

//-------------------variables globales


// Déclaration des les d'interupteurs

int i1T = 32; 
int i1B = 33;
int i2T = 34;
int i2B = 35;
int i3T = 36;
int i3B = 37;
int i4T=28;
int i4B=29;
int i5T=30;
int i5B=31;
 
// Déclaration des interupteurs
int i1 = 49;
int i2 = 40;
int i3 = 41;
int i4 = 38;
int i5 = 38;
// Declaration de l'encodeur
int encodeur = 45;
// Declaration des boutons
int b5 = 2;
int b1 = 22;
int b2 = 23;
int b3 = 24;
int b4 = 25; 
int b6 = 26;
// Potar
int p1 = A8;
int p2 = A9;
// Jack
int vert = 11;
int rouge =12;
int led[12] = {i1T,i1B, i2T, i2B, i3T, i3B, i4T, i4B,i5T, i5B, vert, rouge};
int input[12] = {i1, i2, i3, i4, i5, b1, b2, b3, b4, b5, b6, encodeur};
// 
int etat = 0;
int lastState = 0;
//
int refresh = 1; 
int refreshVitesse = 1;


// Différents réglages
int refreshConfig = 0;
int posConfig = 0;
int vitesseContinuDebut = 1;
int vitesseContinuFin = 100;
int vitesseContinu = 1;

int vitesseIpIDebut = 1;
int vitesseIpIFin = 100;
int vitesseIpI = 1;

int  *vitesse[2] = {&vitesseIpI, &vitesseContinu}; 

int nbPasMoteurB = 1;
int nbPasMoteurA = 1;

int PenteAcceleration = 1;
int nbPulseDesc = 1;
int tempsPose = 1;

//
long posAbsolue = 0;
unsigned long targetAbsolue = 10;
long posRelatif = 0;
long targetRelatif = 123;



//
long tmpA;
long tmpB;
char tmpAff;

char codeK;
char tamponK = -1;

int ecritureClavier = 0;

#include <SPI.h>
#include <SD.h>

File myFile;

#define nb_arg_file 8
int * arg_file[10] = {&vitesseContinuDebut, &vitesseContinuFin, &vitesseIpIDebut, &vitesseIpIFin, &nbPasMoteurA, &PenteAcceleration, &nbPulseDesc, &tempsPose};

  


void setup() 
{
    Serial.begin(9600); // initialise connexion série à 9600 bauds
    // Initialisation des Leds
    for(int i = 0; i < sizeof(led)/sizeof(led[0]) ; i++){
        pinMode(led[i], OUTPUT);
        ledOn(led[i]);
        delay(100);
        ledOff(led[i]); 
    }
    // Initialisations des interrupteurs
    pinMode (i1, INPUT);
    pinMode (i2, INPUT);
    pinMode (i3, INPUT);
    pinMode (i4, INPUT);
    pinMode (i5, INPUT);
    // Initialisation des potentiomètres
    pinMode (p1, INPUT);    
    pinMode (p2, INPUT);
    // Initialisation de l'encodeur
    pinMode (encodeur, INPUT);
    digitalWrite(encodeur,true);
    // Initialisation lcd1 et lcd2
    lcd1.init();       
    lcd2.init();        
    lcd1.backlight();   // Allume l'écran 1
    lcd2.backlight();   // Allume l'écran 2
    affichage_absolue();
    affichage_relatif();

    // READ DATA FROM FILE

    pinMode(53, OUTPUT);
    if (!SD.begin(53)) {
        Serial.println("initialization failed!"); 
    } 
    get_config();
}



void loop() 
{
   etat = get_entry();
   changement = detect_input();
    if(changement != 0){
    Serial.println(changement);
    }
   set_led_output();
   refresh = affichage_menu();
   affichage_classique();
   handling();









 
}

int get_config(){
    myFile = SD.open("config.txt", FILE_READ);
    for(int i = -1; i <=  nb_arg_file; i++){
        char c = myFile.read();
        tmpA = 0;
        while(c != ";"){
            tmpA = tmpA * 10 + c - 49;
        }
        if(i == -1){
            posAbsolue = tmpA;
        } else {
            *arg_file[i] = tmpA;
        }
    }
    myFile.close();
    return 0;
}

int save_config(){
  SD.remove("config.txt");
  myFile = SD.open("TEST.TXT", FILE_WRITE);
  myFile.print(posAbsolue);
  myFile.print(";");
  for(int i = 0; i <= nb_arg_file; i++){
      myFile.print(*arg_file[i]);
      myFile.print(";");
  }
  myFile.close();
  return 0;

}

int ledOn(int nb_led){
  digitalWrite (nb_led, HIGH);
}

int ledOff(int nb_led){
  digitalWrite (nb_led, LOW);
}


int get_entry(void){
/*
   i1 = 0b1
   i2 = 0b10
   i3 = 0b100
   i3 = 0b1000
   i4 = 0b10000
   i4 = 0b100000
   i5 = 0b1000000
   
   b1 = 0b10000000
   b2 = 0b100000000
   b3 = 0b1000000000
   b4 = 0b10000000000
   b5 = 0b100000000000
   b6 = 0b1000000000000
   
*/  
  int entry = 0;
  
  for(int i = 0; i < sizeof(input)/sizeof(input[0]) ; i++){
    if(digitalRead(input[i])){
      entry = entry | (1 << i);
    }
  }
//  Serial.println(entry);
  return entry; 
}

void set_led_output(void){
  
  int output = 0;
  for(int i = 0; i < 5; i++){
    if((etat >> i) & 1){
        output = output | 1 << 2*i;
    } else {
      output = output | 1 << 2*i +1;
    }
  }
//  Serial.println(output);
  if(etat & 1){
    ledOn(i1T);
    ledOff(i1B);
    ledOff(i2T);
    ledOff(i2B);
    for(int i = 4; i < sizeof(led)/sizeof(led[0]) ; i++){
      digitalWrite(led[i], (output >> i )& 1);  
    }
     
  } else {
    for(int i = 0; i < sizeof(led)/sizeof(led[0]) ; i++){
      digitalWrite(led[i], (output >> i )& 1);  
    } 
  }
}

int detect_input(){
  int  diff = 0;
  if(etat != lastState){
     // Serial.println(etat);
        diff = lastState ^ etat;
      if(etat & diff){
        diff = -diff;
      }
        
      lastState = etat;
        
   }
   return diff;
}

int testInter(int pin){
  return etat >> pin & 1;
  
}

int testBoutonReleased(int pin){
  int complement;
  int res = 0;
  if(((changement >> pin) & 1) && changement > 0){
    res = 1 ;
    complement = 1 << pin;
    complement = ~complement;
    changement = changement & complement;
  }
  return res;
  
}

int testBoutonPressed(int pin){
  int complement;
  int a2 = ~changement+1 ;
  int res = 0;
  if(((a2 >> pin) & 1) && changement < 0){
    res = 1 ;
    
    complement = 1 << pin;
    a2 = changement + complement;
    //changement = changement & complement;
    changement = a2;
  }
  return res;
  
}

int testTouchInter(int pin){
  return testBoutonReleased(pin) | testBoutonPressed(pin);
}
int testAbsolue(void){
  return testInter(2);
  
}

int testAvant(void){
  return testInter(3);
}

int touchAvant(){
  return(testTouchInter(3));
  
}

int touchContinu(void){
  return testTouchInter(0);
}
int testContinu(void){
  return testInter(0);
}



int testOk(void){
 
  return  testBoutonPressed (10);
}

int testEncodeur(void){
  return testBoutonReleased(11);
}

void affichageMenuFromPos(int t){
  lcd1.clear();
  lcd1.setCursor (0,0);
  lcd1.print(titreMenu[t]);
  if(t != tailleMenu){
    lcd1.setCursor (0,1);
    lcd1.print("... suite .. ");

  }
}

int retourMenu(void){
  subMenu = 0;
  affichageMenuFromPos(posMenu);
  return 0;
}

int affichage_menu(){
  if(menu == 0){
      if(testEncodeur()){
        menu =1;
        posMenu = 0;
        affichageMenuFromPos(0);
      }
   } else if (subMenu == 0) {
       if(testEncodeur()){
          subMenu = 1;
          refreshConfig = 1;
          lcd1.clear();
          lcd1.setCursor (0,0);
       }
       lcd2.clear();
      encoder.tick();
      int dir = encoder.getDirection();
      if(dir != 0){
          posMenu += dir;
          if(posMenu < 0){
            //posMenu = tailleMenu -1;
            posMenu = 0;
          }
          if(posMenu >= tailleMenu){
            posMenu = tailleMenu -1;
            //posMenu = 0;
          }
          affichageMenuFromPos(posMenu);
          Serial.println(posMenu); 
      } 
             
    } else {

      
  

  

  
  
  
        
      lcd2.clear();
      switch(posMenu){
        // Reglage de plage de vitese en continu
        case 0:
           return doubleMenu(&vitesseContinuDebut, &vitesseContinuFin,"Debut : ", "Fin : ");
        break;

      // Reglage de la plage image par image
        case 1:
          return doubleMenu(&vitesseIpIDebut,&vitesseIpIFin,"Debut : ", "Fin : ");
        break;

      //Nombre de pas moteur A
        case 2:
          return simpleMenu(&nbPasMoteurA, "Nb pas A :");
        break;
      // Nombre de pas moteur B
        case 3:
        return simpleMenu(&nbPasMoteurB, "Nb pas B :");
        break;
      //Pente accélération
        case 4:
        return simpleMenu(&PenteAcceleration, "Pente :");
        break;
  
      // Nb pulse apres desceleration        
        case 5:
        return simpleMenu(&nbPulseDesc, "Nb pulse");
        break;

      // Temps de pose        
        case 6:
        return simpleMenu(&tempsPose, "Tps pose");
        break;

      // Retour        
        case 7:
          menu = 0;
          subMenu =0;
          posMenu = 0;
          return 1;
        break;
       
      } 
      
      if(testEncodeur()){
         subMenu = 0;
         affichageMenuFromPos(posMenu);
      }
    }  
    return 0; 
}

void affichage_classique(){
  if(refresh){
    Serial.println("Refresh");
    affichage_absolue();
    affichage_relatif();
    refresh = 0;
  }
}

int get_code(){
    int resC;
    int resR;
    int colo = 32+128+8;
    int rowo = 64+2+4+16;
    int p;
    int res;
    Wire.beginTransmission(0x20);
    Wire.write(colo);
    Wire.endTransmission();
    Wire.requestFrom(0x20, 1);
    if(Wire.available()) {
        int p = Wire.read();
        if(p != colo){  // Serial.println(p);
            resC = p;
        }
    }

    Wire.beginTransmission(0x20);
    Wire.write(rowo);
    Wire.endTransmission();
    Wire.requestFrom(0x20, 1);
    if(Wire.available()) {
        int p = Wire.read();
        if(p != rowo){
              //Serial.println(p);
            resR = p;
        }
    }
 
    res = resC*100+resR;
    if(res == colo*100 +rowo){
        res = -1;
    }
  //Serial.println(res);
  return res;
}

char get_keypad(){
    char key;
    int code = get_code();
    //Serial.println(code);
    switch(code){
        case 13622:key = '1'; break;
        case 13684: key = '4'; break;
        case 13682: key='7'; break;
        case 13670: key ='*'; break;
        case 4022:key='2'; break;
        case 4084:key='5';break;
        case 4082:key='8';break;
        case 4070:key='0';break;
        case 16022:key='3';break;
        case 16084:key='6';break;
        case 16082:key='9';break;
    default:
        // Trop de "case" dans le switch, le dernier est alors ici
        if(code == 16070){
            key='#';
        } else {
            key = -1;    
        }
    break;
  }
  return key;
}


long saisieClavier(LiquidCrystal_I2C mylcd, int hauteur){
    char entree;
    long saisie = 0;
    char tampon = -1;
    LiquidCrystal_I2C l = mylcd;

    while(testOk() == 0){
        etat = get_entry();
        encoder.tick();
        changement = detect_input();
        if(testEncodeur()){
            return -1;
        }
        entree=tampon;
        tampon = get_keypad();
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
// Fonction permettant d'integrer un menu a double entrée
// A = Premiere Variable, B = 2eme varianle, S1 = string for a, S2 = string for b,
int doubleMenu(int * a, int * b, String s1, String s2){ 
    tmpA = 0;
    tmpB = 0;
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print(s1);
    lcd1.print(*a);
    tmpA = saisieClavier(lcd1,1);
        if(tmpA == -1){
            return retourMenu();
        }
    lcd1.clear(); 
    lcd1.setCursor(0,0);
    lcd1.print(s2);
    lcd1.print(*b);    
    tmpB = saisieClavier(lcd1,1); 
    if(tmpB == -1){
        return retourMenu();
    }         
   if(tmpA < tmpB && tmpA != 0){    
        *a = tmpA;
        *b = tmpB;
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("Configuration faite");
        save_config();
        delay(1000);
        subMenu = 0;
        menu = 0;   
        return 1;
    } else if ( tmpA == 0){
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("Erreur");
        lcd1.setCursor(0,1);
        lcd1.print("Debut = 0");
        delay(1000);
        lcd1.clear();
    } else {
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("Erreur");
        lcd1.setCursor(0,1);
        lcd1.print("Debut > fin");
        delay(1000);
        lcd1.clear();    
    }
    return 0;
}

int simpleMenu(int *a, String s){
    tmpA = 0; 
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print(s);
    lcd1.print(*a);
    tmpA = saisieClavier(lcd1,1);
    if(tmpA == -1){
        return retourMenu();
    }
    *a = tmpA;
    lcd1.clear();
    lcd1.print("Configuration fini");
    save_config();
    subMenu = 0;
    menu = 0;
    return 1;
}





void affichage_absolue(){
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("@");
  lcd1.print(posAbsolue);
  lcd1.setCursor(0,1);
  lcd1.print(targetAbsolue);
  
}

void affichage_vitesse(){
  if(refresh == 1 ||   refreshVitesse == 1 ){
      lcd2.setCursor(9,0);
      lcd2.print("     ");
      if(*vitesse[testContinu()] == 1){
      lcd2.setCursor(13,0);
      lcd2.print("1ms");
    } else {
      lcd2.setCursor(14-ceil(log10(*vitesse[testContinu()])),0);
      lcd2.print(*vitesse[testContinu()]);
      lcd2.print("ms");
  }
  refreshVitesse = 0;
  }
}


void affichage_relatif(){
  Serial.println("affichage R");
  lcd2.clear();
  lcd2.setCursor(0,0);
  lcd2.print("R");
  lcd2.print(posRelatif);

  

  affichage_vitesse();
  lcd2.setCursor(0,1);
  lcd2.setCursor(0,1);
  if(!testAvant()){
    lcd2.print("-");
  } else {
    lcd2.print("+");
  }
  lcd2.setCursor(1,1);
  lcd2.print(targetRelatif);

}

void handling(){

   tmpA = map(analogRead(p1), 26, 1024, vitesseContinuDebut, vitesseContinuFin);
   if(tmpA != vitesseContinu){
    Serial.println(vitesseContinu);
    refreshVitesse = 1;
    affichage_vitesse();
    vitesseContinu = tmpA;
   }
   tmpA = map(analogRead(p2), 26, 1024, vitesseIpIDebut, vitesseIpIFin);
    if(tmpA != vitesseIpI){
     Serial.println(vitesseIpI);
    refreshVitesse = 1;
    affichage_vitesse();
    vitesseIpI = tmpA;
   }
 // delay(700);
   
   
   if(testBoutonPressed(5)){
      Serial.print("1 image arrière :)");
   } 
   if(testBoutonPressed(6)){
      Serial.println("1 image avant");
   }
   if(testBoutonPressed(7)){
      Serial.println("Avance Rapide");
   } 
   if(testBoutonPressed(8)){
      Serial.println("Arrière rapide");
   }
   if(testBoutonPressed(9)){
      Serial.println("Stop");
   }

    if(testBoutonPressed(10)){
      Serial.println("Go");
   }

   if(touchContinu()){
      refreshVitesse = 1;
      affichage_vitesse();
      Serial.println("Continu touch");
   }

   if(touchAvant()){
    Serial.print("Avant");
    refresh = 1;
    
  }
   codeK = tamponK;
   tamponK = get_keypad();
   
 
   if( tamponK == -1 && codeK == '#'){
      int entreeClavier;
      ecritureClavier = 1;
      if(testAbsolue()){
        Serial.println("absolu");
        lcd1.setCursor(0,1);
        lcd1.print("Attente saisie        ");
        tmpA = saisieClavier(lcd1,1);
        targetAbsolue = tmpA;
      } else {
        Serial.println("Relatif");
        lcd2.setCursor(0,1);
        lcd2.print("Attente saisie        ");
        tmpA = saisieClavier(lcd2,1);
        targetRelatif = tmpA;
      }
        Serial.println(tmpA);
        refresh = 1;
      ecritureClavier = 0;
     
   } 

   if(tamponK == -1 && codeK == "*" && ecritureClavier == 0){
    save_config();
   }

  affichage_classique();
}
