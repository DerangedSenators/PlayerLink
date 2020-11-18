//
// Created by hanzalah on 07/11/2020.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
* Diffie Hellman Key Exchange
 * WIP
*/

struct DFHValues{
    unsigned long commonPrime;
    unsigned long secret;
    int baseG;
};
/**
 * Generates a secret to hold for the key exchange
 * @param dfhValues
 */
void generateSecret(struct DFHValues *dfhValues){
    time_t t;
    // Generate Secret
    srand((unsigned ) time(&t));
    dfhValues->secret = rand();
}
int compute(unsigned long commonPrime){
    struct DFHValues dfhValues;
    dfhValues.commonPrime = commonPrime;
    return 0;
}