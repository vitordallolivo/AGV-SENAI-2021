

// THEMOSISTOR

#define NTC A0
// https://www.thinksrs.com/downloads/programs/Therm%20Calc/NTCCalibrator/NTCcalculator.htm
// Para conseguir as variaveis de c1, c2 e c3

float R1 = 1200, logR2, R2, c1 = 1.484778004e-03, c2 =2.348962910e-04 , c3 = 1.006037158e-07;

int temp,celsius;

char letra='z'; // variavel do bluetooth
#include "SoftwareSerial.h"
SoftwareSerial MyBlue(0, 1);// RX | TX

// botão de inicio e parada
#define botao 13
// resistor de aquecimento
#define aquecimento 22 
//resistor leitor do aquecimento



//Relé que manda o DI1, LIGA GERAL 
#define DI1 52// 300 RPM

//Relé DI2
#define DI3 48//800 RPM

//Relé DI3
#define DI4 38 // 1500 RPM

int liga=0;
/*
   ///////////////   DI3*DI4 = 2100 RPM /////////////                                         
*/


// função retirada de https://www.thinksrs.com/downloads/programs/Therm%20Calc/NTCCalibrator/NTCcalculator.htm

int temperatura(int T){
  
  
  temp=analogRead(NTC);
  R2 = R1 * (1023.0 / (float)temp - 1.0);
  logR2 =log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Steinhart and Hart Equation. T  = 1 / (c1 + c2(ln(R2)) + c3(ln(R2))^3);
  T = T - 273.15;

  return (T);
  }


void bluetooth(){
  
         letra = Serial.read();

         switch (letra){

             
             default:
              
                  digitalWrite(DI1,LOW);  
                  Serial.println("off");
                  digitalWrite(DI3,LOW);
                  digitalWrite(DI4,LOW);
                  break;
               
                
             case 'a':
    
    
                  digitalWrite(DI1,HIGH); // 300 rpm
                  digitalWrite(DI3,LOW);
                  digitalWrite(DI4,LOW);
                
              
              
             case 'b':
                  
                  
                  digitalWrite(DI1,HIGH);
                  digitalWrite(DI3,HIGH); // 800 rpm
                  digitalWrite(DI4,LOW);
                    
                  
                  
             case 'c':
                        
                  digitalWrite(DI1,HIGH);
                  digitalWrite(DI3,LOW);
                  digitalWrite(DI4,HIGH); // 1500 rpm
                        
                        
             case 'd' :
                            
                  digitalWrite(DI1,HIGH);
                  digitalWrite(DI3,HIGH);
                  digitalWrite(DI4,HIGH); // 2100 rpm
                            
                            
                            
              } //switch case
  
  
  

} // função bluetooth

void setup() {
  // put your setup code here, to run once:

     Serial.begin(9600);


      pinMode(botao,INPUT);
      pinMode(NTC,INPUT); // input analogico
      pinMode(aquecimento,OUTPUT);
      pinMode(DI1,OUTPUT);
      pinMode(DI3,OUTPUT);
      pinMode(DI4,OUTPUT);
}

void loop() {

      
      bluetooth(); // retorna função do bluetooth
      Serial.println(temperatura(celsius));  // retorna função da temperatura 
      temp=analogRead(NTC) ;
      digitalWrite(aquecimento,LOW);
      digitalWrite(DI1,LOW);
      digitalWrite(DI3,LOW);
      digitalWrite(DI4,LOW);
      // Serial.println(temp); 


      while (digitalRead(botao) == HIGH ) 
      {

              liga=1;
             // Serial.println("liga");

        }

          
     

      while(liga == 1)
      {  
             // Serial.println("liga");
              digitalWrite(aquecimento,HIGH); // aqueciment liga 
              digitalWrite(DI1,HIGH); // /RPM de 300 começa

              temp=analogRead(NTC) ;
              Serial.println(temperatura(celsius));







              if (temp>=154  && temp<175)
              {
                      Serial.println("50ºC");
                      digitalWrite(aquecimento,HIGH); 
                      digitalWrite(DI3,HIGH);
                      Serial.println("estágio dos 50");
                      temp=analogRead(NTC) ;
                      
                      Serial.println(temperatura(celsius));
                      
                     if (digitalRead(botao) == HIGH){  
                       delay(300);
                       while (digitalRead (botao) == HIGH) 
                         {   
                                liga=0;  // DESLIGA TUDO
                                Serial.println("desliga");

                       }
                 }

              } // 50ºC a 75ºC

               

                if (temp>=175  && temp<219)
               {
                     digitalWrite(DI3,LOW);
                     digitalWrite(aquecimento,HIGH);  
                     Serial.println("75ºC");
                     digitalWrite(DI4,HIGH);
                     temp=analogRead(NTC);
                     
                     Serial.println(temperatura(celsius));
                     
                     if (digitalRead(botao) == HIGH){  
                       delay(300);
                       while (digitalRead (botao) == HIGH) 
                         {   
  
  
                            liga=0;  // DESLIGA TUDO
                            Serial.println("desliga");
  
                         }
                    }

               }

              


                if (temp>=219){

                       if (digitalRead(botao) == HIGH){  
                           delay(300);
                           while (digitalRead (botao) == HIGH) 
                             {   


                                liga=0;  // DESLIGA TUDO
                                Serial.println("desliga");

                             }
                       }
                        digitalWrite(aquecimento,HIGH); 
                        temp=analogRead(NTC) ;
                        Serial.println(temperatura(celsius));
                        digitalWrite(DI3,HIGH);
                        digitalWrite(DI4,HIGH);
                        delay(15000); //
                        digitalWrite(DI3,LOW);
                        digitalWrite(DI4,LOW);
                        liga=0;
                        

                } // 100ºC




       } // liga









} // Tudo dentro disso
