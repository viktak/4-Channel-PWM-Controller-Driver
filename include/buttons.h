#ifndef BUTTONS_H
#define BUTTONS_H

#include <Button2.h>

#define BUTTON0_GPIO 18
#define BUTTON2_GPIO 16
#define BUTTON4_GPIO 14
#define BUTTON6_GPIO 26

#define BUTTON1_GPIO 17
#define BUTTON3_GPIO 4
#define BUTTON5_GPIO 13
#define BUTTON7_GPIO 27


void setupButtons();
void loopButtons();

#endif
