#include <SPI.h>
#include <SD.H>
#include "VariableGlobal.h" 


Global::Global(int pin){
  cs_sd = pin;  
 
}

void Global::lcd_init(){
  lcd1.init();
  lcd2.init();
  lcd1.backlight();
  lcd2.backlight();
}

int Global::get_config(){
  int tmp;
  File myFile;
  
    if (!SD.begin(cs_sd)) {
        Serial.println("initialization failed!"); 
        return 1;
           
     }
    
    
    myFile = SD.open("config.txt", FILE_READ);
      if(myFile != 0){
        for(int i = -1; i <  nb_arg_file; i++){
          Serial.println("Getting files");
            char c = myFile.read();
            tmp = 0;
            while(c != ';'){
             // Serial.println(c);
                tmp = tmp * 10 + c - 48;
                c = myFile.read();
            }
            //Serial.println(tmpA);
            if(i == -1){
                posAbsolue = tmp;
            } else {
                *arg_file[i] = tmp;
            }
        }
        Serial.println("test pointeur debut");
        Serial.println(*arg_file[0]);
        Serial.println(vitesseContinuDebut);
        myFile.close();

      SD.end();
    SPI.end();

        return 0;
      }
}


int Global::save_config(){
  File myFile;
    if (!SD.begin(cs_sd)) {
        Serial.println("initialization failed!"); 
        return 1;
    }
 
  SD.remove("config.txt");
  myFile = SD.open("config.txt", FILE_WRITE);
  myFile.print(posAbsolue);
  myFile.print(";");
  for(int i = 0; i < nb_arg_file; i++){
      myFile.print(*arg_file[i]);
      myFile.print(";");
  }
  myFile.close();
  Serial.println("Config sauvegatdee");

  SD.end();
    SPI.end();

  return 0;

}
