#include <stdio.h>
#include <math.h>
#include "stdlib.h"
#include "time.h" //gfg

double main(int argc, char *argv[]) {
    if(argc < 4){
        printf("Usage:./blacbox [x] [y] [d]");
        return -1;
    }
    char* end1;
    char* end2;
    char* end3;
    double x = strtod(argv[1], &end1), y = strtod(argv[2], &end2), d = strtod(argv[3], &end3);
    double z = pow(x, 2) + pow(y, 2) ;
    double e = 0;
    srand(time(0)); //gfg
    if(d == 0){
        e = 1;
    } else{
       // e = rand() % (int)(d*z);
        e = ((double)rand() / ((double)RAND_MAX + 1) * (d*z));
        e += 1;
    }
    double zd = z + e;
    printf("%f", zd);
    return 0;
}
