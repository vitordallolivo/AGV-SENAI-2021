// VALOR PARA SENSOR TCRT5000 COMUM acima de  600 é sensor sem detectar nada
// abaixo de 100 é considerado linha foi percebida

#include <AFMotor.h> // MOTOR 

#include <Ultrasonic.h>
Ultrasonic ultrassom(29,37); // ULTRASONICO FRONTAL trig e echo 
Ultrasonic ultrare(43,41); // TRIG E ECHO

int indore; // VARIAVEL MAIS IMPORTANTE


// IR OU VOLTAR, A VARIAVEL

#define led 40

long distance, distance1; // Variavel da medida da distancia


#define linha1 A15 // direita
#define linha2 A14
#define linha3 A11 // esquerda


int SENSOR1,SENSOR2,SENSOR3; 
/*
 * 
 * SENSOR1 --> DIREITA FRENTE E ESQUERDA ATRÁS
 * 
 * SENSOR2 --> CENTRO
 * 
 * SENSOR3 --> ESQUERDA FRENTE E DIREITA ATRÁS
 * 
*/


AF_DCMotor motor(1,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor motor1(2,MOTOR12_64KHZ); ///  motor 2
AF_DCMotor crema(4,MOTOR12_64KHZ);

#define infra 47// porta do pir

int val; // status do pino normalmente igual a ZERO

int liga, processo;
void setup() {
  // put your setup code here, to run once:
     pinMode(infra,INPUT); // pino do PIR
     pinMode(led,OUTPUT);
     crema.setSpeed(150);
     Serial.begin(9600);
     motor.setSpeed(100);
     motor1.setSpeed(100);
     crema.setSpeed(50);
}

void loop() {
  // put your main code here, to run repeatedly:
        Serial.println(SENSOR2);
     
        SENSOR1 = analogRead(linha1);
        SENSOR2 = analogRead(linha2);
        SENSOR3 = analogRead(linha3);
        motor.run(RELEASE);
        motor1.run(RELEASE);
        
        if (SENSOR2>600){
















































          motor.run(FORWARD);
          motor1.run(FORWARD);
        }

}
