//Importación de librerias
#include <Servo.h>
#include <NewPing.h>
#include <AFMotor.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define distMax 200

NewPing Dist(TRIG_PIN, ECHO_PIN, distMax);  //(trig,echo,dist max)
Servo myServo;

int distancia = 0;
int distanciaD = 0;
int distanciaIz = 0;
boolean Booleano = false;

AF_DCMotor motorLeft1(2, MOTOR12_1KHZ);
AF_DCMotor motorRight1(3, MOTOR34_1KHZ);

void setup() {
  myServo.attach(10);
  myServo.write(115); // Mueve el servo a 115 grados
  delay(1000);
  myServo.write(65);  // Mueve el servo a 65 grados
  delay(500);
  myServo.write(160); // Mueve el servo a 160 grados
  delay(500);
  myServo.write(115); // Mueve el servo a a 115 grados.
}

void loop() {
  distancia = medirDistancia();
  if (distancia >= 25 && distancia <= 250) {
    Adelante();
  } else if (distancia < 25) {
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

    if (distanciaD >= distanciaIz) {
      GirarDerecha();
      Frenar();
    } else if (distanciaIz >= distanciaD) {
      GirarIzquierda();
      Frenar();
    }
  }
}

// Función para medir la distancia hacia adelante
int medirDistancia() {
  delay(10);  // Espera para evitar lecturas incorrectas
  int distanciaCM = Dist.ping_cm();  // Realiza la medición de la distancia en centímetros
  // Si la distancia es menor o igual a cero, o mayor o igual a 250, se considera como 250
  if (distanciaCM <= 0 || distanciaCM >= 250) {
    distanciaCM = 250;
  }
  return distanciaCM;  // Retorna la distancia medida
}

// Función para detener los motores
void Frenar() {
  motorLeft1.run(RELEASE);
  motorRight1.run(RELEASE);
}

// Función para mover el robot hacia adelante
void Adelante() {
  if (Booleano == false) {
    Booleano = true;
    motorLeft1.run(FORWARD);
    motorRight1.run(FORWARD);
    controlVelocidad();
  }
}

// Función para mover el robot hacia atrás
void Reversa() {
  Booleano = false;
  motorLeft1.run(BACKWARD);
  motorRight1.run(BACKWARD);
  controlVelocidad();
}

// Función para girar el servo hacia la derecha y medir la distancia
int mirarDerecha() {
  myServo.write(60);  // Mueve el servo a una posición específica para mirar a la derecha
  delay(350);  // Espera para estabilizar la posición del servo
  int distancia = medirDistancia();  // Realiza la medición de la distancia
  return distancia;  // Retorna la distancia medida
}

// Función para girar el servo hacia la izquierda y medir la distancia
int mirarIzquierda() {
  myServo.write(165);  // Mueve el servo a una posición específica para mirar a la izquierda
  delay(350);  // Espera para estabilizar la posición del servo
  int distancia = medirDistancia();  // Realiza la medición de la distancia
  delay(50);  // Espera adicional para estabilizar la posición del servo
  myServo.write(115);  // Mueve el servo a su posición central original
  return distancia;  // Retorna la distancia medida
}

// Función para mover el robot hacia la derecha
void GirarDerecha() {
  motorLeft1.run(FORWARD);
  motorRight1.run(BACKWARD);
  // Incrementa gradualmente la velocidad de giro
  for(int velocidad = 0; velocidad < 130; velocidad += 2) {
    motorLeft1.setSpeed(velocidad);
    motorRight1.setSpeed(velocidad * 0.3);  // Establece la velocidad para la rueda derecha (30% de la velocidad de la izquierda)
    delay(3);
  }
  delay(400);  // Espera para completar el giro
}

// Función para mover el robot hacia la izquierda
void GirarIzquierda() {
  motorLeft1.run(BACKWARD);
  motorRight1.run(FORWARD);
  // Incrementa gradualmente la velocidad de giro
  for(int velocidad = 0; velocidad < 130; velocidad += 2) {
    motorLeft1.setSpeed(velocidad * 0.3);  // Establece la velocidad para la rueda izquierda (30% de la velocidad de la izquierda)
    motorRight1.setSpeed(velocidad); 
    delay(3);
  }
  delay(400);  // Espera para completar el giro
}

// Función para controlar la velocidad de los motores
void controlVelocidad() {
  // Incrementa gradualmente la velocidad de avance
  for (int velocidad = 0; velocidad < 130; velocidad += 2) {
    motorLeft1.setSpeed(velocidad);
    motorRight1.setSpeed(velocidad);
    delay(3);
  }
}

// Final del código
