#include <stdlib.h>
#include "random.h"

int getRandInt() {
    srand( (unsigned int) time(NULL));
    return rand();
}


int getRandByRange(int lo, int hi) {
    int randint = getRandInt();

    if (hi == 0) {
        hi = lo;
        lo = 0;
    }

    return (int) floor(randint  *  (hi - lo)) + lo;

}
