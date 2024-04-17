#include <openssl/sha.h>
#include<iostream>
using namespace std;
typedef unsigned char byte;

int main(int argc, char *argv[]) {
    const int DataLen = 30;
    SHA_CTX shactx;
    byte digest[SHA_DIGEST_LENGTH];

    byte* testdata = new byte[DataLen];
    for (int i=0; i<DataLen; i++) testdata[i] = 0;

    SHA1_Init(&shactx);
    SHA1_Update(&shactx, testdata, DataLen);
    SHA1_Final(digest, &shactx);

    for (int i=0; i<SHA_DIGEST_LENGTH; i++)
	printf("%02x", digest[i]);
    putchar('\n');

    return 0;
}
