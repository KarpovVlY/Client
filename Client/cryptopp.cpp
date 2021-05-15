#include "cryptopp.h"

#include <QDebug>

using namespace CryptoPP;

#define PRIVATE_KEY "729308A8E815F6A46EB3A8AE6D5463CA7B64A0E2E11BC26A68106FC7697E727E37011"



char networkKey[70];


cryptopp::cryptopp() { }



void cryptopp::generate(QString username, QString password)
{




}


QString cryptopp::generateNetworkKey(long int publicKeyE, long int publicKeyN)
{
    char characters[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
    int index;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uid(0, strlen(characters));

    for(int i = 0 ; i < 69 ; i++)
    {
        index = uid(gen);
        networkKey[i] = characters[index];
    }

    qDebug() << networkKey << '\n';



    QString res(networkKey);
    return res;
}


/*
long int cryptopp::rsaEncrypt(long int stringChar,long int publicKeyE, long int publicKeyN)
{
    long int current, result;

        current = stringChar;
        result = 1;

        for ( long int j = 0; j < publicKeyE; j++ )
        {
            result = result * current;
            result = result % publicKeyN;
        }

        return result;
}

*/


QString cryptopp::encrypt(const QString &password)
{
    std::string plain = password.toStdString();
    std::string ciphertext;


    HexDecoder decoder;
    decoder.Put( (byte *)PRIVATE_KEY, 32 * 2 );
    decoder.MessageEnd();


    word64 size = decoder.MaxRetrievable();
    char *decodedKey = new char[size];
    decoder.Get((byte *)decodedKey, size);


    byte key[ AES::MAX_KEYLENGTH ], iv[ AES::BLOCKSIZE ];
    StringSource( reinterpret_cast<const char *>(decodedKey), true,
                  new HashFilter(*(new SHA256), new ArraySink(key, AES::MAX_KEYLENGTH)));

    memset( iv, 0x00, AES::BLOCKSIZE );

    CBC_Mode<AES>::Encryption Encryptor( key, sizeof(key), iv );

    StringSource( plain, true, new StreamTransformationFilter( Encryptor,
                  new HexEncoder(new StringSink( ciphertext ) ) ) );


    return QString::fromStdString(ciphertext);
}


QString cryptopp::decrypt(const QString &password)
{
    std::string plain;
    std::string encrypted = password.toStdString();


    HexDecoder decoder;
    decoder.Put( (byte *)PRIVATE_KEY, 32 * 2 );
    decoder.MessageEnd();


    word64 size = decoder.MaxRetrievable();
    char *decodedKey = new char[size];
    decoder.Get((byte *)decodedKey, size);


    byte key[ AES::MAX_KEYLENGTH ], iv[ AES::BLOCKSIZE ];
    StringSource( reinterpret_cast<const char *>(decodedKey), true,
                  new HashFilter(*(new SHA256), new ArraySink(key, AES::MAX_KEYLENGTH)));

    memset( iv, 0x00, AES::BLOCKSIZE );

    try
    {
        CBC_Mode<AES>::Decryption Decryptor
        ( key, sizeof(key), iv );
        StringSource( encrypted, true,
                      new HexDecoder(new StreamTransformationFilter( Decryptor,
                                     new StringSink( plain ) ) ) );
    }
    catch (Exception &e) {}
    catch (...) {}

    return QString::fromStdString(plain);
}


