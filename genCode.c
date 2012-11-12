#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macutil.h"



#define MAX_LEN 128
#define PREMAC_EXCEPT -1

#define READ_DB "mac.db"
#define WRITE_C "mac.c"
#define WRITE_H "mac.h"



void write_macc(void);
void write_mach(void);



int main(int argc, char *argv[]){

    write_macc();
    write_mach();

    return 0;
}



/*
 * Procedure: write_macc
 */
void write_macc(void){

    FILE *rfp, *wfp;
    char string[MAX_LEN];
    unsigned long mac, premac;

    if((rfp = fopen(READ_DB, "r")) == NULL){
        fprintf(stderr, "ERROR: File open (%s).\n", READ_DB);
        exit(EXIT_FAILURE);
    }

    if((wfp = fopen(WRITE_C, "w")) == NULL){
        fprintf(stderr, "ERROR: File open (%s).\n", WRITE_C);
        exit(EXIT_FAILURE);
    }

    fprintf(wfp, "#include <stdio.h>\n");
    fprintf(wfp, "#include <stdlib.h>\n\n\n");
    fprintf(wfp, "void searchMac(unsigned long mac){\n");
    fprintf(wfp, "\tprintf(\"Vendor: \");\n");
    fprintf(wfp, "\tswitch(mac){\n");

    premac = PREMAC_EXCEPT;
    while(fgets(string, MAX_LEN, rfp) != NULL){

        char *chs = strchr(string, ' ');
        char *che = strchr(chs, '\n');

        *(chs++) = '\0';
        *che = '\0';

        mac = macton(string);
        if(mac != premac){
            if(premac == PREMAC_EXCEPT)
                fprintf(wfp, "\t\tcase %lu: printf(\"%s\\n\"); ", mac, chs);
            else
                fprintf(wfp, "break;\n\t\tcase %lu: printf(\"%s\\n\"); ", mac, chs);
        }else{
            fprintf(wfp, " printf(\"%s\\n\"); ", chs);
        }
        premac = mac;
    }

    fprintf(wfp, "\n\t\tdefault: printf(\"Unknown.\\n\");\n");
    fprintf(wfp, "\t}\n");
    fprintf(wfp, "\treturn;\n");
    fprintf(wfp, "}\n");
    fclose(wfp);
};



/*
 * procedure: write_mach
 */
void write_mach(void){

    FILE *fp;

    if((fp = fopen(WRITE_H, "w")) == NULL){
        fprintf(stderr, "ERROR: File open (%s).\n", WRITE_H);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "#ifndef MAC_H_INCLUDED\n");
    fprintf(fp, "#define MAC_H_INCLUDED\n");
    fprintf(fp, "\n\n\n");
    fprintf(fp, "void searchMac(unsigned long mac);\n");
    fprintf(fp, "\n\n\n");
    fprintf(fp, "#endif /* MAC_H_INCLUDED */\n");
}
