/*!
 * @file  basic.ino
 * @brief  本示例介绍了DFRobot_ES_RS485库的所有用法
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license    The MIT License (MIT)
 * @author     [fary](feng.yang@dfrobot.com)
 * @version    V1.0
 * @date       2022-07-14
 * @url        https://github.com/DFRobot/DFRobot_ES_RS485
 */
#include "DFRobot_ES_RS485.h"

#define DEVICE_ADDR 0x32
//#define RS485_MODE
#ifdef RS485_MODE //RS485通信
  #if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
    #include "SoftwareSerial.h"
    SoftwareSerial mySerial(/*rx =*/4, /*tx =*/5);
    DFRobot_ES_RS485 Sensor(/*Stream *=*/&mySerial,/*addr=*/DEVICE_ADDR,/*depin=*/16);
  #else
    DFRobot_ES_RS485 Sensor(/*Stream *=*/&Serial1,/*addr=*/DEVICE_ADDR,/*depin=*/16);
  #endif
#else //串口通信
  #if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
    #include "SoftwareSerial.h"
    SoftwareSerial mySerial(/*rx =*/4, /*tx =*/5);
    DFRobot_ES_RS485 Sensor(/*Stream *=*/&mySerial,/*addr=*/DEVICE_ADDR);
  #else
    DFRobot_ES_RS485 Sensor(/*Stream *=*/&Serial1,/*addr=*/DEVICE_ADDR);
  #endif
#endif

void setup(void)
{
#if defined(ARDUINO_AVR_UNO)||defined(ESP8266)
  mySerial.begin(9600);
#elif defined(ESP32)
  Serial1.begin(9600, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  Serial1.begin(9600);
#endif
  Serial.begin(115200);

  while(Sensor.begin() != true){
    Serial.println(" Sensor initialize failed!!");
    delay(1000);
  }
  Serial.println(" Sensor  initialize success!!");
  Serial.print("Firmware Version: ");
  Serial.println(Sensor.getFirmwareVersion());
  Serial.print("Device Vid: ");
  Serial.println(Sensor.getVid());
  Serial.print("Device Pid: ");
  Serial.println(Sensor.getPid());
  
  /*修改设备通信地址范围（0x01~0xF7），设备掉电生效*/
  //Sensor.setDeviceAddress(0x31);
  
  /**
   * 修改设备波特率，设备掉电生效。可选参数有：
   *  eBaud2400   设置SEN0538波特率为2400   
   *  eBaud4800   设置SEN0538波特率为4800   
   *  eBaud9600   设置SEN0538波特率为9600   
   *  eBaud14400  设置SEN0538波特率为14400  
   *  eBaud19200  设置SEN0538波特率为19200  
   *  eBaud38400  设置SEN0538波特率为38400  
   *  eBaud57600  设置SEN0538波特率为57600  
   *  eBaud115200 设置SEN0538波特率为115200 
   */
  //Sensor.setDeviceBaud(Sensor.eBaud9600);

}

void loop()
{
  float temperature=Sensor.getTemperature();
  float humidity = Sensor.getHumidity();

  //上面获取的温湿度经过内部计算，如果你需要更高的精度，请采用获取原始数据的方式
  //float temperature = -45 + 175*((Sensor.getTemperatureRaw())/65536.0);
  //float humidity =  ((Sensor.getHumidityRaw()) * 100.0) / 65536.0;

  /**
   * This API is used to get the sensor operating status
   * Operating status:
   *   0: Normal operation; 
   *   1: Warm-Up phase; 
   *   2: Initial Start-Up phase; 
   *   3: Invalid output
   */
  uint16_t ens160Status=Sensor.getENS160Status();

  /**
   *  Get the air quality index calculated on the basis of UBA
   *  Return value range: 1-5 (Corresponding to five levels of Excellent, Good, Moderate, Poor and Unhealthy respectively)
   */
  uint16_t AQI=Sensor.getAQI();

  /**
   * Get TVOC concentration
   * Return value range: 0–65000, unit: ppb
   */
  uint16_t TVOC=Sensor.getTVOC();

  /**
   * Get CO2 equivalent concentration calculated according to the detected data of VOCs and hydrogen (eCO2 – Equivalent CO2)
   * Return value range: 400–65000, unit: ppm
   * Five levels: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000),Poor(1000 - 1500), Unhealthy(> 1500)
   */
  uint16_t ECO2=Sensor.getECO2();

  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.println(" %RH");
  Serial.print("ens160Status: ");
  Serial.println(ens160Status);
  Serial.print("AQI: ");
  Serial.println(AQI);
  Serial.print("TVOC: ");
  Serial.print(TVOC);
  Serial.println(" ppb");
  Serial.print("ECO2: ");
  Serial.print(ECO2);
  Serial.println(" ppm");
  delay(1000);
}