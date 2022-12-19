//
// Created by wrc on 22-12-8.
//

#ifndef TOOLBOX_MYENCODER_H
#define TOOLBOX_MYENCODER_H

#include <string>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

class myencoder {
public:
    myencoder()=default;
    ~myencoder()=default;

    double getProgress();
    void clearProgress();

    int genarate_key();
    void encrypt(std::string filename);
    void decrypt(std::string filename, std::string key);
private:
    double progress=0;
};


#endif //TOOLBOX_MYENCODER_H
