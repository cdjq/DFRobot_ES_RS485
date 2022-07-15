# DFRobot_ES_RS485
* [中文版](./README_CN.md)

本库提供了获取SEN0538采集数据的全部方法，用户只需要简单的使用本库就可以获取到SEN0538采集的数据。

![产品实物图](./resources/images/SEN0538.png)


## Product Link (https://www.dfrobot.com/)
    SKU：SEN0538


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary
* 读取温湿度
* 读取空气质量
* 读取ECO2数据
* 读取TVOC数据


## Installation

这里提供两种使用本库的方法：
1. 打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_SHT"并安装本库.
2. 首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.


## Methods

```C++

  /**
   * @fn begin
   * @brief 本函数将会尝试与从机设备进行通信,根据返回值判断通信是否成功
   * @return 返回通信结果
   * @retval true  Succeed
   * @retval false Failed
   */
  bool begin(void);

  /**
   * @fn setDeviceAddress
   * @brief  set device address
   * @param  deviceAddr 待修改的设备地址
   * @return  Return setting result
   * @retval true  Succeed
   * @retval false Failed
   */
  bool setDeviceAddress(uint8_t deviceAddr);

  /**
   * @fn setDeviceBaud
   * @brief  set device baud
   * @param baud 待修改的波特率
   * @n     eBaud2400
   * @n     eBaud4800
   * @n     eBaud9600
   * @n     eBaud14400
   * @n     eBaud19200
   * @n     eBaud38400
   * @n     eBaud57600
   * @n     eBaud115200
   * @return  Return setting result
   * @retval true  Succeed
   * @retval false Failed
   */
  bool setDeviceBaud(eSen0538Baud_t baud);

  /**
   * @fn getFirmwareVersion
   * @brief  get firmware version
   * @return  Return  firmware version
   */
  String getFirmwareVersion();

  /**
   * @fn getVid
   * @brief  Get VID
   * @return  Return  VID
   */
  uint16_t getVid();

  /**
   * @fn getPid
   * @brief  Get PID
   * @return  Return  PID
   */
  uint16_t getPid();

  /**
   * @fn getTemperature
   * @brief  Get temperature data 
   * @return  Return  Temperature value, unit:℃ 
   */
  float getTemperature();

  /**
   * @fn getHumidity
   * @brief  Get humidity data
   * @return  Return  Humidity value, unit: %RH
   */
  float getHumidity();

  /**
   * @fn getTemperatureRaw
   * @brief  Obtain the original temperature data collected by the sensor
   * @return  Return  the original temperature data
   */
  uint16_t getTemperatureRaw();

  /**
   * @fn getHumidityRaw
   * @brief  Obtain the original humidity data collected by the sensor
   * @return  Return  the original humidity data
   */
  uint16_t getHumidityRaw();

  /**
   * @fn getENS160Status
   * @brief This API is used to get the sensor operating status
   * @return Operating status:
   * @retval  0: Normal operation; 
   * @retval  1: Warm-Up phase; 
   * @retval  2: Initial Start-Up phase; 
   * @retval  3: Invalid output
   */
  uint8_t getENS160Status(void);

  /**
   * @fn getAQI
   * @brief Get the air quality index calculated on the basis of UBA
   * @return Return value range: 1-5 (Corresponding to five levels of Excellent, Good, Moderate, Poor and Unhealthy respectively)
   */
  uint16_t getAQI(void);

  /**
   * @fn getTVOC
   * @brief Get TVOC concentration
   * @return Return value range: 0–65000, unit: ppb
   */
  uint16_t getTVOC(void);

  /**
   * @fn getECO2
   * @brief Get CO2 equivalent concentration calculated according to the detected data of VOCs and hydrogen (eCO2 – Equivalent CO2)
   * @return Return value range: 400–65000, unit: ppm
   * @note Five levels: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000), 
   * @n                  Poor(1000 - 1500), Unhealthy(> 1500)
   */
  uint16_t getECO2(void);

```


## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |              |       √      |             |


## History

- 2022/07/14 - Version 1.0.0 released.


## Credits

Written by fary(feng.yang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

