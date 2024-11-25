#include "xtmrctr.h"
#include "xintc.h"
#include "xparameters.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#include "mb_interface.h"
#include <xbasic_types.h>
#include <xio.h>
#include <stdint.h>

extern XTmrCtr per_timer;
extern int test_time;
extern int count;
extern int time_spent;

extern int fft_count;
extern int fsl_count;
extern int other_count;
void performance_handler();
