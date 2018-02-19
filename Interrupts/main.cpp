#include <sam.h>
#include <hwlib.hpp>

#include "system_sam3xa.h"

#include "pio.h"

extern "C"
{
	void PIOA_Handler(void)
	{
		hwlib::cout << "test" << hwlib::endl;
	}
	
	void PIOB_Handler(void)
	{
		hwlib::cout << "test" << hwlib::endl;
	}
	
	void PIOC_Handler(void)
	{
		hwlib::cout << "test" << hwlib::endl;
	}
	
	void PIOD_Handler(void)
	{
		hwlib::cout << "test" << hwlib::endl;
	}
}

Pio& port_index_to_reg(uint32_t port) {
	switch(port){
		case 0  : return *PIOA;
		case 1  : return *PIOB;
		case 2  : return *PIOC;
		case 3  : return *PIOD;
		default : return *((Pio*) 0x00); // undefined behavior
	}
}

uint32_t port_index_to_id(uint32_t port) {
	switch(port){
		case 0  : return ID_PIOA;
		case 1  : return ID_PIOB;
		case 2  : return ID_PIOC;
		case 3  : return ID_PIOD;
		default : return -1; // undefined behavior
	}
}

int main(void) {
	PMC->PMC_PCER0 = 0b111111 << 11;// enable clock to all GPIO registers
	
	hwlib::target::pin_info_type pin_info = hwlib::target::pin_info(hwlib::target::pins::d49);
	
	Pio& pinPort = port_index_to_reg(pin_info.port);
	pio_type_t pinMask = (pio_type_t) pin_info.pin;
	
	pio_set_output(&pinPort, pinMask, 0, false, true);
	pio_set_input(&pinPort, pinMask, 0);
	pio_pull_up(&pinPort, pinMask, false);
	
	while (true) {
		hwlib::cout << pio_get(&pinPort, (pio_type_t) PIO_TYPE_PIO_INPUT, pinMask) << hwlib::endl;
		hwlib::wait_ms(100);
	}
}

/*int main(void)
{
	SystemInit();
	
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	hwlib::wait_ms(500);
	
	hwlib::cout << "Hi" << hwlib::endl;
	
	PMC->PMC_PCER0 = ( 0b111111 << 11 ); // enable clock to all GPIO registers
	
	hwlib::target::pin_info_type pin_info = hwlib::target::pin_info(hwlib::target::pins::d49);
	
	Pio& pinPort = port_index_to_reg(pin_info.port);
	
	uint32_t portId = port_index_to_id(pin_info.port);
	uint32_t pinMask = 1 << pin_info.pin;
	
	pinPort.PIO_ODR = pinMask;
	pinPort.PIO_PUDR = pinMask;
	
	NVIC_ClearPendingIRQ((IRQn_Type) portId); // clear pending status
	NVIC_SetPriority((IRQn_Type) portId, 0); // set priority level
	NVIC_EnableIRQ((IRQn_Type) portId); // Enable interrupt
	
	pinPort.PIO_AIMER = pinMask;
	pinPort.PIO_LSR = pinMask;    // "Level" Select Register
	pinPort.PIO_REHLSR = pinMask; // "Rising Edge / High Level" Select Register
	
	hwlib::cout << "Mode configured" << hwlib::endl;
	
	pinPort.PIO_IER = pinMask;
	
	hwlib::cout << "Interrupt enabled" << hwlib::endl;
	
	while (1) {
		hwlib::cout << ((pinPort.PIO_PDSR & pinMask) != 0) << hwlib::endl;
		hwlib::cout << hwlib::endl;
		hwlib::wait_ms(100);
	}
}*/