/* 
 * File:   main.cpp
 * Author: aaron
 *
 * Created on 2013年6月4日, 上午10:44
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "ServerClass.h"
#include "ComprehendClass.h"
#include "IntelAnswerClass.h"
using namespace std;

void iniEnvir();
void engineStart();

int main() {
    iniEnvir();
    engineStart();
    return 0;
}

void engineStart() {

    string filepath("./libraries/dictionary/txt");
    string filepath2("./libraries/index/index");
    string filepath3("./libraries/answer/answer");
    string filepath4("./libraries/tranMatrix/transfer");
    Comprehend compre(filepath.c_str(), filepath4.c_str());
    IntelAnswer answer(filepath2.c_str(), filepath3.c_str());
    //    port num
    Server server(5000);
    while (true) {
        if (server.isAccept() == true) {
            server.recvSent();
            wstring preSent = compre.wordHandler(server.getMessage());
            if (server.getAction() == L"chat") {
                preSent = answer.getAnswer(preSent);
                server.sendSent(preSent);
            } else {
                answer.saveAnswer(preSent, server.getEmotion(), server.getAnswer(), filepath2.c_str(), filepath3.c_str());
                server.sendSent(L"finished");
            }
            compre.reset();
            answer.reset();
            server.reset();
        }
    }
}

void iniEnvir() {

    if (!setlocale(LC_ALL, "zh_CN.UTF-8")) {
        throw "Language intialization failed";
    }
}