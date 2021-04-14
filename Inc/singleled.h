#ifndef __SINGLELED_H
#define __SINGLELED_H
#include "main.h"

void SingleLed_Test(void);

void TurnOff_TheSecondLedB(void);
void TurnOff_TheFirstLedA(void);

void TheFirstGroup_SingleLEDA(uint8_t ledvala);
void TheSecondGroup_SingleLEDB(uint8_t ledvalb);
void FanControl(uint8_t fanval);

#endif 