

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


/* Procedure of turning ON/OFF LED:
 * 1. Get the base address + Offset of Clock RCC AHB1 registers --> 0x4002 3800 + 0x30 = 0x40023830
 * 	then, SET the RCC register at 3rd bit position, rest unchanged; So use (bitwise OR) for SETTING 3rd position 1 and rest 0(unchanges.)
 *
 * 2. Get the base address + offset of GPIOD(PORT MODE SELECTION) peripheral register
 * address--> 0x4002 0C00 + 0x00  = 0x40020c00
 * (port moder at pin 12 is at[25,24 -> 01])
 *
 * 3. Get the base address + offset of GPIOD(OUTPUT DATA Regis) Peripheral registers --> 0x4002 0C00 + 0x04 = 0x40020c14
 */



int main(void)
{

//	//Create Pointer pointing to above address; (don't forget to type cast the address otherwise it will considered as integer value to pointers)
	uintmax_t *ptrClkRccReg = (uintmax_t*) 0x40023830;
	uintmax_t *ptrModeReg = (uintmax_t*) 0x40020c00;
	uintmax_t *ptrOutputReg = (uintmax_t*) 0x40020c14;



	//1. SET RCC 3rd Bit position
	*ptrClkRccReg |= (0x1<<3);   //-> (mask value) has been calculated by Left shifting 0x1<<3; why shifting with 3 bcz it is asked to SET 3rd bit position of CLK RCC registers



	//2. SETING Mode Register at Pin-12
		//-> Firstly, CLEAR 25th and 24th bit to 0,0 -> for CLEARING (&) and Mask value -> calculate through left shift (all 1s except 25th and 24th position is 0).
		//-> Then, SEt 25th and 24th bit to 0,1 -> for SETTING (|) and the Mask Value ->calculate through left shift (all 0s except 25-> 0 & 24-> 1)

	*ptrModeReg &= ~(0x3<<24);  //CLEARING(& *), Mask value -> left shift binary 0000....011=hex 0x3;  0x3<<24 and then negating to 111..00111...1
	*ptrModeReg |= 0x1<<24;		//SETTING(| +), Mask Value -> left shift binary 000...001=hex 0x1;  0x1<<24

	//3. SETTING Output register at pin 12, in this upper nibble(16 bits) are reserved
		//-> SET using (&), Mask Value -> left shift binary 000...001=hex 0x1;;  0x1<<12 (rest is only 12th bit position 1 others from 6th to 31 are reserved don't disturn those pins)

	*ptrOutputReg |= 0x1<<12;


	/* Loop forever */
	while(1);

}





