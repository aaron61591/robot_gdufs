/* 
 * File:   ComprehendClass.h
 * Author: aaron
 *
 * Created on 2013年6月4日, 下午1:20
 */

#ifndef COMPREHENDClass_H
#define	COMPREHENDClass_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h> 
#include <stdlib.h>
#include <locale>
#include "StringHandler.h"
#include "HashClass.h"
using namespace std;

class Comprehend : private StringHandler, Hash {
private:
    size_t keyNum;
    size_t maxLen;
    double mmPro;
    double rmmPro;
    double tmpPro;
    double tMatrix[34][34];
    vector<wstring> *dicData;
    wstring MM(wstring preSent);
    wstring RMM(wstring preSent);
    wstring BM(wstring preSent);
    wstring HMM(wstring preSent);
    wstring findDic(wstring findSent);
public:
    Comprehend(const char fpath[],const char fpath2[]);
    wstring wordHandler(wstring preSent);
    void reset(void);
};

#endif	/* COMPREHENDClass_H */

