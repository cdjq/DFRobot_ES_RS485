/*!
 * @file DFRobot_ES_RS485.cpp
 * @brief  Define the infrastructure DFRobot_ES_RS485 class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2022-07-14
 * @url  https://github.com/DFRobot/DFRobot_ES_RS485
 */
#include "DFRobot_ES_RS485.h"

DFRobot_ES_RS485::DFRobot_ES_RS485( Stream *s,uint8_t addr,int dePin):DFRobot_RTU(s,dePin)
{
    _s = s;
    _dePin=dePin;
    _addr = addr;
}

bool DFRobot_ES_RS485::begin(void)
{
  bool ret=false;
  if(_addr != 0 &&_addr<0xF7){
    if(getPid()==0x21A){
      ret =true;
    }
  }
  return ret;
}

bool DFRobot_ES_RS485::setDeviceAddress(uint8_t deviceAddr)
{
  bool ret=false;
  if(deviceAddr != 0 && deviceAddr<0xF7){
    if(writeHoldingRegister(_addr, eHoldingRegAddrSen0538, deviceAddr)==0){
      ret =true;
    }
  }
  return ret;
}

bool DFRobot_ES_RS485::setDeviceBaud(DFRobot_ES_RS485::eSen0538Baud_t baud)
{
  bool ret=false;
  if(writeHoldingRegister(_addr, eHoldingRegBaudSen0538, baud)==0){
    ret =true;
  }
  return ret;
}

String DFRobot_ES_RS485::getFirmwareVersion()
{
  uint16_t version =readInputRegister(_addr, eInputRegVersionSen0538);
  return String(version>>12)+'.'+String(((version>>8)&0x0F))+'.'+String(((version>>4)&0x0F))+'.'+String((version&0x0F));
}

uint16_t DFRobot_ES_RS485::getVid()
{
  uint16_t vid =readInputRegister(_addr, eInputRegVidSen0538);
  return vid;
}

uint16_t DFRobot_ES_RS485::getPid()
{
  uint16_t vid =readInputRegister(_addr, eInputRegPidSen0538);
  return vid;
}

float DFRobot_ES_RS485::getTemperature()
{
  uint16_t temp =readInputRegister(_addr, eInputRegTemperatureSen0538);
  return temp/100.0;
}

float DFRobot_ES_RS485::getHumidity()
{
  uint16_t hum =readInputRegister(_addr, eInputRegHumiditySen0538);
  return hum/100.0;
}

uint16_t DFRobot_ES_RS485::getTemperatureRaw()
{
  return readInputRegister(_addr, eInputRegRawTemperatureSen0538);
}

uint16_t DFRobot_ES_RS485::getHumidityRaw()
{
  return readInputRegister(_addr, eInputRegRawHumiditySen0538);
}

uint8_t DFRobot_ES_RS485::getENS160Status(void)
{
  return readInputRegister(_addr, eInputRegEns160StatusSen0538);
}

uint16_t DFRobot_ES_RS485::getAQI(void)
{
  return readInputRegister(_addr, eInputRegAQISen0538);
}

uint16_t DFRobot_ES_RS485::getTVOC(void)
{
  return readInputRegister(_addr, eInputRegTVOCSen0538);
}

uint16_t DFRobot_ES_RS485::getECO2(void)
{
  return readInputRegister(_addr, eInputRegECO2Sen0538);
}