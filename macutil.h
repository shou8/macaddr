#ifndef MACUTIL_H_INCLUDED
#define MACUTIL_H_INCLUDED

#define MAC_OUI_RANGE 6

#define ASCII_RANGE_NUM_LOWER 48
#define ASCII_RANGE_NUM_HIGHER 57
#define ASCII_RANGE_ALP_LOWER 65
#define ASCII_RANGE_ALP_HIGHER 70
#define ASCII_ALP_TO_HEX 55

#define HEX_SHIFT 4

unsigned long macton(char macs[]);
char hton(char c);
unsigned long macCmp(unsigned long *mac1, unsigned long *mac2);

#endif /* MACUTIL_H_INCLUDED */
