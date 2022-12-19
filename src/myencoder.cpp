//
// Created by wrc on 22-12-8.
//

#include "myencoder.h"

void myencoder::encrypt(std::string filename) {

    string key = to_string(genarate_key());
    cout << "genarate key is: " << key << endl;
    // Open the input and output files
    std::ifstream input(filename, std::ios::binary);
    std::ofstream output(filename + ".enc", std::ios::binary);

    // Check if the input file could be opened
    if (!input.is_open()) {
        std::cerr << "Error: Could not open input file: " << filename << std::endl;
        return;
    }

    // Encrypt the file by performing an XOR operation on each byte
    // of the input file with each corresponding byte of the key
    char ch, key_ch;
    int key_index = 0;
    int n = 0;
    while (input.get(ch)) {
        // Repeat the key as needed
        key_ch = key[key_index];
        key_index = (key_index + 1) % key.length();

        // Encrypt the character and write it to the output file
        ch ^= key_ch;
        n += sizeof(ch);
        progress=n;
        output.put(ch);
    }

    // Close the input and output files
    input.close();
    output.close();

//    filename.rfind()
    std::ofstream keyout(filename.substr(0, filename.find_last_of('.')) + ".key");
    keyout << key;
    keyout.close();
    std::remove(filename.data());
}

void myencoder::decrypt(std::string filename, std::string keyname) {
    // Open the encrypted and decrypted files
    std::ifstream input(filename, std::ios::binary);
    std::ifstream inputkey(keyname);
    string key{};
    inputkey >> key;
    cout << "get key is: " << key << endl;

    auto i = filename.rfind(".enc");
    std::cout << filename.substr(0, i) << std::endl;
    std::ofstream output(filename.substr(0, i), std::ios::binary);

    // Check if the input file could be opened
    if (!input.is_open()) {
        std::cerr << "Error: Could not open input file: " << filename << std::endl;
        return;
    }

    // Decrypt the file by performing an XOR operation on each byte
    // of the input file with each corresponding byte of the key
    char ch, key_ch;
    int key_index = 0;
    int n = 0;
    while (input.get(ch)) {

        // Repeat the key as needed
        key_ch = key[key_index];
        key_index = (key_index + 1) % key.length();

        // Decrypt the character and write it to the output file
        ch ^= key_ch;
        n += sizeof(ch);
        progress=n;
        output.put(ch);
    }

    // Close the input and output files
    input.close();
    output.close();
    remove(filename.data());
    remove(keyname.data());
}

int myencoder::genarate_key() {
    std::random_device rd;
    int key = rd();
    return key;
}

double myencoder::getProgress() {
    return progress;
}

void myencoder::clearProgress() {
    progress = 0;
}