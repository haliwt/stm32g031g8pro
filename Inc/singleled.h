#ifndef __SINGLELED_H
#define __SINGLELED_H
#include "main.h"

void SingleLed_Test(void);

void TurnOff_TheSecondLedB(void);
void TurnOff_TheFirstLedA(void);

void TheFirstGroup_SingleLEDA(void);
void TheSecondGroup_SingleLEDB(void);
void FanControl(uint8_t fanval);

typedef struct _ledabled_
{
  uint8_t led_by_a;
  uint8_t led_by_b;
    
    
    
}led;

extern led ledab;

#endif
