//
// Created by gdi on 31/8/2018.
//

#ifndef LANGUAGE_GEN_RANDOM_H
#define LANGUAGE_GEN_RANDOM_H

#include <stdlib.h>
#include <math.h>
#include <time.h>

void setSeed();

int getRandInt();

int getRandByRange(int lo, int hi);

int halfChance();

int likely();

int rarely();

#endif //LANGUAGE_GEN_RANDOM_H
