#include "U8glib.h"
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 2  //定义针脚为2
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);        // I2C / TWI
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11);  // SW SPI Com: SCL = 10, SDA = 9, CS = 12, DC = 11,RES=RESET
DHT dht(DHTPIN, DHTTYPE);
extern float sd, wd;
float sd, wd;
double y[6];//未处理数值
int x[6];//已处理数值
double k;
void draw(void) {

  u8g.setFont(u8g_font_8x13); //使用8x13大小的字符
  u8g.setPrintPos(0, 20); // 对应 x，y 轴值，下同理
  u8g.print("HUMI(%) :");
  float sd = dht.readHumidity();
  u8g.setPrintPos(73, 15);
  u8g.print(sd);//输出湿度
  u8g.setPrintPos(0, 30);
  u8g.print("TEMP(oC):");
  u8g.setPrintPos(73, 30);
  float wd = dht.readTemperature();
  u8g.print(wd);//输出温度
  //土壤湿度
  y[6] =  floor(analogRead (A6));//6
  u8g.setPrintPos(0, 45);
  x[6] = 100-floor((y[6] / 1023) * 100);
  u8g.print(x[6]);
  y[5] =  floor(analogRead (A5));//5
  x[5] = 100 - floor((y[5] / 1023) * 100);
  u8g.setPrintPos(20, 45);
  u8g.print(x[5]);
  y[4] =  floor(analogRead (A4));//4
  x[4] = 100 - floor((y[4] / 1023) * 100);
  u8g.setPrintPos(40, 45);
  u8g.print(x[4]);
  y[3] =  floor(analogRead (A3));//3
  x[3] = 100 - floor((y[3] / 1023) * 100);
  u8g.setPrintPos(0, 60);
  u8g.print(x[3]);
  y[2] =  floor(analogRead (A2));//2
  x[2] = 100 - floor((y[2] / 1023) * 100);
  u8g.setPrintPos(20, 60);
  u8g.print(x[2]);
  y[1] =  floor(analogRead (A1));//1
  x[1] = 100 - floor((y[1] / 1023) * 100);
  u8g.setPrintPos(40, 60);
  u8g.print(x[1]);

}


void setup(void) {
  delay(2000);
  dht.begin();
  pinMode(3, OUTPUT);;
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float sd = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float wd = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);
}

void loop(void) {
  delay(1000);

  digitalWrite(3, HIGH);
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  digitalWrite(3, LOW);
}