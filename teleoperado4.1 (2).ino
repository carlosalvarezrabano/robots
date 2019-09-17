
#include <Servo.h>


#define boton_pin 9 // pin digital para el botón, hay que cambiar el modo del pin,
                    //asegurar que ese pin de la placa lo permite
#define X_pin A0 // pin analógico para leer eje X
#define Y_pin A1 // pin analógico para leer eje Y

#define PIN_SERVO  8
#define PIN_DETECTOR_COLISION  6 //final de carrera -> digitalRead(PIN_DETECTOR_COLISION)

Servo servo1; //PIN 8

/*
 * ORDENES SERVO:
 * 0 = sentido antihorario
 * 180 = sentido horario
 * 90 = detener
 * 
 * Valores entre (0-84) y  (93-180) haran que gire mas despacio
 */
 int orden_MaxV_sentidoAntihorario=0;
 int orden_MaxV_sentidoHorario = 180;
 int orden_detener = 90;
 
 
 
 

void setup() {
  Serial.begin(9600);
  servo1.attach(PIN_SERVO); //Asociamos pin 8 al servo
  pinMode(boton_pin, INPUT_PULLUP); //modo que añade una resistencia
  pinMode(PIN_DETECTOR_COLISION, INPUT); 
}



void loop() {
    
  /*
   * LECTURAS DEL JOYSTICK: 
   *  
   * por defecto:  valorX = 500 valorY = 500
   * izq/arriba -> 0,0
   * derecha/abajo -> 1024
   * 
   *Obtencion de los valores: 
   *  analogRead(X_pin) /  analogRead(Y_pin)
	* Boton ->  digitalRead(boton_pin)
   *
    */

  int y_dir =analogRead(Y_pin);
  int x_dir = analogRead(X_pin);
	Serial.println(y_dir);
  Serial.println(x_dir);
	//Serial.println(analogRead(X_pin)+"/"+analogRead(Y_pin));
	// Si Joystick derecha o arriba ( 490 y 510 en vez de 500 para "calibrarlo" un poco)
	if(direccionDerecha(x_dir )||direccionArriba(y_dir)){
		
		//NO TENGO MUY CLARO QUE ES HACIA DELANTE O HACIA ATRAS :S
		servo1.write(orden_MaxV_sentidoHorario);
    
		Serial.println("Moviendo hacia delante ");

		
	}//Si el joystick izquierda o abajo, se mueve hacia "Atras"
	else if(direccionAbajo(y_dir)||direccionIzquierda(x_dir)){
		servo1.write(orden_MaxV_sentidoAntihorario);
		Serial.println("Moviendo hacia atras ");
	}
	else{
		servo1.write(orden_detener);
		Serial.println("Detenido ");
	}

}


 boolean direccionArriba( int y_dir){
  return y_dir < 490;
 }
 
 boolean direccionAbajo( int y_dir){
  return y_dir> 530;
 }
 boolean direccionDerecha( int x_dir){
  return x_dir < 490;
 }
 boolean direccionIzquierda( int x_dir){
  return x_dir > 530;
 }
