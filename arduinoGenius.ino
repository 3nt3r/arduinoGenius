#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

int numerosSorteados[10];
int contador;
int contador2;


boolean jogadorJogou = false;

int vezes = 0;

int contador3 = 0;

int jogadorJogada = 0;

int contador4;

int verificador = -1;


// ========================================================//
// ========================================================//

void setup() {
  pinMode(3, OUTPUT);   // LED Acertou
  pinMode(4, OUTPUT);   // LED Errou
  pinMode(5, OUTPUT);   // Buzzer
  pinMode(2, INPUT);    // Botao Iniciar
  pinMode(6, INPUT);    // Botao LVerde
  pinMode(7, INPUT);    // Botao LAmarelo
  pinMode(8, INPUT);    // Botao LVermelho
  pinMode(9, OUTPUT);   // LED Verde
  pinMode(10, OUTPUT);  // LED Amarelo
  pinMode(11, OUTPUT);  // LED Vermelho

  Serial.begin(9600);
  randomSeed(analogRead(2)); 

  for(contador = 0; contador <= 9; contador++){
    numerosSorteados[contador] = random(9, 12);
  }

  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("APERTE O BOTAO");
  lcd.setCursor(0,1);
  lcd.print("VERMELHO!!!");
  
}

// ========================================================//
// ========================================================//

  void jogo(){
    for(contador2 = 0; contador2 <= 9; contador2++){
      delay(3000);
      for(contador3 = 0; contador3 <= vezes; contador3++){
        digitalWrite(numerosSorteados[contador3], HIGH);
        delay(250);
        digitalWrite(numerosSorteados[contador3], LOW);
        delay(250);
      }
      verificador = -1;
      jogador();
      vezes++; 
    }    
  }

// ========================================================//

  int escolhaJogador(){
     if(digitalRead(6) == HIGH){
      verificador++;
      Serial.println("Verde");
      delay(400);
      jogadorJogou = true;
      return 6;
     }
     if(digitalRead(7) == HIGH){
      verificador++;
      Serial.println("Amarelo");
      delay(400);
      jogadorJogou = true;
      return 7;
     }   
     if(digitalRead(8) == HIGH){
      verificador++;
      Serial.println("Vermelho");
      delay(400);
      jogadorJogou = true;
      return 8;
     }      
  }

// ========================================================//

  void jogador(){
    for(contador4 = -1; contador4 <= vezes; contador4++){

      jogadorJogada = escolhaJogador();


      if(jogadorJogada == 6){
        if(numerosSorteados[contador4+1] == 9){
          jogadorJogou = false;
          if(verificador == vezes){
            break;
          }
        }else{
          perdeu();
        }
      }
  
      if(jogadorJogada == 7){
        if(numerosSorteados[contador4+1] == 10){
          jogadorJogou = false;
          if(verificador == vezes){
            break;
          }
        }else{
          perdeu();
        }
      }
    
      if(jogadorJogada == 8){
        if(numerosSorteados[contador4+1] == 11){
          jogadorJogou = false;
          if(verificador == vezes){
            break;
          }
        }else{
          perdeu();
        }
      }


      while(!jogadorJogou || verificador != vezes){
        jogadorJogada = escolhaJogador();
      }  

      
    }
  
  }

// ========================================================//


  void perdeu(){
    delay(2000);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("Voce Errou!!!!");

    for(contador = 0; contador <= 30; contador++){
      tone(5, 50);
      delay(50);
      noTone(5);
      delay(50);
    }
    asm volatile("jmp 0");
  }


// ========================================================//
// ========================================================//

void loop() {

  if(digitalRead(2) == HIGH){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    lcd.setBacklight(LOW);
    lcd.clear();
    jogo();
  }else{
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    delay(140);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH );
    delay(140);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);    
  }

}

// ========================================================//
// ========================================================//
