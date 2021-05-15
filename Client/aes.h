#ifndef AES_H
#define AES_H

#include <openssl/aes.h>
#include <cstring>

#include <QString>

class AES
{
public:
    AES();


    QString aesEncrypt(QString inputString);

    int aesDecrypt(char* inputString,
                       char* outputString);

    void aesCreateKey();

    void aesKeyEncrypt(char* inputString, char* outputString);
};

#endif
