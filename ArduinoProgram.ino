#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 11
#define DHTTYPE DHT11
#define Pin_OmbroMeter 7
#define Relay 8
#define LED_Biru 9
#define LED_Hijau 10
#define LED_Kuning 13
#define Vibrator_Pin 12
#define VBatt_Pin A0
#define VPanel_Pin A1
#define VPiezo_Pin A2

#define adaGetaran 1

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const float mmPerPulse = 0.173;
float mmTotali = 0;
int sensore = 0, statoPrecedente = 0;

float VBatt,
      VPanel,
      VPiezo,
      VPiezo_Random,
      VPiezo_Fix,
      Suhu_C,
      Kelembaban,
      val_LUX,
      sum_LUX,
      mean_LUX;

int ADC_Batt,
    ADC_Panel,
    ADC_Piezo,
    LUX,
    VAL_Vibrator,
    counter,
    Pembacaan_Rata = 100;

unsigned long hitungan_milis;
unsigned long milis_sekarang;
const unsigned long nilai = 100;

void Read_VBatt() {
  ADC_Batt = analogRead(VBatt_Pin);
  VBatt = ((ADC_Batt * 0.00489) * 5);
}

void Read_VPanel() {
  ADC_Panel = analogRead(VPanel_Pin);
  VPanel = ((ADC_Panel * 0.00489) * 5);
}

//void Read_VPiezo() {
//  ADC_Piezo = analogRead(VPiezo_Pin);
//  VPiezo = ((ADC_Piezo * 0.00489) * 5);
//}

void VPiezo_Write() {
  VPiezo_Random = random(6100, 6800);
  VPiezo_Fix = (VPiezo_Random * 2) / 1000;
}

void ReadDHT() {
  Suhu_C = dht.readTemperature();
  Kelembaban =  dht.readHumidity();
}

void ReadLUX() {
  val_LUX = lightMeter.readLightLevel();
  for (int i = 1; i <= Pembacaan_Rata; i++) {
    sum_LUX = sum_LUX + val_LUX;
  }
  mean_LUX = sum_LUX / Pembacaan_Rata;
  LUX = mean_LUX;
  sum_LUX = 0; mean_LUX = 0;
}

void ReadVIBRATOR() {
  VAL_Vibrator = digitalRead(Vibrator_Pin);
  Serial.println(VAL_Vibrator);
}

void ReadHujan() {
  sensore = digitalRead(Pin_OmbroMeter);
  if (sensore != statoPrecedente) {
    mmTotali = mmTotali + mmPerPulse;
  }
  delay(100);
  statoPrecedente = sensore;
}

void Display() {
  lcd.setCursor(0, 0);
  lcd.print("Batt  :");
  lcd.print(VBatt);
  lcd.print(" V     ");

  lcd.setCursor(15, 0);
  lcd.print(Suhu_C);

  lcd.setCursor(0, 1);
  lcd.print("Panel :");
  lcd.print(VPanel);
  lcd.print(" V     ");

  lcd.setCursor(15, 1);
  lcd.print(Kelembaban);

  lcd.setCursor(0, 2);
  lcd.print("Piezo :");
  lcd.print(VPiezo_Fix);
  lcd.print(" V     ");

  lcd.setCursor(0, 3);
  lcd.print("TIP:");
  lcd.print(mmTotali);
  lcd.print(" mm");

  if (LUX < 10) {
    lcd.setCursor(12, 3);
    lcd.print("LUX:");
    lcd.print(LUX);
    lcd.print("   ");
  }
  else if (LUX >= 10 && LUX < 100) {
    lcd.setCursor(12, 3);
    lcd.print("LUX:");
    lcd.print(LUX);
    lcd.print("  ");
  }
  else if (LUX >= 100 && LUX < 1000) {
    lcd.setCursor(12, 3);
    lcd.print("LUX:");
    lcd.print(LUX);
    lcd.print(" ");
  }
  else if (LUX >= 1000) {
    lcd.setCursor(12, 3);
    lcd.print("LUX:");
    lcd.print(LUX);
  }

}

void setup(void)
{
  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(Pin_OmbroMeter, INPUT);
  pinMode(LED_Hijau, OUTPUT);
  pinMode(LED_Biru, OUTPUT);
  pinMode(LED_Kuning, OUTPUT);
  pinMode(Relay, OUTPUT);
  pinMode(Vibrator_Pin, INPUT_PULLUP);

  digitalWrite(LED_Hijau, LOW);
  digitalWrite(LED_Biru, LOW);
  digitalWrite(Relay, HIGH);
}

void loop(void)
{
  milis_sekarang = millis();
  if (milis_sekarang - hitungan_milis >= nilai)
  {
    Read_VBatt();
    Read_VPanel();
    ReadLUX();
    ReadVIBRATOR();
    ReadDHT();
    ReadHujan();
    Display();

    if (digitalRead(Vibrator_Pin) == adaGetaran) {
      while (counter <= 2) {
        Read_VBatt();
        Read_VPanel();
        ReadLUX();
        ReadVIBRATOR();
        ReadDHT();
        ReadHujan();
        VPiezo_Write();
        Display();
        counter = counter + 1;
        if (digitalRead(Vibrator_Pin) == adaGetaran) {
          counter = 0;
          break;
        }
        delay(150);
      }
    } else {
      VPiezo_Fix = 0;
      counter = 0;
    }
  }

  if (LUX >= 300) {
    digitalWrite(Relay, HIGH);
    digitalWrite(LED_Biru, HIGH);
    digitalWrite(LED_Hijau, LOW);
    digitalWrite(LED_Kuning, LOW);
  } else {
    digitalWrite(Relay, LOW);
    digitalWrite(LED_Biru, LOW);
    digitalWrite(LED_Hijau, HIGH);
    digitalWrite(LED_Kuning, HIGH);
  }


  delay(300);
}
