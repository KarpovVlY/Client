#ifndef CRYPTOPP_H
#define CRYPTOPP_H

#include "cryptopp/aes.h"
#include "cryptopp/rijndael.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"

#include <QString>
#include <QtSql>

#include <cmath>


using namespace CryptoPP;

class cryptopp
{

public:


private:




public:
    cryptopp();


    void generate(QString username, QString password);

    QString encrypt(const QString &password);
    QString decrypt(const QString &password);

    QString generateNetworkKey(long publicKeyE,
                               long publicKeyN);

/*
    long int rsaEncrypt(long int stringChar,
                        long int publicKeyE,
                        long int publicKeyN);*/


};

#endif
