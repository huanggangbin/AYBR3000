/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "A7105_driver.h"
CY_ISR_PROTO(time_1ms_Interrupt);
uint8 t = 0;
uint8 send_buffer[16]; 
uint16 timer_count = 0;
//#define TOUCH_TUNE_SWITCH
int main(void)
{
    static volatile uint8 temp = 0;
    CyGlobalIntEnable; /* Enable global interrupts. */
    A7105_init();
    //GIO1_Write(1);
#ifdef TOUCH_TUNE_SWITCH 
    
    EZI2C_Start(); /* Start EZI2C Component */
    /*
    * Set up communication and initialize data buffer to CapSense data structure
    * to use Tuner application
    */
    EZI2C_EzI2CSetBuffer1(sizeof(key_touch_dsRam), sizeof(key_touch_dsRam),(uint8 *)&key_touch_dsRam);

#endif
    //Timer_1_Start();
    //time_1ms_ISR_StartEx(time_1ms_Interrupt);
    key_touch_Start(); /* Initialize Component */
    key_touch_ScanAllWidgets(); /* Scan all widgets */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Do this only when a scan is done */
        
        if(key_touch_NOT_BUSY == key_touch_IsBusy()) /*判断触控按键扫描是否完成*/
        {
            key_touch_ProcessAllWidgets(); /* Process all widgets */
            
#ifdef TOUCH_TUNE_SWITCH             
            key_touch_RunTuner(); /* To sync with Tuner application */
#endif
            if (key_touch_IsWidgetActive(key_touch_BUTTON0_WDGT_ID))
                t = 1+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON1_WDGT_ID))
                t = 2+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON2_WDGT_ID))
                t = 3+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON3_WDGT_ID))
                t = 4+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON4_WDGT_ID))
                t = 5+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON5_WDGT_ID))
                t = 6+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON6_WDGT_ID))
                t = 7+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON7_WDGT_ID))
                t = 8+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON8_WDGT_ID))
                t = 9+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON9_WDGT_ID))
                t = 10+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON10_WDGT_ID))
                t = 11+0x10;
            if (key_touch_IsWidgetActive(key_touch_BUTTON11_WDGT_ID))
                t = 12+0x10;
            if (t > 0x10)
            {
                temp = !temp;
                t = temp;
            }
            key_touch_ScanAllWidgets(); /* Start next scan */
        }
        //if (!(timer_count % 100))
            //StrobeCmd(CMD_RX);
            //send_data_by_A7105(16, send_buffer);
        /* Place your application code here. */
    }
}
CY_ISR(time_1ms_Interrupt)
{
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
    //SCS_Write(t);
    timer_count++;
}
//*[] END OF FILE */  

