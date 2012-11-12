#include <stdio.h>
#include <stdlib.h>
#include "macutil.h"
#include "mac.h"



int main(int argc, char *argv[]){

    if(argc != 1){
        fprintf(stderr, "Ussage: %s <MAC Address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    unsigned long mac;
    mac = macton(argv[1]);
    searchMac(mac);

    return 0;
}

