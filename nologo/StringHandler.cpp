#include "StringHandler.h"

StringHandler::StringHandler() {

}

wstring StringHandler::s2ws(string preStr) {

    const char* _Source = preStr.c_str();
    size_t _Dsize = preStr.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest, _Source, _Dsize);
    wstring hanStr = _Dest;
    delete []_Dest;
    return hanStr;
}

string StringHandler::ws2s(wstring preStr) {

    size_t const mbs_len = wcstombs(NULL, preStr.c_str(), 0);
    vector<char> tmp(mbs_len + 1);
    wcstombs(&tmp[0], preStr.c_str(), tmp.size());
    string dest;
    dest.assign(tmp.begin(), tmp.end() - 1);
    return dest;
}
