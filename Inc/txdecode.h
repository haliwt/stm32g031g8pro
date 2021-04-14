#ifndef __TXDECODE_H
#define __TXDECODE_H
#include "main.h"
#include "gpio.h"

void TxDecode(void);

void CheckRun(void);


extern uint8_t led_by_id;  //A组 还是 B 组
extern uint8_t led_by_A;   //A
extern uint8_t led_by_B;  //


#endif 


