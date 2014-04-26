/* 
 * File:   HashClass.h
 * Author: aaron
 *
 * Created on 2013年6月8日, 下午2:11
 */

#ifndef HASHCLASS_H
#define	HASHCLASS_H

#include <string>
using namespace std;

class Hash{
private:
    size_t keyNum;
public:
  Hash(void);  
  size_t AaronHash(wstring);
};

#endif	/* HASHCLASS_H */

