#include <Servo.h>

int NO_LINEA =LOW;
int LINEA =HIGH;

//servos
Servo servoIzq; //>90
Servo servoDer; //<90

//velocidades

const int vMax_servoIzq = 180;
const int vMax_servoDer=0;

int pinIrDer=3;
int pinIrIzq =2;
int pinServoIzq =8;
int pinServoDer =9;

//Estados 
const int est_buscandoPista=0;
const int est_corregirTrayectoria=1;
const int est_avanzar=2;

int estadoActual=0;

const int tAvanceEnBusquedaMaximo=3000;
int tAvanceEnBusquedaActual;

void setup(){
	Serial.begin(9600); 
	pinMode(pinIrDer,INPUT);
	pinMode(pinIrIzq,INPUT);
	servoIzq.attach(pinServoIzq);
	servoDer.attach(pinServoDer);
	tAvanceEnBusquedaActual=tAvanceEnBusquedaMaximo;
}

void loop(){

	AnalizarEstado();
	
	BuscarPista();
	
	CorregirTrayectoria();
	
	Avanzar();
}


//PERCEPCION 
void AnalizarEstado(){

	Detener();
	if(difitalRead(pinIrIzq)== NO_LINEA && digitalRead(pinIrDer) ==NO_LINEA){
		estadoActual = est_buscandoPista;
	}else if(difitalRead(pinIrIzq)== LINEA && digitalRead(pinIrDer) ==LINEA){
		estadoActual = est_avanzar;
	}else if(difitalRead(pinIrIzq)== LINEA || digitalRead(pinIrDer) ==LINEA){
		estadoActual = est_corregirTrayectoria;
	}
}

// COMPORTAMIENTOS

void BuscarPista(){
	if(estadoActual == est_buscandoPista){
		servoDer.write(0);
		servoIzq.write(0);	
		servoDer.write(vMax_servoDer+30);
		servoIzq.write(vMax_servoIzq-30);
		delay(tAvanceEnBusquedaActual);
		tAvanceEnBusquedaActual = tAvanceEnBusquedaActual - 500;
	}
		if( tAvanceEnBusquedaActual <= 0|| difitalRead(pinIrIzq)== LINEA || digitalRead(pinIrDer) ==LINEA){
			tAvanceEnBusquedaActual = tAvanceEnBusquedaMaximo;
		}
}


void CorregirTrayectoria(){
	if(estadoActual == est_corregirTrayectoria){
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
	}
}

void Avanzar(){

	servoDer.write(vMax_servoDer);
	servoIzq.write(vMax_servoIzq);
	delay(500);
}

void Detener(){
	servoDer.write(90);
	servoIzq.write(90);
}
