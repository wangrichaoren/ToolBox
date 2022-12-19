//
// Created by wrc on 22-12-6.
//

#include "DES.h"
#include <cstdio>

// 生成16轮密钥
void DES::generateKey(bitset<64> key) {
    // 置换1后的56位密钥
    bitset<56> k;
    k = permutation1(key);
    //cout << k << endl << endl;

    // 左部分和右部分
    bitset<28> left, right, newl, newr;
    bit56tobit28(k, left, right);

    for (int i = 0; i < 16; i++) {
        newl = leftShift(left, shiftBits[i]);
        newr = leftShift(right, shiftBits[i]);
        bit28tobit56(k, newl, newr);
        // cout << shiftBits[i] << " " <<  k << endl;
        subkey[i] = permutation2(k);
        left = newl, right = newr;
    }
    // for (int i = 0; i < 16; i++)cout << subkey[i] << endl;
}

// 代替函数组S
bitset<32> DES::subS(bitset<48> sin) {
    bitset<32> output;
    int x = 0;
    for (int i = 0; i < 48; i += 6) {
        // 进行S盒转化
        int row = sin[i] * 2 + sin[i + 5];
        int col = sin[i + 1] * 8 + sin[i + 2] * 4 + sin[i + 3] * 2 + sin[i + 4];
        bitset<4> num = sbox[i / 6][row * 12 + col];

        // 赋值给32位output
        for (int j = 0; j < 4; j++)
            output[x + j] = num[3 - j];
        x += 4;
    }
    return output;
}


// 选择运算E
bitset<48> DES::selectE(bitset<32> part) {
    bitset<48> res;
    for (int i = 0; i < 48; i++)
        res[i] = part[E[i] - 1];
    return res;
}

// 置换运算P
bitset<32> DES::permuP(bitset<32> inp) {
    bitset<32> res;
    for (int i = 0; i < 32; i++)
        res[i] = inp[P[i] - 1];
    return res;
}

// 56位分为28位和28位
void DES::bit56tobit28(bitset<56> &res, bitset<28> &left, bitset<28> &right) {
    for (int i = 0; i < 28; i++) {
        left[i] = res[i];
        right[i] = res[i + 28];
    }

}

// 28位合成56位
void DES::bit28tobit56(bitset<56> &res, bitset<28> &left, bitset<28> &right) {
    for (int i = 0; i < 28; i++) {
        res[i] = left[i];
        res[i + 28] = right[i];
    }
}


// 置换选择1
bitset<56> DES::permutation1(bitset<64> key) {
    bitset<56> res;
    for (int i = 0; i < 56; i++)
        res[i] = key[PC_1[i] - 1];
    return res;
}

// 循环左移
bitset<28> DES::leftShift(bitset<28> key, int tag) {
    return key >> tag | key << (28 - tag);
}

// 置换选择2
bitset<48> DES::permutation2(bitset<56> key) {
    bitset<48> res;
    for (int i = 0; i < 48; i++)
        res[i] = key[PC_2[i] - 1];
    return res;
}

// 初始置换
bitset<64> DES::initialPermutation(bitset<64> init) {
    bitset<64> res;
    for (int i = 0; i < 64; i++) {
        res[i] = init[IP[i] - 1];
    }
    return res;
}

bitset<64> DES::invInitialPermutation(bitset<64> init) {
    bitset<64> res;
    for (int i = 0; i < 64; i++) {
        res[i] = init[IP_1[i] - 1];
    }
    return res;
}

// 64位变为32位
void DES::bit64tobit32(bitset<64> &res, bitset<32> &left, bitset<32> &right) {
    for (int i = 0; i < 32; i++) {
        left[i] = res[i];
        right[i] = res[i + 32];
    }
}

// 32位合为64位
void DES::bit32tobit64(bitset<64> &res, bitset<32> &left, bitset<32> &right) {
    for (int i = 0; i < 32; i++) {
        res[i] = left[i];
        res[i + 32] = right[i];
    }
}

// 左右32位互换
void DES::exchangelr(bitset<32> &left, bitset<32> &right) {
    bitset<32> temp;
    temp = left;
    left = right;
    right = temp;
}

// 加密函数f
bitset<32> DES::f(bitset<32> in, bitset<48> key) {
    // 选择运算E
    bitset<48> temp;
    temp = selectE(in);

    // 与子密钥异或
    bitset<48> mid;
    mid = temp ^ key;

    // S盒变换
    bitset<32> cur;
    cur = subS(mid);

    // 置换运算P
    bitset<32> later;
    later = permuP(cur);
    return later;

}

// 加密
bitset<64> DES::encrypt(bitset<64> plain) {
    bitset<64> res;
    bitset<64> oIP;
    bitset<64> invIP;
    bitset<32> left;
    bitset<32> right;
    bitset<32> newleft;



    // 初始置换
    oIP = initialPermutation(plain);

    // 将64位变为32位
    bit64tobit32(oIP, left, right);

    for (int i = 0; i < 16; i++) {
        newleft = right;
        right = left ^ f(right, subkey[i]);
        left = newleft;
    }


    // 将32位合成64位 左右要互换
    bit32tobit64(invIP, right, left);

    // 逆初始置换
    res = invInitialPermutation(invIP);

    return res;


}

// 解密
bitset<64> DES::decrypt(bitset<64> cipher) {
    bitset<64> res;
    bitset<64> oIP;
    bitset<64> invIP;
    bitset<32> left;
    bitset<32> right;
    bitset<32> newleft;



    // 初始置换
    oIP = initialPermutation(cipher);

    // 将64位变为32位
    bit64tobit32(oIP, left, right);

    for (int i = 15; i >= 0; i--) {
        newleft = right;
        right = left ^ f(right, subkey[i]);
        left = newleft;
    }

    // 将32位合成64位 左右要互换
    bit32tobit64(invIP, right, left);

    // 逆初始置换
    res = invInitialPermutation(invIP);

    return res;

}


// 字符串转二进制
bitset<64> DES::char2bits(const char s[8]) {
    //0001110011101100011011001010110000101100110011000100110010001100
    bitset<64> bits;
    int x = 0;
    for (int i = 0; i < 8; i++) {
        int num = (int) s[i];
        bitset<8> temp(num);
        for (int j = 0; j < 8; j++)
            bits[x + j] = temp[7 - j];
        x += 8;
    }
    return bits;
}


// 将连续的64位分成8组，存到一个 byte 数组中
void DES::divideToByte(byte out[8], bitset<64> &data) {
    bitset<64> temp;
    for (int i = 0; i < 8; ++i) {
        temp = (data << 8 * i) >> 56;
        out[i] = temp.to_ulong();
    }
}

// 将8个 byte 合并成连续的64位
bitset<64> DES::mergeByte(byte in[8]) {
    bitset<64> res;
    res.reset();  // 置0
    bitset<64> temp;
    for (int i = 0; i < 8; ++i) {
        temp = in[i].to_ulong();
        temp <<= 8 * (7 - i);
        res |= temp;
    }
    return res;
}

double DES::getProgress() {
    return progress;
};

void DES::clearProgress() {
    progress = 0;
};

// 加密文件
void DES::encryptFile(string inPath, string outPath) {
    bitset<64> data;
    bitset<64> key;
    bitset<64> outfile;
    // 将文件 flower.jpg 加密到 cipher.txt 中
    ifstream in;
    ofstream out;

    // 生成16个子密钥
    key = mergeByte(innerKey);
    generateKey(key);

    in.open(inPath, ios::binary);

    auto i1 = inPath.rfind("_decode");
    string dir1{};
    if (i1 < inPath.length()) {
        dir1 = inPath.substr(0, i1);
        auto i = inPath.rfind(".");
        string name = inPath.substr(i + 1, inPath.length() - i - 1);
        outPath = dir1 + "_encode" + "." + name;
    } else {
        auto i = inPath.rfind(".");
        string dir = inPath.substr(0, i);
        string name = inPath.substr(i + 1, inPath.length() - i - 1);
        outPath = dir + "_encode" + "." + name;
    }

    out.open(outPath, ios::binary);

    // 移动文件指针到文件末尾，得到文件的长度后，复原文件指针
    in.seekg(0, ios::end);
    int length = in.tellg(), cur;
    in.seekg(0, ios::beg);

    int n = 0;
    while (in.read((char *) &data, sizeof(data))) {
        if (!is_start){
            cout<<"check stop signal"<<endl;
            return;
        }

        n += sizeof(data);
        progress = n;

        outfile = encrypt(data);
        out.write((char *) &outfile, sizeof(outfile));

        // 找到目前文件指针所在位置，判断剩余文件流是否大于等于一个data字节大小，小于的话直接跳出循环
        cur = in.tellg();
        if (cur + 8 > length) break;

        data.reset();  // 置0
        outfile.reset();
    }
    cout << "n==== " << n << endl;
    // 得到剩余文件流字节大小
    int num = length - cur;
    //初始化一段内存
    char rest[8] = "1";
    // 将剩余的文件读入到该内存中
    in.read(rest, num);

    // 将读入内存的部分写入另一个文件
    out.write(rest, num);
    in.close();
    out.close();

    // 删除inpath
    char *remove_path = const_cast<char *>(inPath.data());
    if (remove(remove_path) == 0) {
        cout << "remove origin file!" << endl;
    } else {
        throw runtime_error("error!");
    }
}

// 解密文件
void DES::decryptFile(string inPath, string outPath) {
    bitset<64> data;
    bitset<64> key;
    bitset<64> outfile;
    // 将文件 flower.jpg 加密到 cipher.txt 中
    ifstream in;
    ofstream out;

    // 生成16个子密钥
    key = mergeByte(innerKey);
    generateKey(key);



    // 解密 cipher.txt，并写入图片 flower1.jpg
    in.open(inPath, ios::binary);


    auto i1 = inPath.rfind("_encode");
    string dir1{};
    if (i1 < inPath.length()) {
        dir1 = inPath.substr(0, i1);
        auto i = inPath.rfind(".");
        string name = inPath.substr(i + 1, inPath.length() - i - 1);
        outPath = dir1 + "_decode" + "." + name;
    } else {
        auto i = inPath.rfind(".");
        string dir = inPath.substr(0, i);
        string name = inPath.substr(i + 1, inPath.length() - i - 1);
        outPath = dir + "_decode" + "." + name;
    }


    out.open(outPath, ios::binary);

    // 移动文件指针到文件末尾，得到文件的长度后，复原文件指针
    in.seekg(0, ios::end);
    int length = in.tellg(), cur;
    in.seekg(0, ios::beg);

    double n = 0;
    while (in.read((char *) &data, sizeof(data))) {
        if (!is_start){
            cout<<"check stop signal"<<endl;
            return;
        }

        n += sizeof(data);
        progress=n;

        outfile = decrypt(data);
        out.write((char *) &outfile, sizeof(outfile));

        // 找到目前文件指针所在位置，判断剩余文件流是否大于等于一个data字节大小，小于的话直接跳出循环
        cur = in.tellg();
        if (cur + 8 > length) break;

        data.reset();  // 置0
        outfile.reset();
    }

    // 得到剩余文件流字节大小
    int num = length - cur;
    //初始化一段内存
    char rest[8] = "1";
    // 将剩余的文件读入到该内存中
    in.read(rest, num);
    // 将读入内存的部分写入另一个文件
    out.write(rest, num);

    in.close();
    out.close();

    // 删除inpath
    char *remove_path = const_cast<char *>(inPath.data());
    if (remove(remove_path) == 0) {
        cout << "remove origin file!" << endl;
    } else {
        throw runtime_error("error!");
    }
}

void DES::stop() {
    is_start= false;
}

void DES::start() {
    is_start= true;
}



