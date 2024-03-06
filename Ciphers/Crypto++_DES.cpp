#include <cryptopp890/cryptlib.h>
#include <cryptopp890/des.h>
#include <cryptopp890/filters.h>
#include <cryptopp890/hex.h>
#include <cryptopp890/modes.h>
#include <iostream>
#include <string>
using namespace std;
using namespace CryptoPP;

int main() {
  try {
    // Key setup
    string keyHex =
        "0011223344556677"; // 8-byte (64-bit) key in hexadecimal format
    string ivHex =
        "1122334455667788"; // 8-byte (64-bit) IV in hexadecimal format

    SecByteBlock key(DES::DEFAULT_KEYLENGTH);
    HexDecoder keyDecoder(new ArraySink(key, key.size()));
    keyDecoder.Put(reinterpret_cast<const CryptoPP::byte *>(keyHex.data()),
                   keyHex.size());
    keyDecoder.MessageEnd();

    SecByteBlock iv(DES::BLOCKSIZE);
    HexDecoder ivDecoder(new ArraySink(iv, iv.size()));
    ivDecoder.Put(reinterpret_cast<const CryptoPP::byte *>(ivHex.data()),
                  ivHex.size());
    ivDecoder.MessageEnd();

    // Plaintext
    string plaintext = "Hello, Crypto++!";
    cout << "Original Text: " << plaintext << endl;

    // Encryption
    string ciphertext;
    CBC_Mode<DES>::Encryption encryption(key, key.size(), iv);
    StringSource(plaintext, true,
                 new StreamTransformationFilter(
                     encryption, new HexEncoder(new StringSink(ciphertext))));
    cout << "Encrypted Text (Hex): " << ciphertext << endl;

    // Decryption
    string decryptedtext;
    CBC_Mode<DES>::Decryption decryption(key, key.size(), iv);
    StringSource(ciphertext, true,
                 new HexDecoder(new StreamTransformationFilter(
                     decryption, new StringSink(decryptedtext))));
    cout << "Decrypted Text: " << decryptedtext << endl;
  } catch (const Exception &e) {
    cerr << "Crypto++ exception: " << e.what() << endl;
    return 1;
  }

  return 0;
}