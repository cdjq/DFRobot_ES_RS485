# -*- coding: utf-8 -*
'''!
  @file       DFRobot_ES_RS485.py
  @brief       这是SEN0538设备基库
  @copyright   Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      fary(feng.yang@dfrobot.com)
  @version     V1.0
  @date        2022-07-14
  @url         https://github.com/DFRobor/DFRobot_ES_RS485
'''

import serial
import os

import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu

## SEN0538的默认设备地址。
SEN0538_DEVICE_ADDR               = 0x0032
## SEN0538 存储PID的输入寄存器的地址。
SEN0538_INPUT_REG_PID             = 0x0000
## SEN0538 存储VID的输入寄存器的地址。
SEN0538_INPUT_REG_VID             = 0x0001
## SEN0538 存储RS485奇偶检验位与停止位的输入寄存器的地址。
SEN0538_INPUT_REG_VERIFYANDSTOP   = 0x0004
## SEN0538 存储固件版本的输入寄存器地址。
SEN0538_INPUT_REG_VERSION         = 0x0005
## SEN0538 存储ENS160内置传感器状态的输入寄存器的地址。
SEN0538_INPUT_REG_ENS160STATUS    = 0x0006
## SEN0538 存储空气质量数据的输入寄存器的地址。
SEN0538_INPUT_REG_AQI             = 0x0007
## SEN0538 存储TVOC数据的输入寄存器的地址。
SEN0538_INPUT_REG_TVOC            = 0x0008
## SEN0538 存储ECO2数据的输入寄存器的地址。
SEN0538_INPUT_REG_ECO2            = 0x0009
## SEN0538 存储温度数据的输入寄存器的地址。
SEN0538_INPUT_REG_TEMPERATURE     = 0x000A
## SEN0538 存储湿度数据的输入寄存器的地址。
SEN0538_INPUT_REG_HUMIDITY        = 0x000B 
## SEN0538 存储原始温度数据的输入寄存器的地址。
SEN0538_INPUT_REG_RAW_TEMPERATURE = 0x000C
## SEN0538 存储原始湿度数据的输入寄存器的地址。
SEN0538_INPUT_REG_RAW_HUMIDITY    = 0x000D

## SEN0538 存储设备地址的保持寄存器的地址。
SEN0538_HOLDING_REG_ADDR          = 0x0002
## SEN0538 存储设备波特率的保持寄存器的地址。
SEN0538_HOLDING_REG_BAUD          = 0x0003

## 设置SEN0538波特率为2400  
SEN0538_BAUD_2400                 = 0x0001
## 设置SEN0538波特率为4800
SEN0538_BAUD_4800                 = 0x0002
## 设置SEN0538波特率为9600
SEN0538_BAUD_9600                 = 0x0003
## 设置SEN0538波特率为14400
SEN0538_BAUD_14400                = 0x0004
## 设置SEN0538波特率为19200
SEN0538_BAUD_19200                = 0x0005
## 设置SEN0538波特率为38400
SEN0538_BAUD_38400                = 0x0006
## 设置SEN0538波特率为57600
SEN0538_BAUD_57600                = 0x0007
## 设置SEN0538波特率为115200
SEN0538_BAUD_115200               = 0x0008

class DFRobot_ES_RS485():
  '''!
    @brief Define DFRobot_ES_RS485 basic class
    @details Drive the sensor
  '''
  def __init__(self,baud = 9600, addr=SEN0538_DEVICE_ADDR):
    '''!
      @brief 初始化串口
    '''
    self._baud = baud
    self._addr = addr
    self.master = modbus_rtu.RtuMaster(serial.Serial(port="/dev/ttyAMA0",baudrate=baud, bytesize=8, parity='N', stopbits=1))
    self.master.set_timeout(1.0)

  def begin(self):
    '''!
      @brief 与设备进行简单的通信，确保设备在线
      @return 返回通信结果
      @retval True 设备在线并且通信成功
      @retval False 设备不在线，通信失败
    '''
    ret=False
    if self._addr!=0 and self._addr<0xF7:
      print(self.get_vid())
      if self.get_pid()==0x21A:
        ret=True
    return ret

  def set_device_address(self,device_addr):
    '''!
      @brief 修改设备通信地址
      @param device_addr 待修改的设备地址
      @return 返回修改结果
      @retval True 修改成功
      @retval False 修改失败
    '''
    ret=False
    list=[device_addr]
    if device_addr!=0 and device_addr<0xF7:
      ret=self._write_holding_register(SEN0538_HOLDING_REG_ADDR,list)
    return ret

  def set_device_baud(self,baud):
    '''!
      @brief 修改设备通信波特率
      @param baud 待修改的设备通信波特率
      @return 返回修改结果
      @retval True 修改成功
      @retval False 修改失败
    '''
    ret=False
    list = [baud]
    if baud>=SEN0538_BAUD_2400 and baud<=SEN0538_BAUD_115200:
      ret=self._write_holding_register(SEN0538_HOLDING_REG_BAUD,list)
    return ret

  def get_firmware_version(self):
    '''!
      @brief  get firmware version
      @return  Return  firmware version
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_VERSION,1)
    version =data[0]
    return str(version>>12)+'.'+str(((version>>8)&0x0F))+'.'+str(((version>>4)&0x0F))+'.'+str((version&0x0F)) 

  def get_vid(self):
    '''!
      @brief  Get VID
      @return  Return  VID
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_VID,1)
    return data[0]

  def get_pid(self):
    '''!
      @brief  Get PID
      @return  Return  PID
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_PID,1)
    return data[0]

  def get_temperature(self):
    '''!
      @brief  Get temperature data 
      @return  Return  Temperature value, unit:℃ 
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_TEMPERATURE,1)
    return data[0]/100.0

  def get_humidity(self):
    '''!
      @brief  Get humidity data
      @return  Return  Humidity value, unit: %RH
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_HUMIDITY,1)
    return data[0]/100.0

  def get_temperature_raw(self):
    '''!
      @brief  Obtain the original temperature data collected by the sensor
      @return  Return  the original temperature data
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_RAW_TEMPERATURE,1)
    return data[0]

  def get_humidity_raw(self):
    '''!
      @brief  Obtain the original humidity data collected by the sensor
      @return  Return  the original humidity data
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_RAW_HUMIDITY,1)
    return data[0]

  def get_ens160_status(self):
    '''!
      @brief This API is used to get the sensor operating status
      @return Operating status:
      @retval  0: Normal operation; 
      @retval  1: Warm-Up phase; 
      @retval  2: Initial Start-Up phase; 
      @retval  3: Invalid output
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_ENS160STATUS,1)
    return data[0]

  def get_AQI(self):
    '''!
      @brief Get the air quality index calculated on the basis of UBA
      @return Return value range: 1-5 (Corresponding to five levels of Excellent, Good, Moderate, Poor and Unhealthy respectively)
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_AQI,1)
    return data[0]

  def get_TVOC(self):
    '''!
      @brief Get TVOC concentration
      @return Return value range: 0-65000, unit: ppb
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_TVOC,1)
    return data[0]

  def get_ECO2(self):
    '''!
      @brief Get CO2 equivalent concentration calculated according to the detected data of
      @return Return value range: 400-65000, unit: ppm
      @note Five levels: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000), 
      @n                  Poor(1000 - 1500), Unhealthy(> 1500)
    '''
    data=self._read_input_register(SEN0538_INPUT_REG_ECO2,1)
    return data[0]

  def _read_input_register(self, reg_addr ,length):
    '''!
      @brief 读取设备输入寄存器
      @param reg_addr 输入寄存器地址
      @param length 读取数据长度
      @return 读取的数据
    '''
    return list(self.master.execute(self._addr, cst.READ_INPUT_REGISTERS, reg_addr, length))
  
  def _write_holding_register(self, reg_addr ,data):
    '''!
      @brief 向设备保持寄存器写入数据
      @param reg_addr 保持寄存器地址
      @param data 数据
      @return 写入结果
      @retval True 写入成功
      @retval False 写入失败
    '''
    ret=True
    list_write=list(self.master.execute(self._addr, cst.WRITE_MULTIPLE_REGISTERS, reg_addr, output_value=data))
    if list_write[1]!=len(data):
      ret=False
    return ret

  def _read_holding_register(self,reg_addr,length):
    '''!
      @brief 读取设备保持寄存器
      @param reg_addr 保持寄存器地址
      @param length 读取数据长度
      @return 读取的数据
    '''
    return list(self.master.execute(self._addr, cst.READ_HOLDING_REGISTERS, reg_addr, length))