#include "aes.h"
#include <QDebug>

#include "stylesheet.h"

#include <QtSql>

QString username = "usr2021_rg_tot";
QString password = "pa_ss_wr400";


char aesKeyGenerated[AES_BLOCK_SIZE * 2] = "tEL1jEjgLlrOAgxSNOcN7WFvlk7Zvlx";


char aesKey[AES_BLOCK_SIZE] = {0};
int aesKeyLength;

AES::AES()
{
    aesCreateKey();



    //qDebug() << "\nkey\n" << aesKey;

/*
    QString str1 = Stylesheet::scrollAreaStylesheet;
    QByteArray ba = str1.toLocal8Bit();

    char *in = ba.data();
    char out[512] = {0};*/

    //aesEncrypt(in, out);

    //qDebug() << "\nencrypted\n" << out;
    //aesDecrypt(out, out);


    //qDebug() <<"\ndecrypted\n" <<  out;

}



void AES::aesCreateKey()
{
    QString key;

    if(username.size() < password.size())
        aesKeyLength = username.size();
    else
        aesKeyLength = password.size();


    for(int i = 0 ; i < aesKeyLength ; i ++)
    {
        key.append(username.at(i));
        key.append(password.at(i));
    }

    aesKeyEncrypt(key.toLocal8Bit().data(), aesKey);
}




void AES::aesKeyEncrypt(char* inputString, char* outputString)
{
    AES_KEY aes;

    unsigned char salt[AES_BLOCK_SIZE] = {0};

    if (!inputString || !outputString)
         return;


     for (int i = 0 ; i < 16 ; ++i)
          salt[i] = i + 32;


     if (AES_set_encrypt_key((unsigned char*)aesKeyGenerated, 256, &aes) < 0)
         return;

     AES_cbc_encrypt((unsigned char*)inputString, (unsigned char*)outputString,
                     aesKeyLength, &aes, salt, AES_ENCRYPT);




}



QString AES::aesEncrypt(QString inputString)
{
   AES_KEY aes;

   char* input = inputString.toLocal8Bit().data();
   char* output = input;

   unsigned char salt[AES_BLOCK_SIZE] = {0};

   if (!input)
        return nullptr;


    for (int i = 0 ; i < 16 ; ++i)
         salt[i] = i + 32;


    if (AES_set_encrypt_key((unsigned char*)aesKey, 256, &aes) < 0)
        return nullptr;

    AES_cbc_encrypt((unsigned char*)input, (unsigned char*)output,
                    4096, &aes, salt, AES_ENCRYPT);


    return QString::fromLocal8Bit((char *)output);
}




int AES::aesDecrypt(char* inputString, char* outputString)
{
    AES_KEY aes;

    unsigned char salt[AES_BLOCK_SIZE] = {0};

     if (!inputString || !outputString)
         return -1;

     for (int i = 0; i < 16; ++i)
        salt[i] = i + 32;

     if (AES_set_decrypt_key((unsigned char*)aesKey, 256, &aes) < 0)
        return -1;


    AES_cbc_encrypt((unsigned char*)inputString, (unsigned char*)outputString,
                    512, &aes, salt, AES_DECRYPT);
    return 0;
}
