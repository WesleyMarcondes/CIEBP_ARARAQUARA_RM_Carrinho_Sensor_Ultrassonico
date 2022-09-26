/*
 *    Última atualização: 2022-09-21.
 *    AUTOR:   CIEBP Araraquara - Espaço 6 Robótica e Modelagem
 *    LINK:    
 *    SKETCH:  Arduino - Carrinho com sensor de obstáculo ultrassonico
 *    DATA:    01/08/2022
 * 
 *    Ideia geral do código: O carrinho anda sempre para frente e em linha reta, quando encontra
 *    um obstaculo até 50 cm de distancia o sensor ultrasonico faz a leitura, para, da ré e de forma
 *    randomica escolhe uma roda para ativar e assim muda de direção.
*/

// Define pinos para componentes 
#define MesquerdoF1  5 //esquerda frente
#define MesquerdoT2  6 //esquerda tras
#define MdireitoT3  9 // //direita tras
#define MdireitoF4  10 //direita frente:

//Define pinos do sensor Ultrasoonico
const int
ECHO = 3,
TRIG = 2,
velocidade = 83;

//Velocidade motor
int 
VelocidadeMD = velocidade + 18,
VelocidadeME = velocidade;

//Distancia do obstaculo
unsigned int 
obstaculo, 
direcao;

int Valor_obstaculo(int TRIG, int ECHO){ // Função para leitura do sensor 
  digitalWrite(TRIG,LOW); //Função que "emite o sinal" para leirura do obstaculo/ desligada
  delayMicroseconds(1);
  digitalWrite(TRIG,HIGH); //Função que "emite o sinal" para leirura do obstaculo/ ligada
  delayMicroseconds(5); 
  digitalWrite(TRIG,LOW); //FALTA COMENTAR A FUNÇÃO DESTE COMANDO
    return 
        pulseIn(ECHO,HIGH)/58; //Retorno da função sensor_morcego será um pulseIN ()
}

Função que faz o carro andar pra frente
void Frente (){
  analogWrite(MesquerdoF1, VelocidadeMD);
  analogWrite(MdireitoF4, VelocidadeME - 3);
  }

// Função que faz o carro andar pra tras  
void Tras (){
  analogWrite(MesquerdoT2, VelocidadeMD);
  analogWrite(MdireitoT3, VelocidadeME);
  }  

 //Função que faz o carro para quando esta andando pra frente 
void StopFrente (){
  digitalWrite(MesquerdoF1,LOW);
  digitalWrite(MdireitoF4, LOW);
  }
void StopTras  (){
  digitalWrite(MesquerdoT2, LOW);
  digitalWrite(MdireitoT3, LOW);
  }

 // Função que faz o carro virar a direita 
void direita(){
  analogWrite(MesquerdoF1, velocidade);
  delay(1000);
  analogWrite(MesquerdoF1, LOW);    
  }

 // Função que faz o carro virar a esquera 
void esquerda(){
  analogWrite(MdireitoF4, velocidade - 20);
  delay(1000);
  analogWrite(MdireitoF4, LOW);
  }

// função que da Ré  
void Re(){
  analogWrite(MesquerdoT2, VelocidadeMD);
  analogWrite(MdireitoT3, VelocidadeME);
  }

// Função que para a ré
void StopRe(){
  analogWrite(MesquerdoT2, 0);
  analogWrite(MdireitoT3, 0);
  }

//Define pinos como entrada ou saida  
void setup(){
  pinMode(ECHO, INPUT); 
  pinMode(TRIG, OUTPUT);
  pinMode(MesquerdoF1, OUTPUT);
  pinMode(MesquerdoT2, OUTPUT);
  pinMode(MdireitoT3, OUTPUT);
  pinMode(MdireitoF4, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}  
void loop(){
 Serial.println(obstaculo);
 delay(1000);
 obstaculo = Valor_obstaculo(TRIG, ECHO);
  
 if (obstaculo <= 50) {
  direcao = random(1,3);
  Serial.println(direcao);
  delay(500);

  switch (direcao){
    case 1:
     StopFrente();
     delay(2000);
     
     Re();
     delay(1000);
     StopRe();
     delay(2000);
      
     esquerda();
     delay(1000);
     break;

     case 2: 
     StopFrente();
     delay(2000);
     
     Re();
     delay(1000);
     StopRe();
     delay(2000);

     direita();
     delay(2000); 

     break;
  }
    } else {
         Frente();
  }
}