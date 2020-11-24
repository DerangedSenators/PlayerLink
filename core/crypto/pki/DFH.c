/*
 * Copyright (C) 2020 Deranged Senators
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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