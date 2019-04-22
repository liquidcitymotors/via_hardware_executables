 /** \file interrupt_link.cpp
 * \brief Interrupt handler callback implementation.
 *
 * The functions in this file link wraps the methods of the module class in C friendly callbacks.
 * If I recall, this was necessary because the interrupt handler functions called from the system NVIC needed to be defined in C code.
 *
 */

#include "interrupt_link.hpp"
#include "delay.hpp"

/// Assign the callback function pointers to the wrapper functions and the pointer to the module class to the void pointer modulePointer.
void linkInterrupts(ViaDelay * voidPointer) {

	modulePointer = (void *) voidPointer;

	uiTimerCallback = *uiTimerHandler;
	mainRisingEdgeCallback = &mainRisingEdgeHandler;
	mainFallingEdgeCallback = &mainFallingEdgeHandler;
	auxRisingEdgeCallback = &auxRisingEdgeHandler;
	auxFallingEdgeCallback = &auxFallingEdgeHandler;
	buttonPressedCallback = &buttonPressedHandler;
	buttonReleasedCallback = &buttonReleasedHandler;
	dacHalfTransferCallback = &dacHalfTransferHandler;
	dacTransferCompleteCallback = &dacTransferCompleteHandler;
	dacTimerCallback = &dacTimerHandler;
	sdaadcConversionCompleteCallback = &sdaadcConversionCompleteHandler;
	adcConversionCompleteCallback = &adcConversionCompleteHandler;
	auxTimer1InterruptCallback = &auxTimer1InterruptHandler;
	auxTimer2InterruptCallback = &auxTimer2InterruptHandler;

}

//@{
/// Cast the void pointer to used to reference the module class to an actual pointer to the class. Use that to call the appropriate handler method.
void uiTimerHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->ui_dispatch(TIMEOUT_SIG);

}
void mainRisingEdgeHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->mainRisingEdgeCallback();

}
void mainFallingEdgeHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->mainFallingEdgeCallback();

}
void auxRisingEdgeHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->auxRisingEdgeCallback();

}
void auxFallingEdgeHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->auxFallingEdgeCallback();

}
void buttonPressedHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->buttonPressedCallback();

}
void buttonReleasedHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->buttonReleasedCallback();

}
void adcConversionCompleteHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->slowConversionCallback();

}
void dacHalfTransferHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->halfTransferCallback();

}
void dacTransferCompleteHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->transferCompleteCallback();

}
void dacTimerHandler(void *) {
	;
}
void sdaadcConversionCompleteHandler(void *) {
	;
}

void auxTimer1InterruptHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->auxTimer1InterruptCallback();

}

void auxTimer2InterruptHandler(void * voidPointer) {

	ViaDelay * modulePointer = (ViaDelay *) voidPointer;
	modulePointer->auxTimer2InterruptCallback();

}
//@}
