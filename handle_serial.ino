const int xPin = A0;     //X attach to A0
const int yPin = A1;     //Y attach to A1
const int btPin = 7;     //Bt attach to digital 7
int stat=0;

void setup() {
  pinMode(btPin, INPUT); //set btpin as INPUT
  digitalWrite(btPin, HIGH); //and HIGH (enable internal pull-up)
  Serial.begin(9600);     //initialize serial
}

void loop() {
  // 读取一次并复用值（提高性能）
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = digitalRead(btPin);
  /*
  Serial.print("X: ");
  Serial.print(xValue, DEC);
  Serial.print("\tY: ");
  Serial.print(yValue, DEC);
  Serial.print("\tZ: ");
  Serial.println(zValue);*/

  // 方向判断（注意：摇杆居中值通常为512，实际需校准）
  if (xValue > 500 && xValue < 600 && yValue > 500 && yValue < 600) {
    stat = 0;//中间
  } else if (xValue < 600 && yValue > 600) {
    stat = 1;//右
  } else if (xValue < 500 && yValue < 600) {
    stat = 2;//下
  }else if (xValue > 500 && yValue < 500) {
    stat = 3;//左
  } else if (xValue > 600 && yValue > 500) {
    stat = 4;//上
  } 
  Serial.println(stat);
  delay(100);
}