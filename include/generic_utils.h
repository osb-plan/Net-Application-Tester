#ifndef GENERIC_UTILS_H
#define GENERIC_UTILS_H

	#define SET(x,y) x |= (1 << y)
	
	// Set bit y (0-indexed) of x to '0' by generating a mask with a '0' in
        // the y position and 1's elsewhere then ANDing the mask with x.
	
	#define CLEAR(x,y) x &= ~(1<< y)
	
	// Return '1' if the bit value at position y within x is '1' and '0' if
        // it's 0 by ANDing x with a bit mask where the bit in y's position is 
        // '1' and '0' elsewhere and comparing it to all 0's.  Returns
        // '1' in least significant bit position if the value of the bit is 
        // '1', '0' if it was '0'.
	
	#define GET(x,y) ((0u == (x & (1<<y)))?0u:1u)
	
	//Toggle bit y (0-index) of x to the inverse: '0' becomes '1', '1' 
        // becomes '0' by XORing x with a bitmask where the bit in position y 
        // is '1' and all others are '0'.
	
	#define TOGGLE(x,y) (x ^= (1<<y))
	#define LSB8(x) (x & 0x0F)
	#define MSB8(x) ((x >> 4) & 0x0F)

#endif
