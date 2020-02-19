/*
 * file APD9151.cpp
 *
 * author(s) Joe Carmon (joe@carmonfamily.com)
 * copyright: GPL V3
 * version  V0.0.1
 * date  02/16/2020
 */
 
 #include <Arduino.h>
 #include <Wire.h>
 
 #include "apds9151.h"
 

APDS9151::APDS9151()
{

}
 

APDS9151::~APDS9151()
{

}


bool APDS9151::init()
{
    uint8_t id;

    ///< Initialize I2C 
    //Check ID of Sensor   
    id= ReadRegistryValue(APDS9151_ID);
  
    //< Read ID register and check against known values for APDS-9151 
    if( id != APDS9151_ID_1 ) {
        return false;
    }

    //Check chip status registry
    id= ReadRegistryValue(APDS9151_STATUS);
    if( id != STATUS ) 
    {
       return false;
    }
   
    //Check main control registry for default values
//    id = ReadRegistryValue(APDS9151_MAIN_CTL);

//    if( id != MAIN_CTL) 
//    {
//       return false;
//    }

    SetControlRegistry(0x07);

    return true;

}

void APDS9151::SetControlRegistry(uint8_t iVal)
{

  Wire.beginTransmission(APDS9151__ADDR);
  Wire.write(APDS9151_MAIN_CTL);
  Wire.write(iVal);
  Wire.endTransmission();


}

void APDS9151::ReadCMYKVlaues( uint8_t &Cyan, uint8_t &Magenta, uint8_t &Yellow, uint8_t &Black)
{

    //Reg Register
    uint8_t iRed2 = ReadRegistryValue(0x14);

    //Green Registry
    uint8_t iGreen1 = ReadRegistryValue(0x0D);
    uint8_t iGreen2 = ReadRegistryValue(0x0E);
    uint8_t iGreen3 = ReadRegistryValue(0x0F);

     //Blue Registry
     uint8_t iBlue1 = ReadRegistryValue(0x10);
     uint8_t iBlue2 = ReadRegistryValue(0x11);
     uint8_t iBlue3 = ReadRegistryValue(0x12);
     
     double dRedPrime = iRed2/255;
     double dBluePrime = iBlue2/255;
     double dGreenPrime = iGreen2/255;

     double dHighest = max(dRedPrime,dBluePrime);
     double dHighest = max(dHighest,dGreenPrime);

     Black   = 1-dHighest;
     Cyan    = (1-(dRedPrime)-Black)/(1-Black);
     Magenta = (1-(dGreenPrime)-Black);
     Yellow  = (1-(dBluePrime)-Black)/(1-Black);


{

void APDS9151::ReadRGBValues(uint8_t &iRed, uint8_t &iGreen, uint8_t &iBlue)
{
  //Red Register
  uint8_t iRed1 = ReadRegistryValue(0x13);
  uint8_t iRed2 = ReadRegistryValue(0x14);
  uint8_t iRed3 = ReadRegistryValue(0x15);

  //Green Registry
  uint8_t iGreen1 = ReadRegistryValue(0x0D);
  uint8_t iGreen2 = ReadRegistryValue(0x0E);
  uint8_t iGreen3 = ReadRegistryValue(0x0F);


  //Blue Registry
  uint8_t iBlue1 = ReadRegistryValue(0x10);
  uint8_t iBlue2 = ReadRegistryValue(0x11);
  uint8_t iBlue3 = ReadRegistryValue(0x12);

  iRed = iRed2;
  iGreen = iGreen2;
  iBlue = iBlue2;


}

uint8_t APDS9151::ReadRegistryValue(uint8_t iReg, int iLen)
{

    uint8_t id;

    Wire.beginTransmission(APDS9151__ADDR);
    Wire.write(iReg);
    Wire.endTransmission();
    Wire.requestFrom(APDS9151__ADDR,iLen);

    while (Wire.available())
    {
       id = Wire.read();
    }

    return id;

}


uint8_t APDS9151::ReadRegistryValue(uint8_t iReg)
{
 
    uint8_t id;
   
    Wire.beginTransmission(APDS9151__ADDR);
    Wire.write(iReg);
    Wire.endTransmission();
    Wire.requestFrom(APDS9151__ADDR,1);
    
    while (Wire.available())
    {
       id = Wire.read();
    }

    return id;
   
}

