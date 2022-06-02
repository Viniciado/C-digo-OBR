#include <AFMotor.h>
int infraC[] = {A8, A9, A10, A11, A12};
// 0 = Ponta Esquerda Cima
// 1 = Esquerda Cima
// 2 = Meio Cima
// 3 = Direita Cima
// 4 = Ponta Direita Cima

int infraB[] = {A13, A14, A15};
// 0 = Esquerda Baixo
// 1 = Meio Baixo
// 2 = Direita Baixo

int ValorBranco[2];

AF_DCMotor motor1(1); // motor esquerda frente
AF_DCMotor motor2(2); // motor esquerda tras
AF_DCMotor motor3(3); // motor direita tras
AF_DCMotor motor4(4); // motor direita frente
 
// Definir valor de branco 
void calibrar() {
delay(1000);
ValorBranco[0] = analogRead(infraC[1])*1000;
ValorBranco[1] = analogRead(infraC[2])*1000;   
}

// Analisar se lê branco ou preto
// 0 = Preto
// 1 = Branco
bool Teste (int entrada, int saida) {
 if (entrada*1000 >= ValorBranco[saida]){
  return true;
 } else {
   return false;
 } 
}

void frente() {
 motor1.setSpeed(200);
 motor1.run(FORWARD);
 motor4.setSpeed(200);
 motor4.run(FORWARD);
}

void esquerda(){
  motor1.setSpeed(150);
  motor1.run(BACKWARD);
  motor4.setSpeed(150);
  motor4.run(FORWARD);
}

void direita(){
  motor1.setSpeed(150);
  motor1.run(FORWARD);
  motor4.setSpeed(150);
  motor4.run(BACKWARD);
}

void Curva90Direita() {
frente();
delay(2000);
if (Teste(analogRead(infraC[2]), 1) && Teste(analogRead(infraC[3]), 1)) {
while (Teste(analogRead(infraC[0]),1)) {
direita();
}
}
}

void Curva90Esquerda() {
frente();
delay(2000);
if (Teste(analogRead(infraC[2]),1) && Teste(analogRead(infraC[1]), 1)) {
while (Teste(analogRead(infraC[0]), 1)) {
esquerda();
}
}
} 

void setup() {
 
 calibrar();
 pinMode(infraC[], INPUT);
 pinMode(infraB[], INPUT);
}

void loop() {
  
  // Curva 90 Direita
  if ( Teste(analogRead(infraC[2]),0) && Teste(analogRead(infraC[3]),0) && Teste(analogRead(infraC[4]), 0)) {
   Curva90Direita();
  // Curva 90 Esquerda
  } else if ( Teste(analogRead(infraC[0]),0) && Teste(analogRead(infraC[1]), 0) && Teste(analogRead(infraC[2]), 0)) {
   Curva90Esquerda();
  // Frente
  } else if ( Teste(analogRead(infraC[2]), 0) && Teste(analogRead(infraB[1]), 0)) {
   frente();
  // Direita
  } else if ( Teste(analogRead(infraC[3]), 0) && Teste(analogRead(infraC[1]), 1)) {
   while (Teste(analogRead(infraC[0]), 0)) {
   direita();
   }
  // Esquerda
  } else if(Teste(analogRead(infraC[1]), 1) && Teste(analogRead(infraC[3]), 0)) {
   while (Teste(analogRead(infraC[0]), 0)) {
   esquerda();
   } 
  // Gap
  } else {
   frente();
 }
}