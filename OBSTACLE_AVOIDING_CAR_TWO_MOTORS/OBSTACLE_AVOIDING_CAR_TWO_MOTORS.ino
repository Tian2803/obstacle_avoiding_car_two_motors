#include <Servo.h> 
#include <NewPing.h>
#include <AFMotor.h>  

#define TRIG_PIN A0
#define ECHO_PIN A1
#define distMax 200
NewPing Dist(TRIG_PIN, ECHO_PIN, distMax);   //(trig,echo,dist max)
Servo myServo; 

int distancia = 0;
int distanciaD = 0;
int distanciaIz = 0;
boolean Booleano = false;

AF_DCMotor MotorL(1, MOTOR12_1KHZ); 
AF_DCMotor MotorD(2, MOTOR12_1KHZ);

void setup() {
  myServo.attach(10);  
  myServo.write(115);
  delay(1000); 
  myServo.write(65);
  delay(500);
  myServo.write(160);
  delay(500);
  myServo.write(115);
}

void loop() {
distancia = medirDistancia();
if (distancia >= 25 && distancia <= 250)
{
  Adelante();
}
else if (distancia < 25)
{
  Frenar();
  delay(150);
  Reversa();
  delay(250);
  Frenar();
  delay(250);
  distanciaD = mirarDerecha();
  delay(250);
  distanciaIz = mirarIzquierda();
  delay(250);

  if(distanciaD >= distanciaIz)
    {
      GirarDerecha();
      Frenar();
    }
    else if(distanciaIz >= distanciaD)
    {
      GirarIzquierda();
      Frenar();
    }
  }
}

//Servo gira a la derecha para observar si hay obstaculos 
int mirarDerecha()
{
    myServo.write(60); 
    delay(350);
    int distancia = medirDistancia();
    return distancia;
}

//Servo gira a la izquierda para observar si hay obstaculos 
int mirarIzquierda()
{
    myServo.write(165); 
    delay(350);
    int distancia = medirDistancia();
    delay(50);
    myServo.write(115); 
    return distancia;
}
  
  //Mide la distancia
  int medirDistancia() 
  { 
    delay(10);
    int ditanciaCM = Dist.ping_cm();
    if(ditanciaCM <= 0 || ditanciaCM >= 250)
    {
      ditanciaCM = 250;
    }
    return ditanciaCM;
  }
 
//Funcion que se encarga de frenar
void Frenar() {
  MotorL.run(RELEASE); 
 } 

 //Funcion qeu se encarga de ir adelante 
void Adelante() {
 if(Booleano == false)
  {
    Booleano = true;
    MotorL.run(FORWARD);          
    controlVelocidad();
  }
}

//Funcion que se encarga de ir hacia atras
void Reversa() {
    Booleano = false;
    MotorL.run(BACKWARD);      
    controlVelocidad();
}  

//Funcion que se encarga de girar a la derecha
void GirarDerecha() {
  MotorD.run(FORWARD);    
  delay(400);  
} 

//Funcion que se encarga de girar a la izquierda
void GirarIzquierda() {  
  MotorD.run(BACKWARD);    
  delay(400);
} 

//Funcion del control de velocidad para reducir el consumo de baterias
 void controlVelocidad(){
   for (int velocidad = 0; velocidad < 160; velocidad +=2) 
   {
      MotorL.setSpeed(velocidad);
      MotorD.setSpeed(velocidad);
      delay(3);
   }
  }
  
  //Fin del recorrido del codigo