/* 
 * File:   IntelAnswerClass.h
 * Author: aaron
 *
 * Created on 2013年6月6日, 下午11:07
 */

#ifndef INTELANSWERCLASS_H
#define	INTELANSWERCLASS_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "StringHandler.h"
#include "HashClass.h"
using namespace std;

class IntelAnswer : private StringHandler, Hash {
private:
    size_t keyNum;
    vector<wstring> keyWord;
    vector<wstring> *indexData;
    vector<wstring> *answerData;
    vector<size_t> matAnswer;
    void getKeyWord(wstring preSent);
    void keyWordSort(wstring preSent);
    bool ifAnswerExist(wstring preSent);
    wstring matchAnswer(void);
public:
    IntelAnswer(const char *fpath, const char *fpath2);
    wstring getAnswer(wstring preSent);
    void saveAnswer(wstring preSent,wstring emotion, wstring answer, const char *fpath, const char *fpath2);
    void reset(void);
};

#endif	/* INTELANSWERCLASS_H */

