#include <Wire.h>
#include <LiquidCrystal.h>

#include <SoftwareSerial.h>
SoftwareSerial BMS_Serial(4, 5); //RX,TX

int i = 0, inteiro;
int BMS_byte[58];

LiquidCrystal lcd(12, 11, 5, 6, 3, 2);

void setup() {
  Serial.begin(9600);
  //Serial.setTimeout(500);
  BMS_Serial.begin(9600);
  //BMS_Serial.setTimeout(1);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("inicializando");
  lcd.clear();
}

void loop() {
  for (i = 0; i < 58; i++) {
    while (!BMS_Serial.available());
    BMS_byte[i] = BMS_Serial.read();

  }
  int tensaoTotal, correnteEntrada, correnteSaida, celula, tensaoCelula, tempCelula, estadoCarga;
  //tensaoTotal = BMS_byte[1]*1.28 + BMS_byte[2]*0.005;
  celula = BMS_byte[24];
  if (celula <= 16) {
    tensaoTotal = (BMS_byte[1] * 256 + BMS_byte[2]) * 0.005;
    correnteEntrada = (BMS_byte[4] * 256 + BMS_byte[5]) * 0.005;
    correnteSaida = (BMS_byte[7] * 256 + BMS_byte[8]) * 0.005;
    celula = BMS_byte[24];
    tensaoCelula = (BMS_byte[26] * 256 + BMS_byte[27]) * 0.005;
    tempCelula = (BMS_byte[28] * 256 + BMS_byte[29]) - 276;
    estadoCarga = BMS_byte[40];
    Serial.print(tensaoTotal); Serial.print(", ");
    Serial.print(correnteEntrada); Serial.print(", ");
    Serial.print(correnteSaida); Serial.print(", ");
    Serial.print(celula); Serial.print(", ");
    Serial.print(tensaoCelula); Serial.print(", ");
    Serial.print(tempCelula); Serial.print(", ");
    Serial.println(estadoCarga);
    lcd.clear();
    
    lcd.setCursor(0, 0);  
    lcd.print("V:");
    lcd.setCursor(2, 0);
    lcd.print(tensaoTotal);
    
    lcd.setCursor(5, 0);
    lcd.print("Ies:");
    lcd.setCursor(9,0);
    lcd.print(correnteEntrada);
    lcd.setCursor(12, 0);
    lcd.print(correnteSaida);

    lcd.setCursor(0,1);
    lcd.print("VTP:");
    lcd.setCursor(4,1);
    lcd.print(tensaoCelula);
    lcd.setCursor(7, 1);
    lcd.print(tempCelula);
    lcd.setCursor(10, 1);
    lcd.print(estadoCarga);
    lcd.setCursor(14, 1);
    lcd.print(celula);
    
  }

}

/*
  i++;
  if (i >= 58) {
  int tensaoTotal, correnteEntrada, correnteSaida, celula, tensaoCelula, tempCelula, estadoCarga;
  //tensaoTotal = BMS_byte[1]*1.28 + BMS_byte[2]*0.005;
  tensaoTotal = (BMS_byte[1] * 256 + BMS_byte[2]) * 0.005;
  correnteEntrada = (BMS_byte[4] * 256 + BMS_byte[5]) * 0.005;
  correnteSaida = (BMS_byte[7] * 256 + BMS_byte[8]) * 0.005;
  celula = BMS_byte[24];
  tensaoCelula = (BMS_byte[26] * 256 + BMS_byte[27]) * 0.005;
  tempCelula = (BMS_byte[28] * 256 + BMS_byte[29]) - 276;
  estadoCarga = BMS_byte[40];
  Serial.print(tensaoTotal); Serial.print(", ");
  Serial.print(correnteEntrada); Serial.print(", ");
  Serial.print(correnteSaida); Serial.print(", ");
  Serial.print(celula); Serial.print(", ");
  Serial.print(tensaoCelula); Serial.print(", ");
  Serial.print(tempCelula); Serial.print(", ");
  Serial.println(estadoCarga);

  i = 0;
  }
  }
*/
