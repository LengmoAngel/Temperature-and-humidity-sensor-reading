#include "U8glib.h"
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 2  //定义针脚为2
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);        // I2C / TWI 
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11);  // SW SPI Com: SCL = 10, SDA = 9, CS = 12, DC = 11,RES=RESET
DHT dht(DHTPIN, DHTTYPE);
float sd,wd;
void draw(void) {
  u8g.setFont(u8g_font_8x13); //使用8x13大小的字符
  u8g.setPrintPos(0, 20); // 对应 x，y 轴值
  u8g.print("HUMI(%) :");
  float sd = dht.readHumidity();
  u8g.setPrintPos(73, 20); 
  u8g.print(sd);
  u8g.setPrintPos(0, 40); 
  u8g.print("TEMP(oC):");
  u8g.setPrintPos(73, 40);
  float wd = dht.readTemperature();
  u8g.print(wd);
}

void setup(void) {
  delay(2000);
  dht.begin();
  pinMode(3,OUTPUT);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float sd = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float wd = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);
}

void loop(void) {
digitalWrite(3,HIGH);
  u8g.firstPage();  
  do {
   draw();
  } while( u8g.nextPage() );
  digitalWrite(3,LOW);
  delay(200);
}