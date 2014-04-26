#include "ComprehendClass.h"

Comprehend::Comprehend(const char fpath[], const char fpath2[]) {

    //initialize set
    keyNum = 200000;
    dicData = new vector<wstring>[keyNum];
    maxLen = 4;
    mmPro = 1;
    rmmPro = 1;
    tmpPro = 0;
    //input the dictionary
    ifstream dic(fpath);
    if (!dic) {
        throw "Error: Unable to open input file.";
    }
    string dicLine;
    while (getline(dic, dicLine)) {
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
        size_t addrKey = 0;
        for (size_t i = 0; i != 3; ++i) {
            if (i == 0)
                addrKey = AaronHash(s2ws(tmpKeyWord[i]));
            dicData[addrKey].push_back(s2ws(tmpKeyWord[i]));
        }
    }
    dic.close();
    wcout << L"Initialization of Dictionary Succeed!" << endl;

    //get tMatrix form fileifstream dic(fpath);
    ifstream transfer(fpath2);
    if (!transfer) {
        throw "Error: Unable to open input file.";
    }
    size_t num = 0;
    size_t size = 35;
    while (getline(transfer, dicLine)) {
        string tmpKeyWord[size];
        int n = 0;
        for (int i = 0; i < dicLine.size(); ++i) {
            if (dicLine[i] != ' ') {
                tmpKeyWord[n] += dicLine[i];
            } else {
                ++n;
            }
        }
        for (size_t i = 0; i != size - 1; ++i) {
            tMatrix[num][i] = atof(tmpKeyWord[i].c_str());
        }
        ++num;
    }
    transfer.close();
    wcout << L"Initialization of Transfer Matrix Succeed!" << endl;
    //    for (size_t i = 0; i < size - 1; ++i) {
    //        for (size_t j = 0; j < size - 1; ++j)
    //            cout << i << ": " << j << tMatrix[i][j] << endl;
    //    }
}

wstring Comprehend::wordHandler(wstring preSent) {

    wstring hanSent = HMM(BM(preSent));
    wcout << L"Sentence Comprehend Finished: " << endl;
    wcout << hanSent << endl;
    return hanSent;
}

void Comprehend::reset() {

}

wstring Comprehend::findDic(wstring preSent) {

    size_t addrKey = AaronHash(preSent);
    double tmpPro2 = 0;
    wstring hanSent;
    vector<wstring>::iterator iter = dicData[addrKey].begin();
    while (iter != dicData[addrKey].end()) {
        wstring endSign(L";");
        if (preSent == *iter) {
            ++iter;
            hanSent += *iter + endSign;
            ++iter;
            double tmpPro3 = atoi(ws2s(*iter).c_str());
            tmpPro2 += tmpPro3;
            stringstream strStr;
            strStr << tmpPro3 << ";";
            hanSent += s2ws(strStr.str());
        }
        ++iter;
    }
    tmpPro = tmpPro2;
    return hanSent;
}

wstring Comprehend::MM(wstring preSent) {

    short index = 0;
    wstring hanSent;
    //match by order
    while (index != preSent.length()) {
        for (short i = maxLen; i != 0; --i) {
            //must less than the length of string
            wstring tmpSent;
            wstring wordAttr;
            if (index + i <= preSent.length()) {
                for (short j = 0; j != i; ++j) {
                    tmpSent += preSent[index + j];
                }
                //search sub-string in the Dic
                wordAttr = findDic(tmpSent);
                if (wordAttr.length() != 0) {
                    mmPro *= tmpPro / keyNum;
                    if (index + i != preSent.length())
                        hanSent += tmpSent + L"(" + wordAttr + L")" + L"/";
                    else
                        hanSent += tmpSent + L"(" + wordAttr + L")";
                    index += (i - 1);
                    break;
                }
            }
        }
        ++index;
    }
    return hanSent;
}

wstring Comprehend::RMM(wstring preSent) {

    short index = preSent.length() - 1;
    wstring hanSent;
    //match by order
    while (index >= 0) {
        for (short i = maxLen; i != 0; --i) {
            wstring tmpSent;
            wstring wordAttr;
            //must less than the length of string
            if (index + 1 >= i) {
                for (short j = 0; j != i; ++j) {
                    tmpSent = preSent[index - j] + tmpSent;
                }
                //search sub-string in the Dic
                wordAttr = findDic(tmpSent);
                if (wordAttr.length() != 0) {
                    rmmPro *= tmpPro / keyNum;
                    if (index + 1 != i)
                        hanSent = L"/" + tmpSent + L"(" + wordAttr + L")" + hanSent;
                    else
                        hanSent = tmpSent + L"(" + wordAttr + L")" + hanSent;
                    index -= (i - 1);
                    break;
                }
            }
        }
        --index;
    }
    return hanSent;
}

wstring Comprehend::BM(wstring preSten) {

    wstring mmSent = MM(preSten);
    wstring rmmSent = RMM(preSten);
    if (mmPro > rmmPro)
        return mmSent;
    else
        return rmmSent;

}

wstring Comprehend::HMM(wstring preSent) {

    wstring hanSent;
    wstring POS[] = {L"<bos>", L"nt", L"ns", L"n", L"g",
        L"nz", L"vn", L"vd", L"f", L"d", L"e", L"b", L"c", L"a", L"o", L"l", L"m",
        L"j", L"k", L"h", L"i", L"w", L"v", L"u", L"t", L"s", L"r", L"q",
        L"p", L"an", L"ad", L"z", L"y", L"<eos>"};
    int CIXING[] = {19484, 10834, 22427, 258894, 7270, 2643,
        41753, 528, 17141, 47805, 27, 8562, 25437, 34308, 70, 5876, 41105, 8354,
        928, 47, 5018, 172913, 184664, 74829, 20649, 3746, 32324, 24190, 39925,
        2798, 5932, 1390, 1889, 0,};
    vector<wstring> cixingji;
    vector<wstring> words;
    wstring tmpStr;
    for (size_t i = 0; i != preSent.length(); ++i) {
        switch (preSent[i]) {
            case L'(':
                words.push_back(tmpStr);
                tmpStr = L"";
                break;
            case L')':
                cixingji.push_back(tmpStr);
                tmpStr = L"";
                break;
            case L'/':
                break;
            default:
                tmpStr += preSent[i];
                break;
        }
    }
    words.push_back(L"<eos>");
    cixingji.push_back(L"<eos>");
    int num = words.size();
    size_t NUM = 34;
    double delta[num][NUM - 2]; //记录每一步的概率
    wstring bestmark[num]; //记录最佳标注
    double cixing_num[num][NUM - 1]; //记录每个词相应词性出现的个数

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < NUM - 2; j++) {
            double launch = 0.0; //发射概率

            //对一个词的词性集切分，单独取一个词性算发射概率
            vector<wstring> cixings;
            cixings.push_back(L"");
            size_t cxnum = 0;
            for (size_t k = 0; k < cixingji[i].length(); ++k) {
                if (cixingji[i][k] != L';') {
                    cixings[cxnum] += cixingji[i][k];
                } else {
                    cixings.push_back(L"");
                    ++cxnum;
                }
            }
            for (int m = 0; m + 2 < cixings.size(); m += 2) {
                if (cixings[m] == POS[j + 1]) {
                    cixing_num[i][j + 1] = atof(ws2s(cixings[m + 1]).c_str());
                    launch = atof(ws2s(cixings[m + 1]).c_str()) * 1.0 / CIXING[j + 1];
                }
            }

            //viterbi 每步计算
            if (i == 0) {//第一步为发射概率乘以初始概率
                delta[i][j] = tMatrix[0][j + 1] * launch;
            } else {
                int index;
                double max = -1.0;
                int maxId = 0;
                double tmp[NUM - 2];

                for (index = 0; index < NUM - 2; index++) {
                    tmp[index] = delta[i - 1][index] * tMatrix[index + 1][j + 1];
                }
                for (index = 0; index < NUM - 2; index++) {
                    if (max <= tmp[index]) {
                        max = tmp[index];
                        maxId = index + 1;
                    }
                }
                delta[i][j] = max * launch;

                bestmark[i - 1] = POS[maxId]; //每步运算确定前一个词的词性
            }
        }
    }

    //拼接结果字符串
    for (int n = 0; n < num - 1; n++) {
        size_t index = 0;
        while (index < NUM) {
            if (bestmark[n] == (POS[index])) {
                break;
            }
            ++index;
        }
        string tmp;
        stringstream stream;
        stream << (int) cixing_num[n][index];
        stream >> tmp;
        hanSent += words[n] + L"(" + bestmark[n] + L";" + s2ws(tmp) + L";)/"; //n为词数
    }
    hanSent = hanSent.substr(0, hanSent.length() - 1);
    return hanSent;
}