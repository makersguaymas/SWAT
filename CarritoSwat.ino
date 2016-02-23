// Incluimos las librerias
#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Instanciamos la clase de MotorShield
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Alternativa (en caso de que no funciones como esperamos)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Accedemos al motor colocando el puerto en el que estan conectados
// M1, M2, M3 o M4
Adafruit_DCMotor *motorIzq = AFMS.getMotor(3);
// Podemos ultilizar varios motores
Adafruit_DCMotor *motorDer = AFMS.getMotor(4);

// Define los pins de Trig y Echo del sensor ultrasonico
const int trigPin = 6;
const int echoPin = 5;

//Distancia maxima a la que funcionara el sensor ultrasonico
#define DISTANCIA_MAXIMA 15

// Variables
int distancia;

//Configuramos el sensor ultrasonico
NewPing sonar(trigPin, echoPin, DISTANCIA_MAXIMA);
Servo myServo; // Creamos un objeto servo para controlar el servo motor

//Configuracion inicial
void setup() {

  pinMode(trigPin, OUTPUT); // Establece trigPin como salida
  pinMode(echoPin, INPUT); // Establece echoPin como entrada
  Serial.begin(9600);

  myServo.attach(12); // Indica en que pin esta conectado el servo

  AFMS.begin();  // Se crea con una frequencia default de 1.6KHz
  //AFMS.begin(1000);  // o puede usar una diferente, como 1KHz
  
  // Indicamos la velocidad inicial, desde 0 (apagado) hasta 255 (maxima velocidad)
  motorIzq->setSpeed(200);
  motorDer->setSpeed(200);

  //Indicamos la direccion hacia donde se empezara a mover
  motorIzq->run(FORWARD);
  motorDer->run(BACKWARD);

  // Encendemos los motores
  motorIzq->run(RELEASE);
  motorDer->run(RELEASE);

  // Apuntamos el sensor al frente
  mirarAlFrente();
  
  Serial.println("Carrito SWAT ACTIVADO!!");
}
void loop() {

  uint8_t i;
  Serial.println(calcularDistancia());
  //TODO: ALGORITMO
  mirarAlFrente();
  avanzar();
  if (distancia != 0) {
    parar();
    delay(1000);
    mirarDerecha();
    delay(1000);
    if(distancia != 0){
      mirarIzquierda();
      delay(1000);
      if(distancia != 0){
        retroceder()
        delay(1000);
        fuga();
        delay(1000);
      }else{
          girarIzquierda();
          delay(1000);
       }
    }else{
      girarDerecha();
      delay(1000);
    }
  }
}

/*
* FUNCIONES DEL SERVO MOTOR
* Y EL SENSOR ULTRASONICO
*
*/

// Funcion para calcular la distancia a la que se encuentra un objetos (si lo hubiera)
int calcularDistancia(){ 
  distancia = sonar.ping_cm();
  return distancia;
  
}

// Funcion para mirar al frente
int mirarAlFrente(){
  myServo.write(60);
  distancia = sonar.ping_cm();
  return distancia;
}

// Funcion para mover el servo hacia la izquierda
int mirarIzquierda(){
  myServo.write(0);
  distancia = sonar.ping_cm();
  return distancia;
}
// Funcion para mover el servo hacia la derecha
int mirarDerecha(){
  myServo.write(120);
  distancia = sonar.ping_cm();
  return distancia;
}

/*
* 
* FUNCIONES DEL MOTOR SHIELD
*
*/
//Funcion basica para avanzar
void avanzar(){
  motorIzq->run(FORWARD);
  motorDer->run(FORWARD);
  motorIzq->setSpeed(200);  
  motorDer->setSpeed(200);
}

//Funcion basica para retroceder
void retroceder(){
  motorIzq->run(BACKWARD);
  motorDer->run(BACKWARD);
  motorIzq->setSpeed(200);  
  motorDer->setSpeed(200);
}

//Funcion basica para detenerse
void parar(){
  motorIzq->setSpeed(0);  
  motorDer->setSpeed(0);
}

//Funcion basica para girar a la izquierda
void girarIzquierda(){
  motorDer->run(FORWARD);
  motorIzq->run(BACKWARD);
  motorDer->setSpeed(50);
  motorIzq->setSpeed(50);
  delay(1500);
}

//Funcon basica para girar a la derecha
void girarDerecha(){
  motorIzq->run(FORWARD);
  motorDer->run(BACKWARD);
  motorIzq->setSpeed(50);
  motorDer->setSpeed(50);
  delay(1500);

}

//Funcion basica para correr por donde veniamos D:
void fuga(){
  motorIzq->run(FORWARD);
  motorDer->run(BACKWARD);
  motorIzq->setSpeed(50);
  motorDer->setSpeed(50);
  delay(2000);
}



