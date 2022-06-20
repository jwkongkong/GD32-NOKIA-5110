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
    /*------------------时钟配置------------------*/
    // GPIO时钟使能
    rcu_periph_clock_enable(RCU_GPIOA);
    // ADC时钟使能
    rcu_periph_clock_enable(RCU_ADC);
    // ADC时钟8分频，最大14MHz
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);

    /*------------------ADC GPIO配置------------------*/
    // 必须为模拟输入
    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_7);
    

    /*------------------ADC工作模式配置------------------*/
    // 单通道用连续转换模式
    adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
    // 转换结果转换右对齐
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    // 转换通道1个
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);

    // 不用外部触发转换，软件开启即可
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);    
    // ADC 采样精度配置
    adc_resolution_config(ADC_RESOLUTION_12B);

    // 使能ADC
    adc_enable();
    
    delay_1ms(1);
    
    // 使能ADC校准
    adc_calibration_enable();

    // ADC 采样通道、采样时间
    adc_regular_channel_config(0, ADC_CHANNEL_7, ADC_SAMPLETIME_55POINT5);
    
    // 使能 ADC 中断
    nvic_irq_enable(ADC_CMP_IRQn, 1, 1);
    // 清除 ADC 规则组转换结束中断标志
    adc_interrupt_flag_clear(ADC_INT_FLAG_EOC);
    // 使能 ADC 规则组转换结束中断
    adc_interrupt_enable(ADC_INT_EOC);
    
    // 软件触发ADC转换
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
