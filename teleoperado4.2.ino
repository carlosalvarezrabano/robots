
#include <Servo.h>


#define boton_pin 9 // pin digital para el botón, hay que cambiar el modo del pin,
                    //asegurar que ese pin de la placa lo permite
#define X_pin A0 // pin analógico para leer eje X
#define Y_pin A1 // pin analógico para leer eje Y

#define PIN_SERVO = 8; 
#define PIN_DETECTOR_COLISION = 6; //final de carrera -> digitalRead(PIN_DETECTOR_COLISION)

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
 int orden_Desp_sentidoAntihorario=42;

 int orden_MaxV_sentidoHorario = 180;
 
 int orden_desp_sentidoHorario = 136;
 
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
	
	
	
	// Si Joystick abajo
	if(612 < analogRead(Y_pin) && analogRead(Y_pin) < 923){
		servo.write(orden_desp_sentidoAntiHorario);
		Serial.println("Moviendo hacia detras despacio "));
	}
	else if(analogRead(Y_pin) > 923){ //Maximo abajo
		servo.write(orden_MaxV_sentidoAntihorario);
		Serial.println("Moviendo hacia detras rapido "));
	}
	else if(100< analogRead(Y_pin) > 412){ //arriba un poco 
		servo.write(orden_desp_sentidoHorario);
		Serial.println("Moviendo hacia adelante despacio "));
	}else if(analogRead(Y_pin)<100 ){ //arriba maximo
		servo.write(orden_MaxV_sentidoHorario);
		Serial.println("Moviendo hacia adelante rapido "));
	}
	else{
		servo.write(orden_detener);
		Serial.println("Detenido "));
	}

}
