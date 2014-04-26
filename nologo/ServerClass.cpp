#include "ServerClass.h"

Server::Server(int listen_port) {

    if ((listenSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw "socket() failed";
    }
    memset(&servAddr, 0, sizeof (servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(listen_port);
    if (bind(listenSock, (sockaddr*) & servAddr, sizeof (servAddr)) < 0) {
        throw "bind() failed";
    }
    wcout << L"Initialization of Server Engine Succeed!" << endl;
    if (listen(listenSock, 10) < 0) {
        throw "listen() failed";
    }
    wcout << L"Server Engine Listening..." << endl;
}

bool Server::isAccept() {

    unsigned int clntAddrLen = sizeof (clntAddr);
    if ((communicationSock = accept(listenSock, (sockaddr*) & clntAddr, &clntAddrLen)) < 0) {
        return false;
    } else {
        return true;
    }
}

void Server::recvSent(void) {

    const size_t BUFFERSIZE = 32;
    char buffer[BUFFERSIZE];
    int recvMsgSize = 32;
    string tmpSent;
    int num = 0;
    while (recvMsgSize == BUFFERSIZE) {
        memset(buffer, 0, sizeof (buffer));
        if ((recvMsgSize = (int) recv(communicationSock, buffer, BUFFERSIZE, 0)) < 0) {
            throw "recv() failed";
        } else {
            ++num;
            tmpSent += buffer;
        }
    }
    mesHandler(s2ws(tmpSent));
    connectInfo();
}

void Server::sendSent(wstring preSent) {

    string tmpSent = ws2s(preSent);
    size_t index = 0;
    size_t strLen = tmpSent.length();
    const size_t BUFFERSIZE = 32;
    while (index < strLen) {
        string tmp;
        for (int i = index; i < strLen && i < index + BUFFERSIZE; ++i) {

            tmp += tmpSent[i];
        }
        const char *buffer = tmp.c_str();
        size_t len = tmp.length();
        send(communicationSock, buffer, len, 0);
        index += BUFFERSIZE;
    }
    close(communicationSock);
    wcout << L"Message Sent:" << endl;
    wcout << preSent << endl;
    wcout << L"Client(IP: " << getClient() << L") Released." << endl;
}

void Server::reset() {
    message.clear();
    vector<wstring>().swap(message);
}

void Server::mesHandler(wstring preSent) {

    origMes = preSent;
    vector<size_t> pos;
    size_t index = 0;
    size_t num = 4;
    bool save = false;
    for (size_t i = 0; i < preSent.length(); ++i) {
        if (preSent[i] == L'"') {
            if (num % 4 > 1) {
                pos.push_back(i);
                if (save) {
                    size_t form = pos[index++] + 1;
                    size_t length = pos[index++] - form;
                    message.push_back(preSent.substr(form, length));
                    save = false;
                } else {
                    save = true;
                }
            }
            ++num;
        }
    }
    for (size_t i = 2; i < 4; ++i) {
        wstring tmpStr = message[i];
        message[i] = L"";
        for (int j = 0; j < tmpStr.length(); ++j) {
            switch (tmpStr[j]) {
                case L';':
                    break;
                case L'(':
                    break;
                case L'/':
                    break;
                case L'\\':
                    break;
                default:
                    message[i] += tmpStr[j];
            }
        }
    }
}

void Server::connectInfo(void) {

    wcout << L"Client(IP: " << getClient() << L") Connected." << endl;
    wcout << L"Json: " << origMes << endl;
    wcout << L"Action: " << getAction() << endl;
    if (message[3] != L"") {
        wcout << L"Question: " << getQuestion() << endl;
        wcout << L"Answer: " << getAnswer() << endl;
    } else {
        wcout << L"Message: " << getMessage() << endl;
    }
}

wstring Server::getAction(void) {

    return message[0];
}

wstring Server::getClient(void) {

    return message[1];
}

wstring Server::getMessage(void) {

    return message[2];
}

wstring Server::getQuestion(void) {

    return message[2];
}

wstring Server::getAnswer(void) {

    return message[3];
}

wstring Server::getEmotion(void) {

    return message[4];
}