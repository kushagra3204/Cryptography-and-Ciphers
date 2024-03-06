#include <bits/stdc++.h>
using namespace std;

string processText(string text) {
  string capitalText;
  for (int i = 0; i < text.length(); i++) {
    if (text[i] <= 122 && text[i] >= 97) {
      capitalText.push_back(text[i] - 32);
    } else {
      capitalText.push_back(text[i]);
    }
  }
  return capitalText;
}

string EncryptText(string plaintext, string key) {
  string cipherText;

  string PText = processText(plaintext);
  string K = processText(key);

  for (int i = 0; i < PText.length(); i++) {
    char x = (PText[i] + K[i]) % 26;
    cipherText.push_back(char(x + 65));
  }
  return cipherText;
}

string DecryptText(string cipherText, string key) {
  string decryptedText;

  string CText = processText(cipherText);
  string K = processText(key);

  for (int i = 0; i < CText.length(); i++) {
    char x = (CText[i] - K[i] + 26) % 26;
    decryptedText.push_back(char(x + 65));
  }
  return decryptedText;
}

string autoKey(string key, int Plength) {
  int i;
  for (i = 0;; i++) {
    if (Plength == i)
      i = 0;
    if (key.size() == Plength)
      break;
    key.push_back(key[i]);
  }
  return key;
}

int main() {

  string plaintext, key, cipherText, decryptedText, generatedKey;
  int x;
  cout << " \n> 1. Encrypt";
  cout << " \n> 2. Decrypt";
  cout << " \n> 3. Exit";
  cout << " \n> Enter Choice (1/2/3): ";
  cin >> x;
  while (x != 3) {

    if (x == 1) {
      // Encrypt
      cout << "\nEnter the plaintext: ";
      cin >> plaintext;
      cout << "Enter the key: ";
      cin >> key;
      generatedKey = autoKey(key, plaintext.length());
      cipherText = EncryptText(plaintext, generatedKey);
      cout << "\n  >> Cipher Text is: " << cipherText << "\n";

    } else if (x == 2) {
      // Decrypt
      cout << "\nEnter the ciphertext: ";
      cin >> cipherText;
      cout << "Enter the key: ";
      cin >> key;
      generatedKey = autoKey(key, cipherText.length());
      decryptedText = DecryptText(cipherText, generatedKey);
      cout << "\n  >> Decrypted Text is: " << decryptedText << "\n";

    } else {
      cout << "\nEnter valid option\n";
    }

    cout << " \n> Enter Choice (1/2/3): ";
    cin >> x;
  }

  return 0;
}