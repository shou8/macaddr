#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "macutil.h"



/*
 * function: macton
 *
 * ARG:
 *      char macs[]: MAC address (string)
 *
 * RET:
 *      unsigned long: MAC address (number)
 *
 */
unsigned long macton(char macs[])
{
	char *p = macs;
	unsigned long macn = 0;

	// counter
	char c = 1;

	while (*p != '\0')
	{
		if (*p == '.' || *p == ':') {
			p++;
			continue;
		}

		macn = macn << HEX_SHIFT;
		macn += (unsigned long)hton(*p);
		p++; c++;

		if (c > MAC_OUI_RANGE)
			break;
	}

	return macn;
}



/*
 * function: hton
 *
 * ARG:
 *      c: Target character to convert hex number
 *
 * RET:
 *      char: HEX number
 *
 */
char hton(char c)
{
	if (c >= ASCII_RANGE_NUM_LOWER && c <= ASCII_RANGE_NUM_HIGHER)
		return (c - ASCII_RANGE_NUM_LOWER);

	c = toupper(c);
	if (c < ASCII_RANGE_ALP_LOWER || c > ASCII_RANGE_ALP_HIGHER){
		fprintf(stderr, "ERROR: Invalid MAC address.\n");
		exit(EXIT_FAILURE);
	}

	return c - ASCII_ALP_TO_HEX;
}



/*
 * function macCmp
 *
 * INFO:
 *      This function compare MAC addresses.
 *      And this compare only 6 units of head of MAC in HEX.
 *      This can only use MAC presented by number
 *      (Use "macton" or "hton")
 *
 * ARG:
 *      mac1: MAC address to compare
 *      mac2: MAC address to compare
 *
 * RET:
 *      unsigned long: 
 *          0   : Match (These of two are same MAC address)
 *          else: Not match (These of two are different)
 */
unsigned long macCmp(unsigned long *mac1, unsigned long *mac2){
	return *mac1 ^ *mac2;
}
