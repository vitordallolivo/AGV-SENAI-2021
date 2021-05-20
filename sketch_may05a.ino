
#include <AFMotor.h> // MOTOR 


#include <Ultrasonic.h>
Ultrasonic ultrassom(31,30); // ULTRASONICO FRONTAL
 
Ultrasonic ultrare(40,41); // ULTRASONICO TRASEIRO



// VARIAVEL MAIS IMPORTANTE


int indore;



// IR OU VOLTAR, A VARIAVEL



long distance, distance1; // Variavel da medida da distancia

#define button 23 // botão

//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 70, rotate = 30;
//limiar do sensor
int threshold = 5;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;


#define linha1 A11
#define linha2 A12
#define linha3 A13




int SENSOR1,SENSOR2,SENSOR3;


AF_DCMotor motor(1,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor motor1(2,MOTOR12_64KHZ); ///  motor 1
AF_DCMotor crema(3,MOTOR12_64KHZ);



int inputPin = 22; // porta do pir
int pirState = LOW; // status dizendo que o pir inicia em baixo
int val=0; // status do pino normalmente igual a ZERO

int liga, processo, usl, ve, vd;

//Rotina de calibracao sensor
void calibrate(){
   for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
   {
       
           SENSOR1 = analogRead(linha1);                                                   // ENTRADAS DOS SENSORES DE LINHA
           SENSOR2 = analogRead(linha2);                                                   // ENTRADAS DOS SENSORES DE LINHA
           SENSOR3 = analogRead(linha3);                                                   // ENTRADAS DOS SENSORES DE LINHA
           leftOffset = leftOffset + SENSOR1;
           centre = centre + SENSOR2;
           rightOffset = rightOffset + SENSOR3;
           
    }
 //obtem a media para cada sensor
         leftOffset = leftOffset /10;
         rightOffset = rightOffset /10;
         centre = centre / 10;
         //calcula os deslocamentos para os sensores esquerdo e direito
         leftOffset = centre - leftOffset;
         rightOffset = centre - rightOffset;
}

  void setup() {
          
      calibrate();
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

              distance1 = ultrare.Ranging(CM);
              
              if( distance1 == 0 && distance1<5){
                
                
                    indore = 1;
               
                }
              
              switch(indore){
                
                  case 1: // INDO PARA FRENTE
      
                      
                             // função do movimento do carrinho PARA FRENTE
                                  
                             //utiliza a mesma velocidade em ambos os motores
                             left = startSpeed;
                             right = startSpeed;
                                     
                             //le os sensores e adiciona os deslocamentos
                             SENSOR1 = analogRead(linha1) + leftOffset;
                             SENSOR2 = analogRead(linha2);
                             SENSOR3 = analogRead(linha3) + rightOffset;
                                     
                             //Se SENSOR1 for maior do que o sensor do centro + limiar,
                             // vire para a direita
                             if (SENSOR1 > SENSOR2+threshold){
                              
                                    left = startSpeed + rotate;
                                    right = startSpeed - rotate;
                                    
                                      
                              }
                                     
                              //Se SENSOR3 for maior do que o sensor do centro + limiar,
                              // vire para a esquerda
                              if (SENSOR3 > (SENSOR2+threshold)){
                                                
                                      left = startSpeed - rotate;
                                      right = startSpeed + rotate;
                             
                             }
                                     
                              //Envia os valores de velocidade para os motores
                              motor.setSpeed(left);
                              motor.run(FORWARD);
                              motor1.setSpeed(right);
                              motor1.run(FORWARD);
                       
                      
                              distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                                    
                               // Distancia
                                    
                              Serial.print("Distancia: ");
                              Serial.print(distance);
                              Serial.println(" cm");
                    
                                  
                              while (distance >=10 && distance < 100 ){ // PARAR O CARRINHO
                                        
                                  motor.run(RELEASE);    
                                  delay(1000); 
                                  distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                                        
                              }
      
                              if( (SENSOR1==800 && SENSOR1<1024) && (SENSOR2==800 && SENSOR2<1024) && (SENSOR3==800 && SENSOR3<1024) ){
      
      
                                      crema.run(FORWARD);
      
                                      delay(5000);


                                      crema.run(RELEASE);

      
                                      if (distance==0 && distance<5){     // QUANDO A PEÇA DESPEJAR IRÁ ATIVAR ESSE COMANDO
                                  
                                                   indore = 2; // voltando
                                  
                                      }
                                      
                              
                               }

                      
                      

              
                      case 2: // INDO DE RÉ
                      
                                  //utiliza a mesma velocidade em ambos os motores
                                   
                                   
                                   left = startSpeed;
                                   right = startSpeed;
                                           
                                   //le os sensores e adiciona os deslocamentos
                                   SENSOR1 = analogRead(linha1) + leftOffset;
                                   SENSOR2 = analogRead(linha2);
                                   SENSOR3 = analogRead(linha3) + rightOffset;


                                    if( (SENSOR1==800 && SENSOR1<1024) && (SENSOR2==800 && SENSOR2<1024) && (SENSOR3==800 && SENSOR3<1024) ){


                                       right = 255;
                                       
                                       left = right;

                                        
                                        motor.run(BACKWARD);
                                        motor1.run(BACKWARD);

                                      
                                    }

                                           
                                   //Se SENSOR1 for maior do que o sensor do centro + limiar,
                                   
                                   // vire para a direita
                                   
                                   if (SENSOR1 > (SENSOR2+threshold) ){
                                    
                                          left = startSpeed + rotate;
                                          right = startSpeed - rotate;
                                          
                                            
                                    }
                                           
                                    //Se SENSOR3 for maior do que o sensor do centro + limiar,
                                    // vire para a esquerda
                                    if (SENSOR3 > (SENSOR2+threshold)){
                                                      
                                            left = startSpeed - rotate;
                                            right = startSpeed + rotate;
                                   
                                   }

                                   
                                           
                                  //Envia os valores de velocidade para os motores
                                   motor.setSpeed(left);
                                   motor.run(BACKWARD);
                                   motor1.setSpeed(right);
                                   motor1.run(BACKWARD);
                                   
                
                                   while (distance >=4 && distance < 100 ){ // PARAR O CARRINHO
                                        
                                      motor.run(RELEASE);     
                                      distance = ultrassom.Ranging(CM); // distancia recebe o valor medido em cm
                                        
                                   }
                
                
                                   if(distance1== 0 && distance1<3){
                                    
                                    
                                        processo = 0;
                                    
                                    }
                             
                
                } //switchcase
              
      } // processo 


      motor.run(RELEASE);
      motor1.run(RELEASE);
      
   } // liga 


} // loop
  

 
