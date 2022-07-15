DFRobot_ES_RS485
===========================

- [中文版](./README_CN.md)

本库提供了获取SEN0538采集数据的全部方法，用户只需要简单的使用本库就可以获取到SEN0538采集的数据。

![产品效果图](../resources/images/SEN0538.png)

## Product Link (https://www.dfrobot.com)

    SKU：SEN0538

## Table of Contents

  * [summary](#summary)
  * [installation](#installation)
  * [methods](#methods)
  * [compatibility](#compatibility)
  * [history](#history)
  * [credits](#credits)

## Summary
* 读取温湿度
* 读取空气质量
* 读取ECO2数据
* 读取TVOC数据

## Installation

要使用库, 首先下载库文件, 将其粘贴到指定的目录中, 然后打开examples文件夹并在该文件夹中运行演示。
本库关联了modbus_tk库，使用前请确保树莓派已经下载了modbus_tk。

## Methods

```python
  def begin(self):
    '''!
      @brief 与设备进行简单的通信，确保设备在线
      @return 返回通信结果
      @retval True 设备在线并且通信成功
      @retval False 设备不在线，通信失败
    '''

  def set_device_address(self,device_addr):
    '''!
      @brief 修改设备通信地址
      @param device_addr 待修改的设备地址
      @return 返回修改结果
      @retval True 修改成功
      @retval False 修改失败
    '''

  def set_device_baud(self,baud):
    '''!
      @brief 修改设备通信波特率
      @param baud 待修改的设备通信波特率
      @return 返回修改结果
      @retval True 修改成功
      @retval False 修改失败
    '''

  def get_firmware_version(self):
    '''!
      @brief  get firmware version
      @return  Return  firmware version
    '''

  def get_vid(self):
    '''!
      @brief  Get VID
      @return  Return  VID
    '''

  def get_pid(self):
    '''!
      @brief  Get PID
      @return  Return  PID
    '''

  def get_temperature(self):
    '''!
      @brief  Get temperature data 
      @return  Return  Temperature value, unit:℃ 
    '''

  def get_humidity(self):
    '''!
      @brief  Get humidity data
      @return  Return  Humidity value, unit: %RH
    '''

  def get_temperature_raw(self):
    '''!
      @brief  Obtain the original temperature data collected by the sensor
      @return  Return  the original temperature data
    '''

  def get_humidity_raw(self):
    '''!
      @brief  Obtain the original humidity data collected by the sensor
      @return  Return  the original humidity data
    '''

  def get_ens160_status(self):
    '''!
      @brief This API is used to get the sensor operating status
      @return Operating status:
      @retval  0: Normal operation; 
      @retval  1: Warm-Up phase; 
      @retval  2: Initial Start-Up phase; 
      @retval  3: Invalid output
    '''

  def get_AQI(self):
    '''!
      @brief Get the air quality index calculated on the basis of UBA
      @return Return value range: 1-5 (Corresponding to five levels of Excellent, Good, Moderate, Poor and Unhealthy respectively)
    '''

  def get_TVOC(self):
    '''!
      @brief Get TVOC concentration
      @return Return value range: 0–65000, unit: ppb
    '''

  def get_ECO2(self):
    '''!
      @brief Get CO2 equivalent concentration calculated according to the detected data of
      @return Return value range: 400–65000, unit: ppm
      @note Five levels: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000), 
      @n                  Poor(1000 - 1500), Unhealthy(> 1500)
    '''

  def _read_input_register(self, reg_addr ,length):
    '''!
      @brief 读取设备输入寄存器
      @param reg_addr 输入寄存器地址
      @param length 读取数据长度
      @return 读取的数据
    '''

  def _write_holding_register(self, reg_addr ,data):
    '''!
      @brief 向设备保持寄存器写入数据
      @param reg_addr 保持寄存器地址
      @param data 数据
      @return 写入结果
      @retval True 写入成功
      @retval False 写入失败
    '''

  def _read_holding_register(self,reg_addr,length):
    '''!
      @brief 读取设备保持寄存器
      @param reg_addr 保持寄存器地址
      @param length 读取数据长度
      @return 读取的数据
    '''
```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| Raspberry Pi2 |           |            |    √     |         |
| Raspberry Pi3 |           |            |    √     |         |
| Raspberry Pi4 |       √   |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |

## History

- 2021/07/14 - Version 1.0.0 released.

## Credits

Written by fary(feng.yang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))
