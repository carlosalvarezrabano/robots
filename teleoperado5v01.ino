
#include <Servo.h>


//asegurar que ese pin de la placa lo permite
#define X_pin A0 // pin analógico para leer eje X
#define Y_pin A1 // pin analógico para leer eje Y

#define PIN_SERVO  8                                                                         


Servo servo1; //PIN 8
/*
   ORDENES SERVO:
   0 = sentido antihorario
   180 = sentido horario
   90 = detener

   Valores entre (0-84) y  (93-180) haran que gire mas despacio
*/
int orden_MaxV_sentidoAntihorario = 0;
int orden_MaxV_sentidoHorario = 180;
int orden_detener = 90;

int numIteraciones = 0;


/**
 * -1 IZQUIERDA
 * 0  DETENIDO
 * 1  DERECHA
 */
int direccionActual = 0;
int direccionPrevia = 0;
/**
 * P = reproducir
 * R = grabar
 * S = parar
 */
String grabando = "P";


void setup() {
  Serial.begin(9600);
  servo1.attach(PIN_SERVO); //Asociamos pin 8 al servo
}



void loop() {
  /*
     LECTURAS DEL JOYSTICK:

     por defecto:  valorX = 500 valorY = 500
     izq/arriba -> 0,0
     derecha/abajo -> 1024

    Obtencion de los valores:
      analogRead(X_pin) /  analogRead(Y_pin)
    Boton ->  digitalRead(boton_pin)

  */

  grabando = Serial.readString();
  if(grabando.equals("P"){
    String aux = Serial.readString();
    String[] = strtok(aux,"|");
  }else if (grabando.equals("R"){
    int x_dir = analogRead(X_pin);

    Serial.println(x_dir);
    moverDireccion(x_dir);
  }else{
    
  }
  
}


void moverDireccion(int x_dir ){
  

  if(direccionDerecha(x_dir)){
    servo1.write(orden_MaxV_sentidoHorario);
    direccionActual = 1;
  }
  else if(direccionIzquierda(x_dir)){
    servo1.write(orden_MaxV_sentidoAntihorario);
     direccionActual = -1;
  }
  else{
    servo1.write(orden_detener);
     direccionActual = 0;
  }
  numIteraciones++;

  if(direccionActual != direccionPrevia){
    Serial.println(String(direccionPrevia) + "|" + String(numIteracciones));
    direccionPrevia=direccionActual;
    numIteracciones=0;
  }

  
  
  
}

boolean direccionArriba( int y_dir) {
  return y_dir < 490;
}

boolean direccionAbajo( int y_dir) {
  return y_dir > 570;
}
boolean direccionDerecha( int x_dir) {
  return x_dir < 490;
}
boolean direccionIzquierda( int x_dir) {
  return x_dir > 570;
}
