// VALOR PARA SENSOR TCRT5000 COMUM acima de  600 é sensor sem detectar nada
// abaixo de 100 é considerado linha foi percebida

#include <AFMotor.h> // MOTOR 


#include <Ultrasonic.h>
Ultrasonic ultrassom(29,37); // ULTRASONICO FRONTAL trig e echo 

int velocidadenormal=100, velocidadevirada=20;


int indore=0; // VARIAVEL MAIS IMPORTANTE


// IR OU VOLTAR, A VARIAVEL



long distance, distance1; // Variavel da medida da distancia


#define linha1 A15 // ESQUERDA
#define linha2 A14
#define linha3 A13 // DIREITA


int SENSOR1,SENSOR2,SENSOR3;


AF_DCMotor motor(1,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor motor1(2,MOTOR12_64KHZ); ///  motor 2
AF_DCMotor crema(4,MOTOR12_64KHZ);

#define infra 47// porta do pir

int val=0; // status do pino normalmente igual a ZERO

int liga, processo;

void calibrar(){
  
     if( SENSOR3> 600 && SENSOR1< 600   ) { // virando para esquerda
     
            motor.setSpeed(100);
            motor1.setSpeed(0);
            delayMicroseconds(50);
                                        
                                        
      }
      if( SENSOR1 > 600  &&  SENSOR3 < 600 ){ // virando a direita
                                        
            motor.setSpeed(0);
            motor1.setSpeed(100);
            delayMicroseconds(50);
                                        
      }
      if ( SENSOR2< 600){ // continua
                                        
            motor.setSpeed(100);
            motor1.setSpeed(100);
                                        
      }

} // calibrar
  
 


void setup() {
    
      pinMode(infra,INPUT); // pino do PIR
      crema.setSpeed(100);
      Serial.begin(9600);
      
      
  }
  
void loop() { 


      switch (indore){
                    
                     case 1:// INDO PARA FRENTE
                                   
                                   Serial.println("frente");
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

                                    
                                    if((SENSOR1 < 600) && (SENSOR2 < 600) && (SENSOR3< 600)){
                                          
                                          motor.run(RELEASE);
                                          motor1.run(RELEASE);
                                          crema.run(RELEASE);
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
                                             
     
                                            
                                    
                              // indore = 1  
      
                     
  /////////////////////////////////////////////////////VOLTAR ////////////////////////////////////////////////////////////////////////////////
                                        
                                              
                            case 3: // INDO DE RÉ
  
                                        Serial.println("indore2");
                                        calibrar(); // calibração do sensores de linha
                                        
                                        crema.run(RELEASE);
                                        motor.run(BACKWARD);
                                        motor1.run(BACKWARD); 
                                        
                                         if((SENSOR1<500) && (SENSOR2<500) && (SENSOR3<500)){
                                              
                                              motor.run(RELEASE);
                                              motor1.run(RELEASE);
                                              processo = 0;
                                          
                                         }
                                       
                             default:
                             
                                Serial.println(digitalRead(infra));
                                motor.run(RELEASE);     // deixar o motor parado  
                                motor1.run(RELEASE);   // motor 1 parado     

                                val = digitalRead(infra);  // LEITURA DO INPUT DO PIR
         
                        
                        
         
                                 if( val == 0 ){ // teste do status do PIR
                
                                        processo = 1;
              
                     
          
                                   } // processo inicia 
                                   
                                while (processo == 1) {
                                     Serial.println("processo ==1");
                                     if( (SENSOR1 < 600 ) &&(SENSOR2 < 600) &&(SENSOR3 < 600) ){
                                  
                                          motor.run(FORWARD);
                                          motor1.run(FORWARD);
                                          indore=1;
                                          delayMicroseconds(10);
                                          processo=0;
                                          Serial.println("processo");   
                                    }                
                               }
                                  
                             
                                 
                    
                    } //indore 
                    
          

      motor.run(RELEASE);
      motor1.run(RELEASE);
      
   


} // loop
