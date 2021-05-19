                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
/*

COMENTARIO:

CARRINHO SEGUIR A LINHA E QUANDO OS DOIS SENSORES MANDAREM UM PULSO CREMALHEIRA ANDA

*/
#include <AFMotor.h> // MOTOR 


#include <Ultrasonic.h>
Ultrasonic ultrassom(31,30); // pinos sensor(ultrassom)

long distance; // Variavel da medida da distancia

#define button 23 // botão

#define linha1 50 // sensor de linha esquerda
#define led1 51 // led1 esquerda

#define linha2 52 // sensor de linha direita
#define led2   53 // led2 a direita


AF_DCMotor motor(1,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor motor1(2,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor crema(3,MOTOR12_64KHZ);


int inputPin = 22; // porta do pir
int pirState = LOW; // status dizendo que o pir inicia em baixo
int val=0; // status do pino normalmente igual a ZERO

int liga, processo, usl, ve, vd;



  void setup() {
    
      motor.setSpeed(ve); // velocidade do motor (está no M1)
      motor1.setSpeed(vd); // velocidade do motor 1 (está no M2)
      pinMode(button,INPUT);
      pinMode(inputPin,INPUT); // pino do PIR


      Serial.begin(9600);
      
  }
  
  void loop() { 

  
       motor.run(RELEASE);     // deixar o motor parado  
       motor1.run(RELEASE);   // motor 1 parado     

       Serial.println("inicio");
       
      if (digitalRead(button)== 1){
          
          liga = 1;
          Serial.println("botão");
          
          
      }
      while (liga ==1) { // Um botão ligado
        
          val = digitalRead(inputPin);  // LEITURA DO INPUT DO PIR
          
          if( val == 1 ){ // teste do status do PIR
            
                processo = 1;
          
          Serial.println("processo"); // DIZ onde estamo no processo
      
          } // processo inicia 
    
          while (processo == 1){ // processo é para o carrinho iniciar como um todo
          /*Primeiro é preciso ligar o botão para depois ligar o processo com um sinal do PIR*/    



              // função do movimento do carrinho
              
              if (digitalRead(linha1) == 1){ // movimento para esquerda

                                    
                    ve = ve+1; // velocidade vai aumentando 1
                    vd = vd - 1; // velocidade vai perdendo 1


                    motor.run(FORWARD);
                    motor1.run(FORWARD);
                    
                    if(ve>255){ ve = 255;} // limite do arduino de 255( 5 Volts)
                    if(vd<0){vd = 0;} // limite do arduino de 0

                    digitalWrite(led1,LOW);

                    Serial.println("canhota");
                
                }
              
              
             
              if (digitalRead(linha2) == 1) // LINHAS IGUAL A 1 ---> LED LOW
                                     
                    ve = ve-1;
                    vd = vd + 1;


                    motor.run(FORWARD);
                    motor1.run(FORWARD);
                    
                    if(vd>255){ vd = 255;}
                    
                    if(ve<0){ve = 0;}

                    digitalWrite(led2,LOW);

                    Serial.println("DIREITA");
                    
                }
              
              
              if (digitalRead(linha1) == 0 && digitalRead(linha2) == 0){
  
                        ve= 255;
                        ve=vd;
        
                        motor.run(FORWARD);
                        motor1.run(FORWARD);
        
  
                        digitalWrite(led1,HIGH);
                        digitalWrite(led2,HIGH);
                
                }
                
              else {
                

                      if(digitalRead(linha1) == 1 && linha2== 1 ){
      
                                digitalWrite(led1,LOW);
                                digitalWrite(led2,LOW);
                                 
                                 
                                 motor.run(RELEASE);     // deixar o motor parado  
                                 motor1.run(RELEASE);   // motor 1 parado     
            
                                 crema.run(RELEASE); // cremalheira anda
                                 delay(1000);
            
                                 crema.run(FORWARD); // cremalheira retorna
                                 delay(1000);
            
                                 crema.run(RELEASE); // fica parada em espera
                                 
                                
                                
                                
                        }
                
                }
            

              distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
              
              // Distancia
              
              Serial.print("Distancia: ");
              Serial.print(distance);
              Serial.println(" cm");

              
              while (distance >=0 && distance < 50 ){
                    
                    motor.run(RELEASE);    
                       
                    delay(1000); 
                    distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                    
              }
      }
      
 }


  
  
  

 
