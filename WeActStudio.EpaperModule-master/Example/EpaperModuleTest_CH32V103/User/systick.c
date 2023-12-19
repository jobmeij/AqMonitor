/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "systick.h"
#include "ch32v10x.h"
#include "ch32v10x_pwr.h"

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

volatile uint32_t _tick = 0;

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void)
{
    uint32_t ticks = (SystemCoreClock / SysTick_Tick);

    //�ر�ϵͳ������STK��������ֹͣ����
    SysTick->CTLR = 0x0000;

    //����ϵͳ�������Ĵ�����ֵ

    //ϵͳ��������λ�Ĵ���
    SysTick->CNTL0 = 0;
    SysTick->CNTL1 = 0;
    SysTick->CNTL2 = 0;
    SysTick->CNTL3 = 0;

    //ϵͳ��������λ�Ĵ���
    SysTick->CNTH0 = 0;
    SysTick->CNTH1 = 0;
    SysTick->CNTH2 = 0;
    SysTick->CNTH3 = 0;

    //���ü����ȽϼĴ�����ֵ����Ҫ���ڴ���STK�жϷ���������CNT[63:0]��CMP[63:0]ֵ���ʱ������STK�жϷ���
    //���ü����Ƚϵ�λ�Ĵ�����ֵ
    SysTick->CMPLR0 = (uint8_t)(ticks & 0xFF);
    SysTick->CMPLR1 = (uint8_t)(ticks >> 8);
    SysTick->CMPLR2 = (uint8_t)(ticks >> 16);
    SysTick->CMPLR3 = (uint8_t)(ticks >> 24);

    //���ü����Ƚϸ�λ�Ĵ�����ֵ
    SysTick->CMPHR0 = 0;
    SysTick->CMPHR1 = 0;
    SysTick->CMPHR2 = 0;
    SysTick->CMPHR3 = 0;
    NVIC_SetPriority(SysTicK_IRQn, 15); //����SysTick�ж����ȼ�
    NVIC_EnableIRQ(SysTicK_IRQn);       //ʹ�ܿ���Systick�ж�
    SysTick->CTLR = 0x0001;             //����ϵͳ������STK��HCLK/8ʱ���� 72000000/8=9000000
}

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay(uint32_t count)
{
    uint32_t utick;
    utick = count + systick_get_tick();

    while (systick_get_tick() < utick)
    {
    }
}

/*!
    \brief      delay a time in milliseconds with low power
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_lp(uint32_t count)
{
    uint32_t utick;
    utick = count + systick_get_tick();

    while (systick_get_tick() < utick)
    {
        PWR_EnterSTANDBYMode();
    }
}

/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    _tick++;
}

/*!
    \brief      get systick tick
    \param[in]  none
    \param[out] none
    \retval     none
*/

uint32_t systick_get_tick(void)
{
    return _tick;
}

void systick_DisableIRQ(void)
{
    NVIC_DisableIRQ(SysTicK_IRQn);
}

void systick_EnableIRQ(void)
{
    NVIC_EnableIRQ(SysTicK_IRQn);
}

void systick_Disable(void)
{
    /* Disable SysTick */
    //�ر�ϵͳ������STK��������ֹͣ����
    SysTick->CTLR = 0x0000;
}

void systick_Enable(void)
{
    /* Enable SysTick */
    //����ϵͳ������STK��HCLK/8ʱ���� 72000000/8=9000000
    SysTick->CTLR = 0x0001;
}

void systick_deinit(void)
{
    //�ر�ϵͳ������STK��������ֹͣ����
    SysTick->CTLR = 0x0000;
}

void SysTick_Handler(void)
{
    //����ϵͳ�������Ĵ�����ֵ
    //ϵͳ��������λ�Ĵ���
    SysTick->CNTL0 = 0;
    SysTick->CNTL1 = 0;
    SysTick->CNTL2 = 0;
    SysTick->CNTL3 = 0;
    //ϵͳ��������λ�Ĵ���
    SysTick->CNTH0 = 0;
    SysTick->CNTH1 = 0;
    SysTick->CNTH2 = 0;
    SysTick->CNTH3 = 0;

    delay_decrement();
}
