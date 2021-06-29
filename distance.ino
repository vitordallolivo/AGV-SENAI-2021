// VALOR PARA SENSOR TCRT5000 COMUM acima de  600 é sensor sem detectar nada
// abaixo de 100 é considerado linha foi percebida

#include <AFMotor.h> // MOTOR 


#include <Ultrasonic.h>
Ultrasonic ultrassom(29,37); // ULTRASONICO FRONTAL trig e echo 
Ultrasonic ultrare(43,41); // TRIG E ECHO

int velocidadenormal=100, velocidadevirada=20;


int indore; // VARIAVEL MAIS IMPORTANTE


// IR OU VOLTAR, A VARIAVEL

#define led 40

long distance, distance1; // Variavel da medida da distancia


#define linha1 A15 // direita
#define linha2 A14
#define linha3 A11 // esquerda


int SENSOR1,SENSOR2,SENSOR3;


AF_DCMotor motor(1,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor motor1(2,MOTOR12_64KHZ); ///  motor 2
AF_DCMotor crema(4,MOTOR12_64KHZ);

#define infra 47// porta do pir

int val; // status do pino normalmente igual a ZERO

int liga, processo;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    distance1  = ultrare.Ranging(CM);
    Serial.print("Distancia: ");
    Serial.print(distance1);
    Serial.println(" cm");

    
}
