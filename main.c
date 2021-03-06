/*!
    \file    main.c
    \brief   GPIO Running LED demo

    \version 2022-03-06, V1.0.0, demo for GD32F3x0
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f3x0.h"
#include "gd32f310g_start.h"
#include "systick.h"
#include "nokia_5110.h"

void gd_led_config(void);
void gd_led_toggle(void);
void adc_init(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    gd_led_config();
    systick_config();

    LCD_init();

    //LCD_write_english_string(0, 10, "GD32F310G");
    //LCD_write_english_string(0, 20, "START");
    adc_init();

    while (1)
    {
        /* insert 500 ms delay */
        delay_1ms(500);

        /* toggle the LED */
        gd_led_toggle();

        /* insert 500 ms delay */
        delay_1ms(500);
        
    }
}

void adc_init(void)
{
    /*------------------????????????------------------*/
    // GPIO????????????
    rcu_periph_clock_enable(RCU_GPIOB);
    // ADC????????????
    rcu_periph_clock_enable(RCU_ADC);
    // ADC??????8???????????????14MHz
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);

    /*------------------ADC GPIO??????------------------*/
    // ?????????????????????
    gpio_mode_set(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_0);
    

    /*------------------ADC??????????????????------------------*/
    // ??????????????????????????????
    adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
    // ???????????????????????????
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    // ????????????1???
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);

    // ?????????????????????????????????????????????
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);    
    // ADC ??????????????????
    adc_resolution_config(ADC_RESOLUTION_12B);

    // ??????ADC
    adc_enable();
    
    delay_1ms(1);
    
    // ??????ADC??????
    adc_calibration_enable();

    // ADC ???????????????????????????
    adc_regular_channel_config(0, ADC_CHANNEL_8, ADC_SAMPLETIME_55POINT5);
    
    // ?????? ADC ??????
    nvic_irq_enable(ADC_CMP_IRQn, 1, 1);
    // ?????? ADC ?????????????????????????????????
    adc_interrupt_flag_clear(ADC_INT_FLAG_EOC);
    // ?????? ADC ???????????????????????????
    adc_interrupt_enable(ADC_INT_EOC);
    
    // ????????????ADC??????
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL); 
    
    
   
}

/*!
    \brief      configure led
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_led_config(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* configure led GPIO port */
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);

    GPIO_BC(GPIOA) = GPIO_PIN_1;
}

/*!
    \brief      toggle led
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_led_toggle(void)
{
    GPIO_TG(GPIOA) = GPIO_PIN_1;
}
