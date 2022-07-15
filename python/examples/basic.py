# -*- coding: utf-8 -*
'''!
  @file  basic.py
  @brief 本示例介绍了DFRobot_ES_RS485库的所有用法
  @copyright   Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      [fary](feng.yang@dfrobot.com)
  @version     V1.0
  @date        2022-07-14
  @url         https://github.com/DFRobor/DFRobot_LTR390UV
'''
from __future__ import print_function
import sys
import os
sys.path.append("../")
import time
import RPi.GPIO as GPIO

from DFRobot_ES_RS485 import *


ADDRESS = 0x32
sensor=DFRobot_ES_RS485(baud = 9600, addr=ADDRESS)


def setup():
  while (sensor.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  print("Sensor  initialize success!!")

  print("Version: "+ sensor.get_firmware_version())#获取环境光和紫外线原始数据
  print("vid: %d"%(sensor.get_vid()))
  print("pid: %d"%(sensor.get_pid()))

  #修改设备通信地址范围（0x01~0xF7），设备掉电生效
  #sensor.set_device_address(0x33)

  '''!
    修改设备波特率，设备掉电生效。可选参数有：
    设置SEN0538波特率为2400    SEN0538_BAUD_2400
    设置SEN0538波特率为4800    SEN0538_BAUD_4800 
    设置SEN0538波特率为9600    SEN0538_BAUD_9600
    设置SEN0538波特率为14400   SEN0538_BAUD_14400
    设置SEN0538波特率为19200   SEN0538_BAUD_19200
    设置SEN0538波特率为38400   SEN0538_BAUD_38400
    设置SEN0538波特率为57600   SEN0538_BAUD_57600
    设置SEN0538波特率为115200  SEN0538_BAUD_115200 
  '''
  #sensor.set_device_baud(SEN0538_BAUD_115200)
  
def loop():

  temperature=sensor.get_temperature()
  humidity=sensor.get_humidity()

  #上面获取的温湿度经过内部计算，如果你需要更高的精度，请采用获取原始数据的方式
  # temperature = -45 + 175*((sensor.get_temperature_raw())/65536.0)
  # humidity =  ((sensor.get_humidity_raw()) * 100.0) / 65536.0

  '''!
    This API is used to get the sensor operating status
    Operating status:
      0: Normal operation; 
      1: Warm-Up phase; 
      2: Initial Start-Up phase; 
      3: Invalid output
  '''
  status=sensor.get_ens160_status()

  '''!
    Get the air quality index calculated on the basis of UBA
    Return value range: 1-5 (Corresponding to five levels of Excellent, Good, Moderate, Poor and Unhealthy respectively)
  '''
  AQI=sensor.get_AQI()

  '''!
    Get TVOC concentration
    Return value range: 0~65000, unit: ppb
  '''
  TVOC=sensor.get_TVOC()

  '''!
    Get CO2 equivalent concentration calculated according to the detected data of VOCs and hydrogen (eCO2-Equivalent CO2)
    Return value range: 400~65000, unit: ppm
    Five levels: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000),Poor(1000 - 1500), Unhealthy(> 1500)
  '''
  ECO2=sensor.get_ECO2()

  print("temperature: %f C"%(temperature))
  print("humidity: %f"%(humidity)+" %RH")
  print("status: %d"%(status))
  print("AQI: %d"%(AQI))
  print("TVOC: %d ppb"%(TVOC))
  print("ECO2: %d ppm"%(ECO2))
  time.sleep(1)

if __name__ == "__main__":
  setup()
  while True:
    loop()