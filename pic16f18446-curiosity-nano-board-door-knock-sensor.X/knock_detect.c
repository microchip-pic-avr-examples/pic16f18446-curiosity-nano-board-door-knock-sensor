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

#include "knock_detect.h"
#include "mcc_generated_files/mcc.h"

/* ms of silence to stop listening */
#define LISTEN_WAIT                     (500)

/* amplitude TH to continue listening */
#define KEEP_TH                         (80)

#define SEGMENT_LEN                     (50)
#define HIT_TH                          (70)
#define HIT_LEN                         (4)

#define AMPLITUDE_BUF_LEN               (100)
#define AMPLITUDE_BUF_ZERO_PREFIX_LEN   (2)
#define TH_MAX_DIV_K                    (3)
#define TH_DIV_HALF                     (2)

volatile uint16_t n;
volatile uint8_t max;
volatile uint8_t amplitudeBuf[AMPLITUDE_BUF_LEN];
volatile uint8_t amplitudeBufIndex;
volatile uint16_t sampleIndex;
volatile uint8_t hitBuf[HIT_LEN];

static bool hitDetect(void);
static uint8_t knockCount(uint8_t *buf, uint8_t n);

void KnockDetect_reset(void)
{
    uint8_t i;
    
    n = LISTEN_WAIT;
    sampleIndex = 0;
    max = 0;
    
    for(i=0; i<AMPLITUDE_BUF_ZERO_PREFIX_LEN; i++)
    {
        amplitudeBuf[i] = 0;
    }
    amplitudeBufIndex = i;
    
    for(i=0; i<HIT_LEN; i++)
    {
        hitBuf[i] = 0;
    }
}

/* 0 = normal sample */
/* 1 = 1 knock detected */
/* 2 = 2 knocks detected */
/* ... */
/* 255 = hit detected */

uint8_t KnockDetect_task(uint8_t adcVal)
{
    bool hit = false;
        
    sampleIndex++;
    if(sampleIndex==SEGMENT_LEN) {
        sampleIndex = 0;
        /* store max for completed segment: */
        amplitudeBuf[amplitudeBufIndex++] = max;
        
        for(uint8_t i=0; i<HIT_LEN-1; i++)
        {
            hitBuf[i] = hitBuf[i+1];
        }
        hitBuf[HIT_LEN-1] = max;

        hit = hitDetect();  
        
        /* reset max: */
        max = 0;
    }
    
    if(adcVal > max)
    {
        max = adcVal;
    }
        
    if(adcVal > KEEP_TH)
    {
        n = LISTEN_WAIT;
    }
    
    if(n>0)
    {
        n--;
    }  
    
    if(hit)
    {
        return KNOCK_RESULT_HIT;
    }
    
    if(n==0)
    {
        return knockCount(amplitudeBuf, amplitudeBufIndex);
    }
    
    return 0;
}

static bool hitDetect(void)
{
    for(uint8_t i=0; i<HIT_LEN; i++)
    {
        if(hitBuf[i] < HIT_TH)
        {
            return false;
        }
    }
    return true;
}

static uint8_t knockCount(uint8_t *buf, uint8_t n)
{
    uint8_t res = 0;
    uint8_t maxBuf = 0;
    uint8_t th;
    int16_t d, d2;
    
    /* compute maxBuf: */
    for(uint8_t i=0; i<n; i++)
    {
        if(buf[i] > maxBuf)
        {
            maxBuf = buf[i];   
        }
    }
    
    th = maxBuf/TH_MAX_DIV_K;
    
    n = n-1;
    for(uint8_t i=0; i<n; i++)
    {
        d = buf[i+1];
        d -= buf[i];
        
        /* if half detected */
        if(d > th/TH_DIV_HALF)
        {
            /*if can go further */
            if(i+1 < n)
            {
                d2 = buf[i+2] - buf[i+1];
                /* if goes even upper */
                if(d2 > 0)
                {
                    /*% add it */
                    d = d + d2;
                }
            }
        }
    
        if(d > th)
        {
            res++;
        }
    }
    
    return res;
}
