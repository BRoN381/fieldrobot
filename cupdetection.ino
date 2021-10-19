String str;
int num;
const int lf = 5;
const int lb = 3;
const int rf = 6;
const int rb = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    str = Serial.readStringUntil('\n');
    num = str.toInt();
    int cup = num/10;
    int arrow = num%10;
    //no arrow do cup detect
    if (arrow == 0){
      if (cup == 2){
        analogWrite(lf, 80);
        analogWrite(rf, 80);
        analogWrite(rb, 0);
        analogWrite(lb, 0);
      }
      else if (cup == 3){
        analogWrite(lf, 140);
        analogWrite(rf, 80);
        analogWrite(rb, 0);
        analogWrite(lb, 0);
      }
      else if (cup == 1){
        analogWrite(lf, 80);
        analogWrite(rf, 140);
        analogWrite(rb, 0);
        analogWrite(lb, 0);
      }
    }
    else if (arrow == 2){//右轉
      analogWrite(rf, 80);
      analogWrite(lf, 77);
      analogWrite(rb, 0);
      analogWrite(lb, 0);
      delay(5000);
      analogWrite(rb, 80);//right
      analogWrite(lf, 77);
      analogWrite(rf, 0);
      analogWrite(lb, 0);
      delay(3000);
      analogWrite(rf, 80);
      analogWrite(lf, 77);
      analogWrite(rb, 0);
      analogWrite(lb, 0);
      delay(10000);
      analogWrite(rb, 80);
      analogWrite(lf, 77);
      analogWrite(rf, 0);
      analogWrite(lb, 0);
    }
    else{//左轉
      analogWrite(rf, 80);
      analogWrite(lf, 77);
      analogWrite(rb, 0);
      analogWrite(lb, 0);
      delay(5000);
      analogWrite(rf, 80);//right
      analogWrite(lb, 77);
      analogWrite(rb, 0);
      analogWrite(lf, 0);
      delay(3000);
      analogWrite(rb, 80);
      analogWrite(lb, 77);
      analogWrite(rf, 0);
      analogWrite(lf, 0);
      delay(10000);
      analogWrite(rf, 80);
      analogWrite(lb, 77);
      analogWrite(rb, 0);
      analogWrite(lf, 0);
    }
  }
}
