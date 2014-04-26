/* 
 * File:   ServerClass.h
 * Author: aaron
 *
 * Created on 2013年6月4日, 上午11:08
 */

#ifndef SERVERCLASS_H
#define	SERVERCLASS_H

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include "StringHandler.h"
using namespace std;

class Server : private StringHandler {
private:
    int listenSock;
    int communicationSock;
    sockaddr_in servAddr;
    sockaddr_in clntAddr;
    vector<wstring> message;
    wstring origMes;
    void mesHandler(wstring preSent);
    void connectInfo(void);
public:
    Server(int listen_port);
    bool isAccept(void);
    void recvSent(void);
    wstring getClient(void);
    wstring getAction(void);
    wstring getMessage(void);
    wstring getQuestion(void);
    wstring getAnswer(void);
    wstring getEmotion(void);
    void sendSent(wstring preSent);
    void reset(void);
};


#endif	/* SERVERCLASS_H */

