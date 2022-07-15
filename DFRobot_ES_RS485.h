/*!
 * @file  DFRobot_ES_RS485.h
 * @brief  Define infrastructure of DFRobot_ES_RS485 class
 * @details  该库实现了与SEN0538设备进行通信的所有功能，包括配置设备参数和读取设备数据
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-14
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_ES_RS485
 */
#ifndef __DFROBOT_ES_RS485_H__
#define __DFROBOT_ES_RS485_H__
#include <Arduino.h>
#include "DFRobot_RTU.h"
#define DFRobot_ES_RS485_DEVICE_ADDR   0x32
class DFRobot_ES_RS485:public DFRobot_RTU{
public: 
  /**
   * @enum  eSen0538InputReg_t
   * @brief  设备的输入寄存器地址
   */
  typedef enum{
    eInputRegPidSen0538=0x0000,                 /**< SEN0538 存储PID的输入寄存器的地址 */
    eInputRegVidSen0538,                        /**< SEN0538 存储VID的输入寄存器的地址 */
    eInputRegReserved0Sen0538,                  /**< SEN0538 该寄存器保留 */
    eInputRegReserved1Sen0538,                  /**< SEN0538 该寄存器保留 */
    eInputRegVerifyAndStopSen0538,              /**< SEN0538 存储RS485奇偶检验位与停止位的输入寄存器的地址 */
    eInputRegVersionSen0538,                    /**< SEN0538 存储固件版本的输入寄存器地址 */
    eInputRegEns160StatusSen0538,               /**< SEN0538 存储ENS160内置传感器状态的输入寄存器的地址 */
    eInputRegAQISen0538,                        /**< SEN0538 存储空气质量数据的输入寄存器的地址 */
    eInputRegTVOCSen0538,                       /**< SEN0538 存储TVOC数据的输入寄存器的地址 */
    eInputRegECO2Sen0538,                       /**< SEN0538 存储ECO2数据的输入寄存器的地址 */
    eInputRegTemperatureSen0538,                /**< SEN0538 存储温度数据的输入寄存器的地址 */
    eInputRegHumiditySen0538,                   /**< SEN0538 存储湿度数据的输入寄存器的地址 */
    eInputRegRawTemperatureSen0538,             /**< SEN0538 存储原始温度数据的输入寄存器的地址 */
    eInputRegRawHumiditySen0538,                /**< SEN0538 存储原始湿度数据的输入寄存器的地址 */
  }eSen0538InputReg_t;

  /**
   * @enum  eSen0538HoldingReg_t
   * @brief  设备的保持寄存器地址
   */
  typedef enum{
    eHoldingRegReserved0Sen0538=0x0000,         /**< SEN0538 该寄存器保留 */
    eHoldingRegReserved1Sen0538,                /**< SEN0538 该寄存器保留 */
    eHoldingRegAddrSen0538,                     /**< SEN0538 存储设备地址的保持寄存器的地址 */
    eHoldingRegBaudSen0538,                     /**< SEN0538 存储设备波特率的保持寄存器的地址 */
    eHoldingRegReserved2Sen0538,                /**< SEN0538 该寄存器保留 */
  }eSen0538HoldingReg_t;

  /**
   * @enum  eSen0538Baud_t
   * @brief  设备的波特率
   */
  typedef enum{
    eBaud2400=0x0001,                           /**< 设置SEN0538波特率为2400 */
    eBaud4800,                                  /**< 设置SEN0538波特率为4800 */
    eBaud9600,                                  /**< 设置SEN0538波特率为9600 */
    eBaud14400,                                 /**< 设置SEN0538波特率为14400 */
    eBaud19200,                                 /**< 设置SEN0538波特率为19200 */
    eBaud38400,                                 /**< 设置SEN0538波特率为38400 */
    eBaud57600,                                 /**< 设置SEN0538波特率为57600 */
    eBaud115200,                                /**< 设置SEN0538波特率为115200 */
  }eSen0538Baud_t;
  /**
   * @fn DFRobot_ES_RS485
   * @brief DFRobot_ES_RS485 constructor
   * @param addr: The device address of the communication between the host computer and DFRobot_ES_RS485 slave device
   * @n     DFRobot_ES_RS485_DEVICE_ADDR or 50(0X32): Default address of DFRobot_ES_RS485 device, if users do not change the device address, it's default to 50.
   * @param s   : The serial port pointer to the Stream, which requires calling begin in the demo to init communication serial port config of Arduino main controller, in line with that of DFRobot_ES_RS485 device slave.
   * @n DFRobot_ES_RS485 serial port config: 9600 baud rate, 8-bit data bit, no check bit, 1 stop bit, parameters other than baud rate cannot be changed.
   */
  DFRobot_ES_RS485(Stream *s,uint8_t addr=DFRobot_ES_RS485_DEVICE_ADDR, int dePin=-1);
  ~DFRobot_ES_RS485(){};

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
private:
  Stream    *_s = NULL;
  int    _dePin;
  uint8_t   _addr;
};
#endif