#include "led.h"

#define THREAD_PRIORITY         30
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static rt_thread_t tid = RT_NULL;

static void led_entry(void *parm)
{
    int count = 1;
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    while(count++)
    {
        rt_pin_write(LED1_PIN, count % 2);
        rt_thread_delay(100);
        rt_pin_write(LED2_PIN, count % 2);
        rt_thread_delay(100);
        rt_pin_write(LED3_PIN, count % 2);
        rt_thread_delay(100);
    }
}

int led_init(void)
{
    tid = rt_thread_create("led", led_entry, RT_NULL, THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(led_init);
