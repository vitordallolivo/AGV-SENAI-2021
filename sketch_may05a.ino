

// VALOR PARA SENSOR TCRT5000 COMUM acima de  600 é sensor sem detectar nada
// abaixo de 100 é considerado linha foi percebida

#include <AFMotor.h> // MOTOR 


#include <Ultrasonic.h>
Ultrasonic ultrassom(29,37); // ULTRASONICO FRONTAL trig e echo
 
Ultrasonic ultrare(42,30); // ULTRASONICO TRASEIRO

int velocidadenormal=210, velocidadevirada=100;




int indore=0; // VARIAVEL MAIS IMPORTANTE




// IR OU VOLTAR, A VARIAVEL



long distance, distance1; // Variavel da medida da distancia


#define linha1 A13 // DIREITA
#define linha2 A14
#define linha3 A15 // ESQUERDA


int SENSOR1,SENSOR2,SENSOR3;


AF_DCMotor motor(1,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor motor1(2,MOTOR12_64KHZ); ///  motor 2
AF_DCMotor crema(4,MOTOR12_64KHZ);

#define infra 47// porta do pir

int val=0; // status do pino normalmente igual a ZERO

int liga, processo;


void calibrar(){
  
     if(SENSOR1< 500 && SENSOR3>  500) { // virando para esquerda
     
            motor.setSpeed(velocidadenormal);
            motor1.setSpeed(velocidadevirada);
           delayMicroseconds(50);
                                        
                                        
      }
      if(SENSOR1> 500 && SENSOR3<500){ // virando a direita
                                        
            motor.setSpeed(velocidadevirada);
            motor1.setSpeed(velocidadenormal);
            delayMicroseconds(50);
                                        
      }
      if (SENSOR1> 500 && SENSOR3> 500){
                                        
            motor.setSpeed(velocidadenormal);
            motor1.setSpeed(velocidadenormal);
                                        
      }

}
  
  



void setup() {
    
      pinMode(infra,INPUT_PULLUP); // pino do PIR
      crema.setSpeed(100);
      Serial.begin(9600);
      
      
  }
  
void loop() { 
         
         
         Serial.println(infra);
         motor.run(RELEASE);     // deixar o motor parado  
         motor1.run(RELEASE);   // motor 1 parado     
       
 
          
          
         val = digitalRead(infra);  // LEITURA DO INPUT DO PIR
         
                        
                        
         
              if( val == 0 ){ // teste do status do PIR
                
                    processo = 1;
              
                     Serial.println("processo"); // DIZ onde estamo no processo   
          
              } // processo inicia 
        
              while (processo == 1){ // processo é para o carrinho iniciar como um todo
              /*Primeiro é preciso ligar o botão para depois ligar o processo com um sinal do PIR*/    
    
                  distance1 = ultrare.Ranging(CM);
                  distance = ultrassom.Ranging(CM);
                  SENSOR1 = analogRead(linha1);
                  SENSOR2 = analogRead(linha2);
                  SENSOR3 = analogRead(linha3);
                  
                  while( (SENSOR1 < 500) &&( SENSOR2< 500) &&(SENSOR3 < 500) ){
                    
                    
                        indore = 1; // INDO PARA FRENTE
                        motor.run(255);
                        motor1.run(255);
                        Serial.println(SENSOR1);
                    }
                  
                  
                    
                   while(indore == 1){ // INDO PARA FRENTE
          
                                 crema.run(RELEASE);
                                 motor.run(FORWARD);
                                 motor1.run(FORWARD);

                                       
                                 //le os sensores e adiciona os deslocamentos
                                 SENSOR1 = analogRead(linha1);
                                 SENSOR2 = analogRead(linha2);
                                 SENSOR3 = analogRead(linha3);
                                                                      
                           
                          
                                 distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                                        
                                   // Distancia
                                                                    
                                  Serial.print("Distancia: ");
                                  Serial.print(distance);
                                  Serial.println(" cm");   
                                  calibrar();
                                  while((SENSOR1<500) && (SENSOR2<500) && (SENSOR3<500)){

                                        motor.run(RELEASE);
                                        motor1.run(RELEASE);
                                        crema.run(FORWARD);
                                        delay(3000);
                                        motor.run(BACKWARD);
                                        motor1.run(BACKWARD);
                                        indore = 2;
                                        crema.run(RELEASE);
                                    
                                    
                                    }
                                    
                                  while (distance >=10 && distance < 100 && indore == 1){ // PARAR O CARRINHO
                                            
                                      motor.run(RELEASE);  
                                      motor1.run(RELEASE);
                                      delayMicroseconds(50); 
                                      distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                                            
                                  }
                                           
   
                                          
                                  
                           } // indore = 1  
    
                   
/////////////////////////////////////////////////////VOLTAR ////////////////////////////////////////////////////////////////////////////////
                                      
                                            
                          while( indore == 2){ // INDO DE RÉ

                                      
                                      calibrar(); // calibração do sensores de linha
                                      
                                      motor.run(BACKWARD);
                                      motor1.run(BACKWARD); 
                                      distance1 = ultrare.Ranging(CM); // distancia recebe o valor medido em cm
                                    
                                       while (distance1 >=4 && distance1 < 100 ){ // PARAR O CARRINHO
                                            
                                          motor.run(RELEASE);
                                          motor1.run(RELEASE);     
                                          distance1 = ultrare.Ranging(CM); // distancia recebe o valor medido em cm
                                            
                                       }
                    
                    
                                       if((SENSOR1<500) && (SENSOR2<500) && (SENSOR3<500)){
                                            
                                            motor.run(RELEASE);
                                            motor1.run(RELEASE);
                                            processo = 0;
                                        
                                       }
                                       
                                      
                                 
                    
                    } //indore 2
                  
          }// processo 


      motor.run(RELEASE);
      motor1.run(RELEASE);
      
   


} // loop
  

 
