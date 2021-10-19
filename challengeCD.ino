#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); 
#include "DHT.h"
#define DHTPIN 4 // DHT11 的腳位 (可變的 pin 位)
#define DHTTYPE DHT11 // 宣告 DHT 的型號
DHT dht(DHTPIN, DHTTYPE); // 宣告 dht 物件
#include <Ultrasonic.h>
Ultrasonic us(2, 3); // 測量深度距離 in cm (Trig, Echo)
Ultrasonic ush(12,13); // 車子前面的 SR04, 用來測量終點距離 in cm
const int lf = 5;
const int rf = 6;
int botDistance = 0;
int frontDistance = 0;
int state = 0;
int depth = 0;

void runMotor(int lSpeed, int rSpeed){
  analogWrite(lf, lSpeed);  
  analogWrite(rf, rSpeed);
}

void lcdDepth(int depth){
  lcd.setCursor(0, 0);
  lcd.print("The Depth:");
  lcd.setCursor(0,1);
  lcd.print(depth);
}

void lcdTemp(int temperature){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The temperature:");
  lcd.setCursor(0,1);
  lcd.print(temperature);
}

void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();
}

//state 1: 直走
//state 2: 停下等測深
//state 3: 停下等測溫
void loop(){
  botDistance = us.read() - 8;//扣除車高
  frontDistance = ush.read();
  if (botDistance < 3){//判斷是否遇到深度關
    state = 1;
  }
  else{
    state = 2;
  }
  if (frontDistance <10){//快撞牆停下測溫
    state = 3;
  }

  if (state == 1){
    runMotor(77, 80);
  }
  else if (state == 2){
    runMotor(0, 0);
    delay(2000);
    lcdDepth(us.read());
    delay(10000);//顯示十秒
    lcd.clear();
    runMotor(77, 80);
    delay(2000);//走出深坑
  }
  else{
    runMotor(0, 0);
    while(1){
      float temperature = dht.readTemperature();
      lcdTemp(temperature);
      delay(1000);//dht頻率
    }
  }
}
