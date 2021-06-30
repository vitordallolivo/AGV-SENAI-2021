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
     Serial.begin(9600);
     motor.setSpeed(200);
     motor1.setSpeed(220);
     crema.setSpeed(200);
     digitalWrite(led,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
     Serial.println(SENSOR1);

     crema.run(RELEASE);
     
     SENSOR1 = analogRead(linha1);
     SENSOR2 = analogRead(linha2);
     SENSOR3 = analogRead(linha3);
     motor.run(FORWARD);
     motor1.run(FORWARD);
        
        
       
      if ( SENSOR2 > 600){ // continua
           motor.run(FORWARD);
           motor1.run(FORWARD);                            
            
      }
      
      if ( SENSOR1> 600 && SENSOR2<600){ // SENSOR 1 É JUNTO AO M1 (MOTOR NORMAL NÃO O MOTOR 1)
        
        
         motor.run(FORWARD);
         motor1.run(BACKWARD);  
            
            
        }                                  
      
      if ( SENSOR3> 600 && SENSOR2<600){ // SENSOR3 É JUNTO AO M2, MOTOR1
        
            motor.run(BACKWARD);
            motor1.run(FORWARD);
            
        
        }  
     
      
    
      if (SENSOR1>600 && SENSOR2>600 && SENSOR3>600){

            delayMicroseconds(30);
            motor.run(RELEASE);
            motor.setSpeed(0);
            motor1.run(RELEASE);
            motor1.setSpeed(0);
            crema.run(FORWARD);
            delay(3000);
            crema.run(RELEASE);
        
      }




}
