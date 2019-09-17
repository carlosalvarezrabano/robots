#include <Servo.h>

int NO_LINEA =LOW;
int LINEA =HIGH;

Servo servoIzq;
Servo servoDer;

int pinIrDer=3;
int pinIrIzq =2;
int pinServoIzq =8;
int pinServoDer =9;

//Estados 
int est_buscandoPista=0;
int est_corregirTrayectoria=1;
int est_avanzar=2;

int estadoActual=0;


void setup(){
	Serial.begin(9600); 
	pinMode(pinIrDer,INPUT);
	pinMode(pinIrIzq,INPUT);
	servoIzq.attach(pinServoIzq);
	servoDer.attach(pinServoDer);
}

void loop(){

	AnalizarEstado();
	if(difitalRead(pinIrIzq)== NO_LINEA && digitalRead(pinIrDer) ==NO_LINEA){
	
		//Moverse aleatoriamente o pararse
	
	}
	if(difitalRead(pinIrIzq)== LINEA && digitalRead(pinIrDer) ==NO_LINEA){
		//mover izquierda
		servoDer.write(0);
		servoIzq.write(110);
	}
	if(difitalRead(pinIrIzq)== NO_LINEA && digitalRead(pinIrDer) ==LINEA){
		//mover izquierda
		servoDer.write(70);
		servoIzq.write(180);
	}
	if(difitalRead(pinIrIzq)== LINEA && digitalRead(pinIrDer) ==LINEA){
		//mover izquierda
		servoDer.write(20);
		servoIzq.write(160);
	}
}


}