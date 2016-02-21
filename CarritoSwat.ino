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
#define DISTANCIA_MAXIMA 20

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
  motorIzq->setSpeed(100);
  motorDer->setSpeed(100);

  //Indicamos la direccion hacia donde se empezara a mover
  motorIzq->run(FORWARD);
  motorDer->run(BACKWARD);

  // Encendemos los motores
  motorIzq->run(RELEASE);
  motorDer->run(RELEASE);
  
  Serial.println("Carrito SWAT ACTIVADO!!");
}
void loop() {

  uint8_t i;

  fuga();
  parar();
  delay(2000);
  
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
void mirarAlFrente(){
  myServo.write(60);
}

// Funcion para mover el servo hacia la izquierda
void mirarIzquierda(){
  
  for(int i=60;i>0;i--){ //60 -> 0  
    myServo.write(i);
    delay(30);
    distancia = calcularDistancia();// Llama a la funcion calcularDistancia cada vez que el servo avanza un grado
    Serial.print(i); // Envia el grado actual al Serial Port
    Serial.print(":"); // Se envia un carater especial para separar el valor de los grados y la distancia
    Serial.print(distancia); // Se envia la distancia al Serial Port
    Serial.print(".");
  }
}
// Funcion para mover el servo hacia la derecha
void mirarDerecha(){

  for(int i=60;i<=120;i++){  //60 -> 120
    myServo.write(i);
    delay(30);
    distancia = calcularDistancia();
    Serial.print(i);
    Serial.print(":");
    Serial.print(distancia);
    Serial.print(".");
  }
}

/*
* 
* FUNCIONES DEL MOTOR SHIELD
*
*/

void avanzar(){
  motorIzq->run(FORWARD);
  motorDer->run(FORWARD);
  motorIzq->setSpeed(100);  
  motorDer->setSpeed(100);
}

void retroceder(){
  motorIzq->run(BACKWARD);
  motorDer->run(BACKWARD);
  motorIzq->setSpeed(100);  
  motorDer->setSpeed(100);
}

void parar(){
  motorIzq->setSpeed(0);  
  motorDer->setSpeed(0);
}

void girarIzquierda(){
  motorDer->run(FORWARD);
  motorIzq->run(BACKWARD);
  motorDer->setSpeed(50);
  motorIzq->setSpeed(50);
  delay(1500);
}

void girarDerecha(){
  motorIzq->run(FORWARD);
  motorDer->run(BACKWARD);
  motorIzq->setSpeed(50);
  motorDer->setSpeed(50);
  delay(1500);

}

void fuga(){
  motorIzq->run(FORWARD);
  motorDer->run(BACKWARD);
  motorIzq->setSpeed(50);
  motorDer->setSpeed(50);
  delay(2000);
}

