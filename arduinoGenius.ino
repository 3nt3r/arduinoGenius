// Créditos à Robson Couto pela Música
// Asa branca - Luiz Gonzaga
// Score available at https://musescore.com/user/190926/scores/181370

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

int numerosSorteados[10];
int vezes = 0;
int contador;
int contador2;
int contador3;
int contador4;

boolean jogadorJogou = false;
int verificador = -1;
int jogadorJogada = -1;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int tempo = 120;
int buzzer = 5;

int melody[] = {
  NOTE_G4,8, NOTE_A4,8, NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_B4,4, 
  NOTE_C5,4, NOTE_C5,2, NOTE_G4,8, NOTE_A4,8,
  NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_C5,4,

  NOTE_B4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
  NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,
  NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,

  NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
  NOTE_G4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
  NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,

  NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,
  NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
  NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,

  NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
  NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,
  NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
  NOTE_G4,-2, REST,4
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;


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

  while(true){
    if(digitalRead(2) == HIGH){
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      lcd.setBacklight(LOW);
      lcd.clear();
      break;
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

  jogo();
}


// ========================================================//
// ========================================================//


  void jogo(){
    for(contador2 = 0; contador2 <= 9; contador2++){
      delay(3000);
      jogadorJogou = false;
      verificador = -1;      
      for(contador3 = 0; contador3 <= vezes; contador3++){
        digitalWrite(numerosSorteados[contador3], HIGH);
        delay(250);
        digitalWrite(numerosSorteados[contador3], LOW);
        delay(250);
      }
      jogador();
      vezes++; 
    }

    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0,0);
    lcd.print("VOCE VENCEU!!!!");

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      divider = melody[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      tone(buzzer, melody[thisNote], noteDuration * 0.9);
      delay(noteDuration);
      noTone(buzzer);
    }
  
    asm volatile("jmp 0");
  }


// ========================================================//


  int escolhaJogador(){
     if(digitalRead(6) == HIGH){
      delay(300);
      jogadorJogou = true;
      return 6;
     }
     if(digitalRead(7) == HIGH){
      delay(300);
      jogadorJogou = true;
      return 7;
     }   
     if(digitalRead(8) == HIGH){
      delay(300);
      jogadorJogou = true;
      return 8;
     }      
  }


// ========================================================//


  void jogador(){
    for(contador4 = 0; contador4 <= vezes; contador4++){
      while(!(verificador == vezes)){
        if(!jogadorJogou){
          jogadorJogada = escolhaJogador();
        }else{
          break;
        }
      }

      if(jogadorJogada == 6){
        if(numerosSorteados[contador4] == 9){
          digitalWrite(3, HIGH);
          delay(50);
          verificador++;
          jogadorJogada = -1;
          jogadorJogou = false;
          delay(50);
          digitalWrite(3, LOW);
          continue;
        }else{
          digitalWrite(4, HIGH);         
          perdeu();
        }
      }
  
      if(jogadorJogada == 7){
        if(numerosSorteados[contador4] == 10){
          digitalWrite(3, HIGH);
          delay(50);
          verificador++;
          jogadorJogada = -1;
          jogadorJogou = false;
          delay(50);
          digitalWrite(3, LOW);
          continue;
        }else{
          digitalWrite(4, HIGH);         
          perdeu();
        }
      }
    
      if(jogadorJogada == 8){
        if(numerosSorteados[contador4] == 11){
          digitalWrite(3, HIGH);
          delay(50);
          verificador++;
          jogadorJogada = -1;
          jogadorJogou = false;
          delay(50);
          digitalWrite(3, LOW);
          continue;
        }else{
          digitalWrite(4, HIGH);
          perdeu();
        }
      }
    }
  }


// ========================================================//


  void perdeu(){
    delay(500);
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


void loop() {}


// ========================================================//
// ========================================================//
