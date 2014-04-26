#include "HashClass.h"

Hash::Hash(void){

    keyNum=200000;
}

size_t Hash::AaronHash(wstring key) {

    size_t addrKey = 0;
    for (int i = 0; i != key.size(); ++i) {
        addrKey += key[i];
    }
    if (addrKey < 0) {
        addrKey *= -1;
    }
    if (addrKey > keyNum) {

        addrKey %= keyNum;
    }
    return addrKey;
}
