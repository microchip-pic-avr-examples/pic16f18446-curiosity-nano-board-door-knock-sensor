/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC16F18446
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdbool.h>
#include "snd.h"
#include "knock_detect.h"

#define DELAY_AFTER_SND_INIT    (1000)
#define ADACC_SHIFT_DIV32       (5)

void APP_task(void) /* every 1ms */
{
    uint8_t knockResult;
    knockResult = KnockDetect_task(ADACC >> ADACC_SHIFT_DIV32);
    
    if(knockResult != KNOCK_RESULT_NOTHING)
    {
        TMR1_StopTimer();
        KnockDetect_reset();
        
        if(knockResult == KNOCK_RESULT_HIT)
        {
            SND_alarmX4();
        }
        else
        {
            SND_dingDong(knockResult);
        }
        
        PIR1bits.ADTIF = 0;
        PIE1bits.ADTIE = 1;
        SLEEP();
    }
    
    PIR4bits.TMR1IF = 0;
}

void APP_startTaskTimer(void)
{
    TMR1_StartTimer();
    
    /* disable interrupt */
    /* will be enabled back after sound output */
    PIE1bits.ADTIE = 0;
}

void APP_init(void)
{
    SND_init();
    __delay_ms(DELAY_AFTER_SND_INIT);
    
    KnockDetect_reset();
    
    ADCC_SetADTIInterruptHandler(APP_startTaskTimer);
    TMR1_SetInterruptHandler(APP_task);
    
    ADCC_StartConversion(PIEZO_PIN);
    
    SLEEP();
}

void main(void)
{
    /* initialize the device */
    SYSTEM_Initialize();

    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    APP_init();
    
    while (1)
    {
        ;
    }
}