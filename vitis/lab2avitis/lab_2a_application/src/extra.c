#include "extra.h"
#include "xgpio.h"
#include "xparameters.h"
#include <stdlib.h>

XIntc sys_intc;
XTmrCtr sys_tmrctr;
XGpio EncoderGpio;

Xuint32 data;

volatile int count = 0;
volatile int ledOut = 0b0000000000000001;

enum States {
	R,
	CW1,
	CW0,
	CW2,
	CCW2,
	CCW0,
	CCW1
};
volatile int enable = 1;
enum States fsm = R;

int light = 0;

XGpio RGBGpio;


void extra_handler() {
	// This is the interrupt handler function
	// Do not print inside of this function.
	Xuint32 ControlStatusReg;
	/*
	 * Read the new Control/Status Register content.
	 */
	ControlStatusReg =
			XTimerCtr_ReadReg(sys_tmrctr.BaseAddress, 0, XTC_TCSR_OFFSET);

	if(count == 5){
		count = 0;
		light = 1 - light;
	}


	count++;

	if(light == 1){
//		XGpio_DiscreteWrite(&RGBGpio, 1, 18);
//      It's blinding me.

	}
	else {
		XGpio_DiscreteWrite(&RGBGpio, 1, 0);
	}
	/*
	 * Acknowledge the interrupt by clearing the interrupt
	 * bit in the timer control status register
	 */
	XTmrCtr_WriteReg(sys_tmrctr.BaseAddress, 0, XTC_TCSR_OFFSET,
			ControlStatusReg |XTC_CSR_INT_OCCURED_MASK);

}

void encoder_handler(void *CallbackRef){
	XGpio *GpioPtr = (XGpio *)CallbackRef;

	unsigned int encoderVal = XGpio_DiscreteRead(&EncoderGpio, 1);
	if(encoderVal > 3) enable = 1 - enable;

	int bit0 = 1 & encoderVal;
	int bit1 = (2 & encoderVal) >> 1;

	if(enable){
		switch(fsm){
		case R:
			if(bit0 == 0) fsm = CW1;
			else if(bit1 == 0) fsm = CCW2;
			//else xil_printf("ERROR");
			break;
		case CW1:
			if(bit0 == 1) fsm = R;
			else if(bit1 == 0) fsm = CW0;
			//else xil_printf("ERROR");
			break;
		case CW0:
			if(bit0 == 1) fsm = CW2;
			else if(bit1 == 1) fsm = CW1;
			//else xil_printf("ERROR");
			break;
		case CW2:
			if(bit0 == 0) fsm = CW0;
			else if(bit1 == 1) {
				fsm = R;
				ledOut = ledOut << 1;
				if(ledOut > 0b1000000000000000) ledOut = 1;
			}
			//else xil_printf("ERROR");
			break;
		case CCW2:
			if(bit0 == 0) fsm = CCW0;
			else if(bit1 == 1) fsm = R;
			//else xil_printf("ERROR");
			break;
		case CCW0:
			if(bit0 == 1) fsm = CCW2;
			else if(bit1 == 1) fsm = CCW1;
			//else xil_printf("ERROR");
			break;
		case CCW1:
			if(bit0 == 1){
				fsm = R;
				ledOut = ledOut >> 1;
				if(ledOut == 0) ledOut = 0b1000000000000000;
			}
			else if(bit1 == 0) fsm = CCW0;
			//else xil_printf("ERROR");
			break;
		}
	}

	//xil_printf("%d",encoderVal);

	XGpio_InterruptClear(GpioPtr, 1);
}

void extra_disable() {
	XIntc_Disable(&sys_intc,
			XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR);
}

void extra_enable() {
	XIntc_Enable(&sys_intc,
			XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR);
}

int extra_method() {
	//xil_printf("I'm in the main() method\r\n");

	XStatus Status;
	XGpio_Initialize(&RGBGpio, XPAR_RGBLEDS_DEVICE_ID);
	/*
	 * Initialize the interrupt controller driver so that
	 * it is ready to use, specify the device ID that is generated in
	 * xparameters.h
	 */
	Status = XST_SUCCESS;
	Status = XIntc_Initialize(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID);

	if (Status != XST_SUCCESS) {
		if (Status == XST_DEVICE_NOT_FOUND) {
			xil_printf("XST_DEVICE_NOT_FOUND...\r\n");
		} else {
			xil_printf("a different error from XST_DEVICE_NOT_FOUND...\r\n");
		}
		xil_printf("Interrupt controller driver failed to be initialized...\r\n");
		return XST_FAILURE;
	}
	xil_printf("Interrupt controller driver initialized!\r\n");
	/*
	 * Connect the application handler that will be called when an interrupt
	 * for the timer occurs
	 */
	Status = XIntc_Connect(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR,
			(XInterruptHandler) extra_handler, &sys_tmrctr);
	if (Status != XST_SUCCESS) {
		xil_printf("Failed to connect the application handlers to the interrupt controller...\r\n");
		return XST_FAILURE;
	}
	xil_printf("Connected to Interrupt Controller!\r\n");

	XIntc_Connect(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_ENCODER_IP2INTC_IRPT_INTR,
				(XInterruptHandler) encoder_handler, &EncoderGpio);

	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts.
	 */
	Status = XIntc_Start(&sys_intc, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		xil_printf("Interrupt controller driver failed to start...\r\n");
		return XST_FAILURE;
	}
	xil_printf("Started Interrupt Controller!\r\n");
	/*
	 * Enable the interrupt for the timer counter
	 */
	XIntc_Enable(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_TIMER_0_INTERRUPT_INTR);
	XIntc_Enable(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_ENCODER_IP2INTC_IRPT_INTR);

	/*
	 * Initialize the timer counter so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
	Status = XTmrCtr_Initialize(&sys_tmrctr, XPAR_AXI_TIMER_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("Timer initialization failed...\r\n");
		return XST_FAILURE;
	}
	xil_printf("Initialized Timer!\r\n");
	/*
	 * Enable the interrupt of the timer counter so interrupts will occur
	 * and use auto reload mode such that the timer counter will reload
	 * itself automatically and continue repeatedly, without this option
	 * it would expire once only
	 */
	XTmrCtr_SetOptions(&sys_tmrctr, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
	/*
	 * Set a reset value for the timer counter such that it will expire
	 * eariler than letting it roll over from 0, the reset value is loaded
	 * into the timer counter when it is started
	 */
	XTmrCtr_SetResetValue(&sys_tmrctr, 0, 0xFFFFFFFF - RESET_VALUE);// 1000 clk cycles @ 100MHz = 10us
	/*
	 * Start the timer counter such that it's incrementing by default,
	 * then wait for it to timeout a number of times
	 */
	XTmrCtr_Start(&sys_tmrctr, 0);
	/*
	 * Register the intc device driver’s handler with the Standalone
	 * software platform’s interrupt table
	 */


	//Encoder Interrupt Creation
	XGpio_Initialize(&EncoderGpio, XPAR_GPIO_2_DEVICE_ID);
	XGpio_InterruptEnable(&EncoderGpio, 1);
	XGpio_InterruptGlobalEnable(&EncoderGpio);



	microblaze_register_handler(
			(XInterruptHandler) XIntc_DeviceInterruptHandler,
			(void*) XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID);
//	microblaze_register_handler((XInterruptHandler)XIntc_DeviceInterruptHandler,
//			(void*)PUSHBUTTON_DEVICE_ID);
	//xil_printf("Registers handled!\r\n");

	/*
	 * Enable interrupts on MicroBlaze
	 */
	microblaze_enable_interrupts();
	xil_printf("Interrupts enabled!\r\n");
	/*
	 * At this point, the system is ready to respond to interrupts from the timer
	 */

	return XST_SUCCESS;
}
