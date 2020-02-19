/*
 * file APD9151.h
 *
 * author(s) Joe Carmon (joe@carmonfamily.com)
 * copyright: GPL V3
 * version  V0.0.1
 * date  02/16/2020
 */
 
#ifndef apds9151_H
#define apds9151_H

#include <Arduino.h>

//< Debug 
#define DEBUG                     0

//< APDS-9151 I2C address 
#define APDS9151__ADDR            0x52

//< Acceptable device IDs 
#define APDS9151_ID_1             0xC2

//Chip Defaults
#define STATUS                    32
#define MAIN_CTL                  0
#define PS_LED                    54

///< APDS-9151 register addresses
#define APDS9151_MAIN_CTL         0x00
#define APDS9151_PS_LED           0x01
#define APDS9151_ID               0x06
#define APDS9151_STATUS           0x07

///< On/Off definitions 
#define OFF                     0
#define ON                      1

///< LED Drive values 
#define LED_DRIVE_100MA         0
#define LED_DRIVE_50MA          1
#define LED_DRIVE_25MA          2
#define LED_DRIVE_12_5MA        3


//< APDS9151 Class 
class APDS9151 {
public:

    APDS9151();
	
    ~APDS9151();
    bool init();
    
    uint8_t ReadRegistryValue(uint8_t iReg);
    uint8_t ReadRegistryValue(uint8_t iReg, int iLen);

    //Set Functions	
    void SetControlRegistry(uint8_t iVal);

    //Read Functions
    void ReadRGBValues(uint8_t &iRed, uint8_t &iGreen, uint8_t &iBlue);
    void ReadCMYKValues(uint8_t &Cyan, uint8_t &Magenta, uint8_t &Yellow, uint8_t &Black);

};

#endif
