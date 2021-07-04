// VALOR PARA SENSOR TCRT5000 COMUM acima de  600 é sensor sem detectar nada
// abaixo de 100 é considerado linha foi percebida

#include <AFMotor.h> // MOTOR 

#include <Ultrasonic.h>

void andarFrente();
void andarTras();
void speedMotor(int,int);
void velocidadeMotor(int,int,int,int);

Ultrasonic ultrassom(29, 37); // ULTRASONICO FRONTAL trig e echo
Ultrasonic ultrare(43, 41); // TRIG E ECHO

int indore = 0; // VARIAVEL MAIS IMPORTANTE


long distance, distance1; // Variavel da medida da distancia


#define linha1 A15 // direita
#define linha2 A14
#define linha3 A11 // esquerda


int sensorDireita, sensorCentro, sensorEsquerda;
/*

   sensorDireita --> DIREITA FRENTE E ESQUERDA ATRÁS

   sensorCentro --> CENTRO

   sensorEsquerda --> ESQUERDA FRENTE E DIREITA ATRÁS

*/


AF_DCMotor motorE(1, MOTOR12_64KHZ); ///  motorE 1  M1 e sensor 3 pegar m2 acelera
AF_DCMotor motorD(2, MOTOR12_64KHZ); ///  motorD 2 M2
AF_DCMotor crema(4, MOTOR12_64KHZ);

#define infra 47// porta do infravermelho

int val; // status do pino normalmente igual a ZERO


void setup() {
  pinMode(infra, INPUT); // pino do PIR
  Serial.begin(9600);
  crema.setSpeed(100);
}

void speedMotor(int speedMotorD,int speedMotorE){
  motorE.setSpeed(speedMotorE);
  motorD.setSpeed(speedMotorD);
}

void velocidadeMotor(int speedMD,int speedME, int runMD,int runME){
  motorD.run(runMD);
  motorE.run(runME);
  speedMotor(speedMD,speedME);
}


void loop() {
  //Serial.println(sensorDireita);
  val = digitalRead(infra);  // LEITURA DO INPUT DO infra

  if (val == 0) {

    indore = 1; // indo para frente

    velocidadeMotor(90,70,FORWARD,FORWARD);
    delay(1000);
    andarFrente();
    andarTras();
  }
}

void andarFrente(){
  int frente = 1;
  while (frente) {

    sensorDireita = analogRead(linha1);
    sensorCentro = analogRead(linha2);
    sensorEsquerda = analogRead(linha3);

    // Serial.println(sensorEsquerda);
    if  (sensorCentro > 600 && sensorDireita < 600 && sensorEsquerda < 600) {
      speedMotor(90,70);
      continue;
    }

    if (sensorCentro > 600 && sensorEsquerda < 600 && sensorDireita > 600) {
      speedMotor(100,130);
      continue;
    }

    if (sensorCentro > 600 && sensorEsquerda > 600 && sensorDireita < 600) {
      speedMotor(150,80);
      continue;
    }

    // SAIU PELA ESQUERDA
    if (sensorEsquerda < 600 && sensorDireita > 600) { 
      speedMotor(60,120);
      continue;
    }
    if (sensorDireita < 600 && sensorEsquerda > 600) {
      speedMotor(140,40);
      continue;
    }

    // todos os sensores detectaram a linha    
    if ( sensorDireita > 600 && sensorCentro > 600 && sensorEsquerda > 600 ) {
      velocidadeMotor(0,0,RELEASE,RELEASE);

      crema.run(FORWARD);
      
      delay(1500);
      velocidadeMotor(0,0,RELEASE,RELEASE);
      velocidadeMotor(90,70,BACKWARD,BACKWARD);

      crema.run(RELEASE);
      delay(1000);

      frente = !frente;
    }
  }
}

void andarTras(){
  int tras = 1;
  while (tras) { // indo para trás
    sensorDireita = analogRead(linha1);
    sensorCentro = analogRead(linha2);
    sensorEsquerda = analogRead(linha3);
    // motorD.run(BACKWARD);
    // motorE.run(BACKWARD);
    // motorE.setSpeed(70);
    // motorD.setSpeed(80);
    
    if  (sensorCentro > 600 && sensorDireita < 600 && sensorEsquerda < 600) {
      speedMotor(90,70);
      continue;
    }

    if (sensorCentro > 600 && sensorEsquerda < 600 && sensorDireita > 600) {
      speedMotor(150,70);
      continue;
    }

    if (sensorCentro > 600 && sensorEsquerda > 600 && sensorDireita < 600) {
      speedMotor(90,130);
      continue;
    }

    if (sensorEsquerda < 600 && sensorDireita > 600) { 
      speedMotor(150,40);
      continue;
    }
    if (sensorDireita < 600 && sensorEsquerda > 600) {
      speedMotor(60,130);
      continue;
    }

    // chegou no inicio novamente
    if (sensorDireita > 600 && sensorCentro > 600 && sensorEsquerda > 600 ){
      velocidadeMotor(80,70,FORWARD,FORWARD);
      delay(1000);
      velocidadeMotor(0,0,RELEASE,RELEASE);

      tras = !tras;
    }
  }
}