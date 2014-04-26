/* 
 * File:   generalFun.h
 * Author: aaron
 *
 * Created on 2013年6月6日, 下午4:44
 */

#ifndef GENERALFUN_H
#define	GENERALFUN_H
#include <string>
#include <stdlib.h>
#include <vector>
#include <string.h>
using namespace std;

class StringHandler {
public:
    StringHandler(void);
    wstring s2ws(string preStr);
    string ws2s(wstring preStr);
};



#endif	/* GENERALFUN_H */

