// VALOR PARA SENSOR TCRT5000 COMUM acima de  600 é sensor sem detectar nada
// abaixo de 100 é considerado linha foi percebida

#include <AFMotor.h> // MOTOR 

#include <Ultrasonic.h>
Ultrasonic ultrassom(29, 37); // ULTRASONICO FRONTAL trig e echo
Ultrasonic ultrare(43, 41); // TRIG E ECHO

int indore; // VARIAVEL MAIS IMPORTANTE


long distance, distance1; // Variavel da medida da distancia


#define linha1 A15 // direita
#define linha2 A14
#define linha3 A11 // esquerda


int SENSOR1, SENSOR2, SENSOR3;
/*

   SENSOR1 --> DIREITA FRENTE E ESQUERDA ATRÁS

   SENSOR2 --> CENTRO

   SENSOR3 --> ESQUERDA FRENTE E DIREITA ATRÁS

*/


AF_DCMotor motor(1, MOTOR12_64KHZ); ///  motor 1  M1 e sensor 3 pegar m2 acelera
AF_DCMotor motor1(2, MOTOR12_64KHZ); ///  motor 2 M2
AF_DCMotor crema(4, MOTOR12_64KHZ);

#define infra 47// porta do pir

int val; // status do pino normalmente igual a ZERO

int liga;

void setup() {

  pinMode(infra, INPUT); // pino do PIR
  Serial.begin(9600);
  crema.setSpeed(100);


}

void loop() {

  //Serial.println(SENSOR1);
  SENSOR1 = analogRead(linha1);
  SENSOR2 = analogRead(linha2);
  SENSOR3 = analogRead(linha3);

  val = digitalRead(infra);  // LEITURA DO INPUT DO PIR

  if (val == 0) {

    indore = 1 ; // indo para frente

    motor1.run(FORWARD);
    motor.run(FORWARD);
    motor.setSpeed(70);
    motor1.setSpeed(90);
    delay(1000);

  }

  while (indore == 1) {

    motor1.run(FORWARD);
    motor.run(FORWARD);
    motor.setSpeed(70);
    motor1.setSpeed(90);
    SENSOR1 = analogRead(linha1);
    SENSOR2 = analogRead(linha2);
    SENSOR3 = analogRead(linha3);



    if ( SENSOR1 > 600 && SENSOR2 > 600 && SENSOR3 > 600 ) // todos os sensores detectaram a linha
    {

      motor.run(RELEASE);
      motor.setSpeed(0);
      motor1.run(RELEASE);
      motor1.setSpeed(0);
      crema.run(FORWARD);
      delay(1500);
      motor.run(RELEASE);
      motor.setSpeed(0);
      motor1.run(RELEASE);
      motor1.setSpeed(0);
      motor1.run(BACKWARD);
      motor.run(BACKWARD);
      motor.setSpeed(70);
      motor1.setSpeed(90);
      crema.run(RELEASE);
      delay(1000);
      indore = 2;


    }

  }

  while (indore == 2) { // indo para trás
    SENSOR1 = analogRead(linha1);
    SENSOR2 = analogRead(linha2);
    SENSOR3 = analogRead(linha3);
    motor1.run(BACKWARD);
    motor.run(BACKWARD);
    motor.setSpeed(70);
    motor1.setSpeed(80);

    if ( SENSOR1 > 600 && SENSOR2 > 600 && SENSOR3 > 600 ) // chegou no inicio novamente
    {
      motor1.run(FORWARD);
      motor.run(FORWARD);
      motor.setSpeed(70);
      motor1.setSpeed(80);
      delay(1000);
      motor.run(RELEASE);
      motor.setSpeed(0);
      motor1.setSpeed(0);

      indore = 3;

    }




  }



}
