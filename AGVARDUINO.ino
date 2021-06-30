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

void calibrar(){
  
     if( SENSOR3> 600 && SENSOR1< 600   ) { // virando para esquerda
     
            motor.setSpeed(100);
            motor1.setSpeed(0);
            delayMicroseconds(0);
                                          
      }

      if (SENSOR1 > 600 && SENSOR2>600){ // direita-centro FRENTE
        
            motor1.setSpeed(60);
            motor.setSpeed(100);
        
        }

      if (SENSOR2> 600 && SENSOR3> 600){ // esquerda-centro FRENTE
        
           motor1.setSpeed(100);
           motor.setSpeed(60);
        
        
        
        }  
      
      if( SENSOR1 > 600  &&  SENSOR3 < 600 ){ // virando a direita
                                        
            motor.setSpeed(0);
            motor1.setSpeed(100);
            delayMicroseconds(0);
                                        
      }
      if ( SENSOR2 > 600){ // continua
                                        
            motor.setSpeed(100);
            motor1.setSpeed(100);
                                        
      }

} // calibrar


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
void calibrar1(){ // o sinal de quando está indo de maneira reversa é oposto a de maneira normal

     // esquerda foi revertida com a direita
  
     if( SENSOR3> 600 && SENSOR1< 600   ) { //  virando a esquerda
     
            motor.setSpeed(0);
            motor1.setSpeed(100);
            delayMicroseconds(0);
                                          
      }
      if( SENSOR1 > 600  &&  SENSOR3 < 600 ){ // virando a direita 
                                        
            motor.setSpeed(100);
            motor1.setSpeed(0);
            delayMicroseconds(0);
                                        
      }
      if ( SENSOR2 > 600){ // continua
                                        
            motor.setSpeed(100);
            motor1.setSpeed(100);
                                        
      }


      if (SENSOR1 > 600 && SENSOR2>600){ // esquerda-centro RÉ
        
            motor1.setSpeed(100);
            motor.setSpeed(60);
        
        }

      if (SENSOR2> 600 && SENSOR3> 600){ // direita-centro RÉ
        
           motor1.setSpeed(60);
           motor.setSpeed(100);
        
        
        
        }

} // calibrar  1


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    
      pinMode(infra,INPUT); // pino do PIR
      pinMode(led,OUTPUT);
      crema.setSpeed(150);
      Serial.begin(9600);
      
      
  }
  
void loop() { 

      while(indore == 1){// INDO PARA FRENTE
                                   
            Serial.println("frente");
            crema.run(RELEASE);
            motor.run(FORWARD);
            motor1.run(FORWARD);
            calibrar();
                                         
            //le os sensores e adiciona os deslocamentos
            SENSOR1 = analogRead(linha1);
            SENSOR2 = analogRead(linha2);
            SENSOR3 = analogRead(linha3);
                                                                        
                             
                            
            distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                                          
            // Distancia
           /*                                                           
            Serial.print("Distancia: ");
            Serial.print(distance);
            Serial.println(" cm");   
           */  
                                  
            if((SENSOR1 >600) && (SENSOR2 >600) && (SENSOR3>600)){
                                          
                  motor.run(RELEASE);
                  motor1.run(RELEASE);
                  crema.run(RELEASE);
                  delay(3000);
                  motor.run(BACKWARD);
                  motor1.run(BACKWARD);
                  indore = 2;
                  crema.run(RELEASE);
                  Serial.println("esteira");
                                          
                                      
             }
                                     
             while (distance >=10 && distance < 100 && indore == 1){ // PARAR O CARRINHO
                                              
                     motor.run(RELEASE);  
                     motor1.run(RELEASE);
                     delayMicroseconds(50); 
                     distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm 
                                              
             }
                                             
     
                                            
      }        
                              // indore = 1  
      
                     
  /////////////////////////////////////////////////////VOLTAR ////////////////////////////////////////////////////////////////////////////////
                                        
                                              
      while(indore == 2){ // Condição de andar de ré
                           
           SENSOR1 = analogRead(linha1);
           SENSOR2 = analogRead(linha2);
           SENSOR3 = analogRead(linha3);
           Serial.println("indore2");
           calibrar1(); // calibração do sensores de linha

           distance1 = ultrare.Ranging(CM); // distancia recebe o valor medido em cm
                                        
           crema.run(RELEASE);
           motor.run(BACKWARD);
           motor1.run(BACKWARD); 
                                        
           if((SENSOR1>600) && (SENSOR2>600) && (SENSOR3>600)){
                                              
                   motor.run(RELEASE);
                   motor1.run(RELEASE);
                   indore = 3;
                                          
            }
           while (distance1>=0 && distance1=<10){ // distancia da parte traseira

                  motor.run(RELEASE); // motor da direita 
                  motor1.run(RELEASE);// motor da esquerda
                  delayMicroseconds(10);
           }
           
      }
                              
      while (indore =! 1 && indore =! 2){ // Condição de inicio
                              
                             
           Serial.println(digitalRead(infra));
           SENSOR1 = analogRead(linha1);
           SENSOR2 = analogRead(linha2);
           SENSOR3 = analogRead(linha3);  
                                    
           val = digitalRead(infra);  // LEITURA DO INPUT DO PIR
                   
           if (val == 0 ){
                                            
                  motor.run(FORWARD);
                  motor1.run(FORWARD);
                  indore=1;
                  delay(500);
                  Serial.println(SENSOR1);   
           }
      
      }     
                                            
} // loop
