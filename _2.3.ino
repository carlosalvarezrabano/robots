#include <Keypad.h>

//leds: 
int ledVerde=9;
int ledRojo=8;
int led13=13;

//tiempo
double inicioCuentaTiempo=0;
double inicioTiempoPass=0;
boolean abierta=false;

//Contraseña
char pass[]= {'5','4','1','2'};
int auxPass=0;
boolean ledPass = false;

//teclado
const byte nfilas = 4;
const byte ncolumnas =4;
char teclas[nfilas][ncolumnas] = {{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'},
};
byte pfilas[nfilas]={2,3,4,5};// Filas
byte pcolumnas[ncolumnas]={A0,A1,A2,A3};
Keypad teclado =Keypad(makeKeymap(teclas),pfilas,pcolumnas,nfilas,ncolumnas);

 void setup() {
    Serial.begin(9600);
    pinMode(ledVerde,OUTPUT);
    pinMode(ledRojo,OUTPUT);
  pinMode(led13,OUTPUT);
  digitalWrite(ledRojo,HIGH);

}

 void loop() {
    
    char tecla = teclado.getKey();

  //Introduciendo contraseña
if(!abierta && tecla!='\0'){ //si esta cerrada e introducimos una tecla 
    if((tecla == pass[auxPass])){
    auxPass++;  
    Serial.println("Tecla correcta");
    if(auxPass==4){
      digitalWrite(ledVerde,HIGH);
      digitalWrite(ledRojo, LOW);
      inicioCuentaTiempo= millis();
      ledPass=true;
      abierta=true;
      auxPass=0;
      digitalWrite(led13,HIGH);
        Serial.println("Correcto");
    }
  }else{  //contraseña falsa
    int n=3; 
    auxPass=0;
    while(n!=0){ //repetir 3 veces
      digitalWrite(led13,HIGH);
      delay(500);
      digitalWrite(led13,LOW);
      delay(250);
      n = n-1;
    }
  }
}

//si el led de contraseña correcta sigue encendido
if(ledPass &&(millis() -inicioCuentaTiempo) >=1000){
    digitalWrite(led13,LOW);
    ledPass=false;
}
 
//si la puerta esta abierta
if(abierta){
// si se pulsa c
  if((tecla == 'c' || tecla =='C') ){
      digitalWrite(ledRojo,HIGH);
      digitalWrite(ledVerde,LOW);
      abierta=false;
      Serial.println("CERRADO POR PULSACION");
    }
    //si ha pasado 5 segundos
    if((millis() - inicioCuentaTiempo) >=5000){
      digitalWrite(ledRojo,HIGH);
      digitalWrite(ledVerde,LOW);
      abierta=false;
      Serial.println("CERRADO POR TEMPORIZADOR");
    }
  }

}

