# 吃豆人游戏 - 串口摇杆控制说明

## 功能概述

本游戏现在支持通过Arduino摇杆传感器来控制吃豆人的移动，除了原有的键盘控制外，还可以使用连接到COM4端口的摇杆进行游戏。

## 硬件要求

- Arduino开发板
- 摇杆传感器模块
- USB连接线
- 支持Web Serial API的浏览器（Chrome 89+）

## Arduino代码

摇杆传感器应该按照以下代码进行编程，通过串口发送方向数据：

```cpp
const int xPin = A0;     //X attach to A0
const int yPin = A1;     //Y attach to A1
const int btPin = 7;     //Bt attach to digital 7
int stat=0;

void setup() {
  pinMode(btPin, INPUT);
  digitalWrite(btPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = digitalRead(btPin);
  
  // 方向判断
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
```

## 使用方法

### 1. 硬件连接
- 将Arduino通过USB连接到电脑
- 确保Arduino运行上述摇杆控制代码
- 记住Arduino的COM端口号（通常是COM4）

### 2. 浏览器设置
- 使用Chrome浏览器（版本89或更高）
- 确保网站运行在HTTPS环境下（Web Serial API要求）

### 3. 游戏控制

#### 键盘控制（原有功能）
- 方向键：控制吃豆人移动
- 空格键/回车键：暂停/继续游戏

#### 串口控制（新功能）
- **C键**：连接串口设备
  - 按下C键后会弹出串口选择对话框
  - 选择对应的COM端口（如COM4）
  - 连接成功后控制台会显示"串口连接成功"

- **D键**：断开串口连接
  - 按下D键断开当前串口连接
  - 断开后控制台会显示"串口连接已断开"

#### 摇杆控制
连接成功后，摇杆的移动会直接控制吃豆人：
- 摇杆向右：吃豆人向右移动
- 摇杆向下：吃豆人向下移动  
- 摇杆向左：吃豆人向左移动
- 摇杆向上：吃豆人向上移动
- 摇杆居中：无操作

## 数据协议

Arduino通过串口发送的数据格式：
- `0`：摇杆居中，无操作
- `1`：向右移动
- `2`：向下移动
- `3`：向左移动
- `4`：向上移动

## 故障排除

### 1. 浏览器不支持
- 确保使用Chrome 89+版本
- 确保网站运行在HTTPS环境

### 2. 串口连接失败
- 检查Arduino是否正确连接
- 确认COM端口号是否正确
- 检查Arduino代码是否正确上传

### 3. 摇杆无响应
- 检查摇杆硬件连接
- 确认Arduino串口输出是否正常
- 查看浏览器控制台是否有错误信息

## 技术实现

本功能使用了以下技术：
- **Web Serial API**：用于浏览器与串口设备通信 <mcreference link="https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API" index="3">3</mcreference>
- **TextDecoderStream**：用于解码串口数据流 <mcreference link="https://developer.mozilla.org/en-US/docs/Web/API/SerialPort" index="1">1</mcreference>
- **异步数据处理**：实时处理摇杆输入数据 <mcreference link="https://developer.chrome.com/docs/capabilities/serial" index="2">2</mcreference>

## 兼容性

- ✅ Chrome 89+
- ✅ Edge 89+
- ❌ Firefox（暂不支持）
- ❌ Safari（暂不支持）

---

**注意**：Web Serial API是一个实验性功能，需要在支持的浏览器中使用。建议在本地开发环境或HTTPS环境下测试。