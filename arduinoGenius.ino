#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
  lcd.begin (16,2);
  pinMode(3, OUTPUT);   // LED Venceu
  pinMode(4, OUTPUT);   // LED Perdeu
  pinMode(5, OUTPUT);   // Buzzer
  pinMode(2, INPUT);    // Botao Iniciar
  pinMode(6, INPUT);    // Botao LVerde
  pinMode(7, INPUT);    // Botao LAmarelo
  pinMode(8, INPUT);    // Botao LVermelho
  pinMode(9, OUTPUT);   // LED Verde
  pinMode(10, OUTPUT);  // LED Amarelo
  pinMode(11, OUTPUT);  // LED Vermelho
}

void loop() {

  //tone(5, 50);
  //noTone(5);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Teste");
  lcd.setCursor(0,1);
  lcd.print("Teste");


}
