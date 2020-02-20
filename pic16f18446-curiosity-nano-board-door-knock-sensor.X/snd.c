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

#include "snd.h"
#include "mcc_generated_files/mcc.h"

#define DELAY_AFTER_SND     (200)
#define SND_DING_HALF_PER   (645)
#define SND_DONG_HALF_PER   (806)
#define SND_LEN_SHORT       (300)
#define SND_LEN_LONG        (1000)

#define SND_ALARM_LEN1      (38)
#define SND_ALARM_LEN2      (58)
#define SND_ALARM_LEN3      (92)
#define SND_ALARM_CNT       (10)

#define SND_ALARM_HALF_PER1 (219)
#define SND_ALARM_HALF_PER2 (146)
#define SND_ALARM_HALF_PER3 (90)

#define SND_ALARM_DELAY     (200)

#define SND_BEEP_LEN        (250)
#define SND_BEEP_HALF_PER   (100)
#define SND_BEEP_DELAY      (100)

static void SND_alarm(void);

void SND_dingDong(uint8_t knocks)
{
    SNDP_PIN_Toggle();
    while(knocks>1)
    {
        for(uint16_t i=0; i<SND_LEN_SHORT; i++)
        {
            SNDP_PIN_Toggle();
            SNDN_PIN_Toggle();
            __delay_us(SND_DING_HALF_PER);
        }
        for(uint16_t i=0; i<SND_LEN_SHORT; i++)
        {
            SNDP_PIN_Toggle();
            SNDN_PIN_Toggle();
            __delay_us(SND_DONG_HALF_PER);
        }
        knocks--;
    }
    
    for(uint16_t i=0; i<SND_LEN_SHORT; i++)
    {
        SNDP_PIN_Toggle();
        SNDN_PIN_Toggle();
        __delay_us(SND_DING_HALF_PER);
    }
    for(uint16_t i=0; i<SND_LEN_LONG; i++)
    {
        SNDP_PIN_Toggle();
        SNDN_PIN_Toggle();
        __delay_us(SND_DONG_HALF_PER);
    }
    
    SNDP_PIN_SetLow();
    SNDN_PIN_SetLow();
    
    __delay_ms(DELAY_AFTER_SND);
}

static void SND_alarm(void)
{
    SNDP_PIN_Toggle();
    for(uint8_t j=0; j<SND_ALARM_CNT; j++)
    {
        for(uint16_t i=0; i<SND_ALARM_LEN1; i++)
        {
            SNDP_PIN_Toggle();
            SNDN_PIN_Toggle();
            __delay_us(SND_ALARM_HALF_PER1);
        }

        for(uint16_t i=0; i<SND_ALARM_LEN2; i++)
        {
            SNDP_PIN_Toggle();
            SNDN_PIN_Toggle();
            __delay_us(SND_ALARM_HALF_PER2);
        }

        for(uint16_t i=0; i<SND_ALARM_LEN3; i++)
        {
            SNDP_PIN_Toggle();
            SNDN_PIN_Toggle();
            __delay_us(SND_ALARM_HALF_PER3);
        }
    }
    
    SNDP_PIN_SetLow();
    SNDN_PIN_SetLow();
}

void SND_alarmX4(void)
{
    for(uint8_t i=0; i<4; i++)
    {
        SND_alarm();
        __delay_ms(SND_ALARM_DELAY);
    }
    
    __delay_ms(DELAY_AFTER_SND);
}

void SND_beep(void)
{
    SNDP_PIN_Toggle();
    for(uint8_t i=0; i<SND_BEEP_LEN; i++)
    {
        SNDP_PIN_Toggle();
        SNDN_PIN_Toggle();
        __delay_us(SND_BEEP_HALF_PER);
    }
    SNDP_PIN_SetLow();
    SNDN_PIN_SetLow();
}

void SND_init(void)
{
    SND_beep();
    __delay_ms(SND_BEEP_DELAY);
    SND_beep();  
}
