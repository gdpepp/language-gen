#include <stdlib.h>
#include "random.h"
#include <stdio.h>

void setSeed() {
    srand( (unsigned int) time(NULL));
}

int getRandInt() {
    return rand();
}


int getRandByRange(int lo, int hi) {
    int randint = getRandInt();
    int result = 0;
    if (hi == 0) {
        hi = lo;
        lo = 0;
    }

     result = (int) (randint) % (hi - lo ) + lo;
     return result;
}

int halfChance() {
    int rand = getRandByRange(0, 10);	   
    printf("%d ",rand);
    return rand < 5 ? 1 : 0; 
}


int likely() {
    int rand = getRandByRange(0, 10);	
    return rand < 6 ? 1 : 0; 
}

int rarely() {
    int rand = getRandByRange(0, 10);	
    return rand <=1 ? 1 : 0; 
}

