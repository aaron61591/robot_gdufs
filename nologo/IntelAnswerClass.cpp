#include "IntelAnswerClass.h"

IntelAnswer::IntelAnswer(const char *fpath, const char *fpath2) {

    //initialize set
    keyNum = 200000;
    indexData = new vector<wstring>[keyNum];
    answerData = new vector<wstring>[keyNum];

    //input the index file
    ifstream index(fpath);
    if (!index) {
        throw "Error: Unable to open input file.";
    }
    string dicLine;
    size_t num = 0;
    while (getline(index, dicLine)) {
        string tmpKeyWord[3];
        int n = 0;
        for (int i = 0; i < dicLine.size(); ++i) {
            if (dicLine[i] != '/') {
                tmpKeyWord[n] += dicLine[i];
            } else {
                ++n;
            }
        }
        //create index
        size_t addrKey = AaronHash(s2ws(tmpKeyWord[0]));
        bool exist = false;
        tmpKeyWord[2] += ";";
        for (vector<wstring>::iterator iter = indexData[addrKey].begin(); iter != indexData[addrKey].end(); iter += 3) {
            if (*iter == s2ws(tmpKeyWord[0])) {
                if (*++iter == s2ws(tmpKeyWord[1])) {
                    *++iter += s2ws(tmpKeyWord[2]);
                    exist = true;
                    break;
                }
                --iter;
            }
        }
        if (!exist) {
            for (size_t i = 0; i != 3; ++i) {
                indexData[addrKey].push_back(s2ws(tmpKeyWord[i]));
            }
        }
        ++num;
    }
    index.close();
    wcout << L"Initialization of Answer Index Succeed!" << endl;

    //input the answer file
    ifstream answer(fpath2);
    if (!answer) {
        throw "Error: Unable to open input file.";
    }
    while (getline(answer, dicLine)) {
        string keyWord[3];
        int n = 0;
        for (int i = 0; i < dicLine.size(); ++i) {
            if (dicLine[i] != '/') {
                keyWord[n] += dicLine[i];
                //                keyWord[0] = s2ws(dicLine.substr(0, i));
                //                keyWord[1] = s2ws(dicLine.substr(i + 1, dicLine.size() - i));
            } else {
                ++n;
            }
        }
        //create index
        size_t addrKey = AaronHash(s2ws(keyWord[0]));
        answerData[addrKey].push_back(s2ws(keyWord[0]));
        answerData[addrKey].push_back(s2ws(keyWord[1]));
        answerData[addrKey].push_back(s2ws(keyWord[2]));
        ++num;
    }
    answer.close();
    wcout << L"Initialization of Answer File Succeed!" << endl;

    //        for (size_t i = 0; i < keyNum; ++i)
    //            for (vector<wstring>::iterator iter = answerData[i].begin(); iter != answerData[i].end(); ++iter)
    //                wcout << *iter << endl;
}

wstring IntelAnswer::getAnswer(wstring preSent) {

    keyWordSort(preSent);
    wstring index = matchAnswer();
    vector<wstring> answer = answerData[AaronHash(index)];
    for (vector<wstring>::iterator iter = answer.begin(); iter != answer.end(); iter += 3) {
        if (*iter == index) {
            //the first char is emotion code
            wstring tmp = *++iter;
            tmp += *++iter;
            return tmp;
        }
    }
    return L"5= =！ 额。。。你教我回答呗。。。";
}

void IntelAnswer::saveAnswer(wstring preSent, wstring emotion, wstring answer, const char *fpath, const char *fpath2) {

    time_t now = 0;
    stringstream strStr;
    wstring answerId;
    string tmp;
    size_t addrKey = 0;
    time(&now);
    strStr << now;
    strStr >> tmp;
    answerId = s2ws(tmp);
    //get a answer id
    while (ifAnswerExist(answerId)) {

        answerId += L"X";
    }
    addrKey = AaronHash(answerId);
    //add the new answer to ram;
    answerData[addrKey].push_back(answerId);
    answerData[addrKey].push_back(emotion);
    answerData[addrKey].push_back(answer);
    //add the new answer to disk
    ofstream answerFile(fpath2, ios::app);
    answerFile << ws2s(answerId) << "/" << ws2s(emotion) << "/" << ws2s(answer) << endl;
    answerFile.close();
    //get the index keyword
    getKeyWord(preSent);
    vector<wstring> saveKeyWord;
    size_t save_num = 0;
    for (vector<wstring>::iterator iter = keyWord.begin(); iter != keyWord.end() && save_num < 9; ++iter, ++save_num) {
        saveKeyWord.push_back(*iter);
    }
    ofstream indexFile(fpath, ios::app);
    for (vector<wstring>::iterator iter = saveKeyWord.begin(); iter != saveKeyWord.end(); iter += 3) {
        //add the index to ram
        size_t addrKey = AaronHash(*iter);
        bool find = false;
        for (vector<wstring>::iterator iter2 = indexData[addrKey].begin(); iter2 != indexData[addrKey].end(); iter2 += 3) {
            if (*iter2 == *iter) {
                if (*++iter2 == *++iter) {
                    *++iter2 += answerId + L";";
                    --iter2;
                    find = true;
                }
                --iter;
                --iter2;
            }
        }
        if (!find) {
            for (int i = 0; i < 3; ++i, ++iter)
                if (i == 2) {
                    indexData[addrKey].push_back(answerId + L";");
                } else
                    indexData[addrKey].push_back(*iter);
            iter -= 3;
        }
        //add the index to disk
        indexFile << ws2s(*iter) << "/";
        indexFile << ws2s(*++iter) << "/";
        indexFile << ws2s(answerId) << endl;
        --iter;
    }
    indexFile.close();
}

void IntelAnswer::reset(void) {

    matAnswer.clear();
    keyWord.clear();
    vector<size_t>().swap(matAnswer);
    vector<wstring>().swap(keyWord);
}

void IntelAnswer::getKeyWord(wstring preSent) {

    wstring tmpSent;
    size_t length = preSent.length();
    for (size_t i = 0; i <= length; ++i) {
        switch (preSent[i]) {
            case L'(':
                keyWord.push_back(tmpSent);
                tmpSent = L"";
                break;
            case L';':
                keyWord.push_back(tmpSent);
                tmpSent = L"";
                break;
            case L')':
                break;
            case L'/':
                break;
            default:
                tmpSent += preSent[i];
                break;
        }
    }
}

void IntelAnswer::keyWordSort(wstring preSent) {

    //get keywords
    getKeyWord(preSent);

    //to sort keyWords by num the keyWord appearence
    size_t keyWordNum = 0;
    size_t keyWordNum2 = 0;
    wstring tmpWord;
    for (vector<wstring>::iterator iter = keyWord.begin(); iter != keyWord.end(); ++iter) {
        iter += 2;
        keyWordNum = atoi(ws2s(*iter).c_str());
        for (vector<wstring>::iterator iter2 = iter + 1; iter2 != keyWord.end(); ++iter2) {
            iter2 += 2;
            keyWordNum2 = atoi(ws2s(*iter2).c_str());
            if (keyWordNum > keyWordNum2) {
                iter -= 2;
                iter2 -= 2;
                for (size_t k = 0; k != 3; ++k, ++iter, ++iter2) {
                    tmpWord = *iter;
                    *iter = *iter2;
                    *iter2 = tmpWord;
                }
                --iter;
                --iter2;
                keyWordNum = atoi(ws2s(*iter).c_str());
            }
        }
    }
    wcout << L"KeyWord Sort Finished: " << endl;
    for (vector<wstring>::iterator iter = keyWord.begin(); iter != keyWord.end(); ++iter) {
        wcout << *iter << L" ";
    }
    wcout << endl;
}

wstring IntelAnswer::matchAnswer(void) {

    //get all keywords' anwer
    wcout << L"All KeyWords' Answer: " << endl;
    wstring tmpKeyWord[keyWord.size() / 3];
    size_t answerIndex = 0;
    for (vector<wstring>::iterator iter = keyWord.begin(); iter != keyWord.end(); iter += 3, ++answerIndex) {
        size_t index = AaronHash(*iter);
        for (vector<wstring>::iterator iter2 = indexData[index].begin(); iter2 != indexData[index].end(); iter2 += 3) {
            if (*iter == *iter2) {
                if (*++iter == *++iter2) {
                    tmpKeyWord[answerIndex] = *++iter2;
                    wcout << L"KeyWord" << answerIndex << L": " << *iter2 << endl;
                    iter -= 1;
                    break;
                } else {
                    --iter;
                    --iter2;
                }
            }
        }
    }

    //get the best match answer
    vector<wstring> answerVec;
    for (size_t i = 0; i < keyWord.size() / 3; ++i) {

        //it will be more efficient when the keyword has no answer
        if (tmpKeyWord[i].length()) {
            wstring tmpStr;
            //get the answer number to a vector
            vector<wstring> newAnswer;
            for (size_t j = 0; j < tmpKeyWord[i].length(); ++j) {
                if (tmpKeyWord[i][j] != L';') {
                    tmpStr += tmpKeyWord[i][j];
                } else {
                    newAnswer.push_back(tmpStr);
                    tmpStr = L"";
                }
            }
            if (answerVec.empty()) {
                answerVec = newAnswer;
                //                break;
                continue;
            } else {

                //get the itersection
                vector<wstring> tmpVec;
                for (vector<wstring>::iterator iter = answerVec.begin(); iter != answerVec.end(); ++iter) {
                    for (vector<wstring>::iterator iter2 = newAnswer.begin(); iter2 != newAnswer.end(); ++iter2) {
                        if (*iter == *iter2) {
                            tmpVec.push_back(*iter);
                        }
                    }
                }
                if (tmpVec.begin() != tmpVec.end())
                    answerVec = tmpVec;
                else
                    break;
            }
        }
    }
    //finished
    wcout << L"Answer Match Finished:" << endl;
    for (vector<wstring>::iterator iter = answerVec.begin(); iter != answerVec.end(); ++iter) {
        wcout << *iter << L" ";
    }
    wcout << endl;
    //select one answer by random
    if (answerVec.size() != 0) {
        srand((int) time(0));
        vector<wstring>::iterator iter = answerVec.begin();
        iter += rand() % answerVec.size();
        return *iter;
    } else {
        return L"";
    }
}

bool IntelAnswer::ifAnswerExist(wstring preSent) {


    size_t addrKey = AaronHash(preSent);
    for (vector<wstring>::iterator iter = answerData[addrKey].begin(); iter != answerData[addrKey].end(); iter += 3) {
        if (*iter == preSent) {
            return true;
        }
    }
    return false;
}