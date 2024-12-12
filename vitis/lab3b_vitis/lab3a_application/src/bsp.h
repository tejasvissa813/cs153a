/*****************************************************************************
* bsp.h for Lab2A of ECE 153a at UCSB
* Date of the Last Update:  October 23,2014
*****************************************************************************/
#ifndef bsp_h
#define bsp_h


void GpioHandler(void *CallbackRef);
void TwistHandler(void *CallbackRef);
void TimerHandler();
void LatencyHandler();

extern float freq;
extern int fft_timer;
extern int encoder;
extern int short_time;
extern int time;
extern int hfsm;
extern int draw_timer;


/* bsp functions ..........................................................*/

void BSP_init(void);
void ISR_gpio(void);
void ISR_timer(void);

void printDebugLog(void);

#define BSP_showState(prio_, state_) ((void)0)


#endif                                                             /* bsp_h */


