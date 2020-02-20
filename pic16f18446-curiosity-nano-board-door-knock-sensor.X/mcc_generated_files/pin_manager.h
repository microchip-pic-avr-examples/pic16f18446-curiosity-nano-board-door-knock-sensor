/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SNDN_PIN aliases
#define SNDN_PIN_TRIS                 TRISAbits.TRISA4
#define SNDN_PIN_LAT                  LATAbits.LATA4
#define SNDN_PIN_PORT                 PORTAbits.RA4
#define SNDN_PIN_WPU                  WPUAbits.WPUA4
#define SNDN_PIN_OD                   ODCONAbits.ODCA4
#define SNDN_PIN_ANS                  ANSELAbits.ANSA4
#define SNDN_PIN_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SNDN_PIN_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SNDN_PIN_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SNDN_PIN_GetValue()           PORTAbits.RA4
#define SNDN_PIN_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SNDN_PIN_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SNDN_PIN_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define SNDN_PIN_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define SNDN_PIN_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define SNDN_PIN_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define SNDN_PIN_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SNDN_PIN_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set PIEZO_PIN aliases
#define PIEZO_PIN_TRIS                 TRISCbits.TRISC1
#define PIEZO_PIN_LAT                  LATCbits.LATC1
#define PIEZO_PIN_PORT                 PORTCbits.RC1
#define PIEZO_PIN_WPU                  WPUCbits.WPUC1
#define PIEZO_PIN_OD                   ODCONCbits.ODCC1
#define PIEZO_PIN_ANS                  ANSELCbits.ANSC1
#define PIEZO_PIN_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define PIEZO_PIN_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define PIEZO_PIN_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define PIEZO_PIN_GetValue()           PORTCbits.RC1
#define PIEZO_PIN_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define PIEZO_PIN_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define PIEZO_PIN_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define PIEZO_PIN_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define PIEZO_PIN_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define PIEZO_PIN_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define PIEZO_PIN_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define PIEZO_PIN_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SNDP_PIN aliases
#define SNDP_PIN_TRIS                 TRISCbits.TRISC3
#define SNDP_PIN_LAT                  LATCbits.LATC3
#define SNDP_PIN_PORT                 PORTCbits.RC3
#define SNDP_PIN_WPU                  WPUCbits.WPUC3
#define SNDP_PIN_OD                   ODCONCbits.ODCC3
#define SNDP_PIN_ANS                  ANSELCbits.ANSC3
#define SNDP_PIN_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SNDP_PIN_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SNDP_PIN_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SNDP_PIN_GetValue()           PORTCbits.RC3
#define SNDP_PIN_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SNDP_PIN_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SNDP_PIN_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SNDP_PIN_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SNDP_PIN_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SNDP_PIN_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SNDP_PIN_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SNDP_PIN_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/