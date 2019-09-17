#include <Keypad.h>

//leds: 
int ledVerde=2;
int ledRojo=3;

//tiempo
double inicioCuentaTiempo=0;
boolean abierta=false;

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

}

 void loop() {
	digitalWrite(ledRojo,HIGH);
  	char tecla = teclado.getKey();

	//si se pulsa a y esta cerrada
  	if((tecla == 'a' || tecla =='A') && !abierta){
		digitalWrite(ledVerde,HIGH);
		inicioCuentaTiempo= millis();
		abierta=true;
   	 	Serial.println("ABRIR");
 // si se pulsa c y esta abierta 
}else if((tecla == 'c' || tecla =='C') && abierta){
		digitalWrite(ledRojo,HIGH);
		digitalWrite(ledVerde,LOW);
		abierta=false;
		Serial.println("CERRADO POR PULSACION");
}
	//si ha pasado 5 segundos y esta abierta 
	if((millis() - inicioCuentaTiempo) >=5000 && abierta){
		digitalWrite(ledRojo,HIGH);
		digitalWrite(ledVerde,LOW);
		abierta=false;
		Serial.println("CERRADO POR TEMPORIZADOR");
}

}