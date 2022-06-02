// CypherCryp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <stdexcept>
using namespace std;

class CypherCryp {
private:
    const char alphabet [26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
public:
    bool isValidMessage(string message) {
        for (int i = 0; i < message.length(); i++) {
            if (message[i] == ' ') {
                continue;
            }
            else if (!isalpha(message[i])) {
                return false;
            }
        }
        return true;
    }

    string encrypt(string plainText, string key) {
        if (!isValidMessage(plainText) || key.length() == 0) {
            return "Please use only letters in the US alphabet.";
        }
        string encryptedMessage = "";
        vector<int> plainTextAsInts;
        vector<int> keyAsInts;
        transform(plainText.begin(), plainText.end(), plainText.begin(), ::toupper);
        transform(key.begin(), key.end(), key.begin(), ::toupper);

        for (int i = 0; i < plainText.length(); i++) {
            for (int j = 0; j < 26; j++) {
                if (plainText[i] == alphabet[j]) {
                    plainTextAsInts.push_back(j);
                    break;
                }
                else if (plainText[i] == ' ') {
                    plainTextAsInts.push_back(-1);
                    break;
                }
            }
        }

        for (int i = 0; i < key.length(); i++) {
            for (int j = 0; j < 26; j++) {
                if (key[i] == alphabet[j]) {
                    keyAsInts.push_back(j);
                    break;
                }
                else if (key[i] == ' ') {
                    keyAsInts.push_back(-1);
                    break;
                }
            }
        }

        for (int i = 0; i < plainText.length(); i++) {
            if (plainTextAsInts.at(i) == -1 || keyAsInts.at(i) == -1) {
                encryptedMessage.push_back(' ');
            }
            else {
                int P = plainTextAsInts.at(i);
                int K = keyAsInts.at(i);
                int E = (P + K) % 26;
                encryptedMessage.push_back(alphabet[E]);
            }
        }

        cout << "Encryption Complete!" << endl;
        
        return encryptedMessage;
    }

    string decrypt(string encryptedMsg, string key) {
        if (!isValidMessage(encryptedMsg)) {
            return "Please use only letters in the US alphabet.";
        }

        string decryptedMessage = "";
        vector<int> eMsgAsInts;
        vector<int> keyAsInts;
        transform(encryptedMsg.begin(), encryptedMsg.end(), encryptedMsg.begin(), ::toupper);
        transform(key.begin(), key.end(), key.begin(), ::toupper);

        for (int i = 0; i < key.length(); i++) {
            for (int j = 0; j < 26; j++) {
                if (key[i] == alphabet[j]) {
                    keyAsInts.push_back(j);
                    break;
                }else if (key[i] == ' ') {
                    keyAsInts.push_back(-1);
                    break;
                }
            }
        }

        for (int i = 0; i < encryptedMsg.length(); i++) {
            for (int j = 0; j < 26; j++) {
                if (encryptedMsg[i] == alphabet[j]) {
                    eMsgAsInts.push_back(j);
                    break;
                }
                else if (encryptedMsg[i] == ' ') {
                    eMsgAsInts.push_back(-1);
                    break;
                }
            }
        }

        for (int i = 0; i < encryptedMsg.length(); i++) {
            if (eMsgAsInts.at(i) == -1 || keyAsInts.at(i) == -1) {
                decryptedMessage.push_back(' ');
            }
            else {
                int E = eMsgAsInts.at(i);
                int K = keyAsInts.at(i);
                int D = (E - K + 26) % 26;
                decryptedMessage.push_back(alphabet[D]);
            }
        }
        
        cout << "Decryption Complete!" << endl;
        return decryptedMessage;
    }

    string generateKey(string plaintext, string keyword) {
        if (!isValidMessage(plaintext) || !isValidMessage(keyword)) {
            return "";
        }
        int keywordIdx = 0;
        string key = "";
        for (int i = 0; i < plaintext.length(); i++) {
            if (plaintext[i] == ' ') {
                key += ' ';
            }
            else {
                key += keyword[keywordIdx];
                keywordIdx++;
                if (keywordIdx == keyword.length()) {
                    keywordIdx = 0;
                }
            }
        }
        return key;
    }
};

int main()
{
    CypherCryp cypher;
    int menuOption = 0;
    cout << "Welcome to CypherCryp! " << endl;
    cout << "This program will encrypt or decrypt messages when given the message to be encrypted and a keyword." << endl;
    cout << "Please select an option from below to begin (input the value 1 - 3 and press enter):" << endl;
    cout << "\n1. Encrypt Message" << endl;
    cout << "2. Decrypt Message" << endl;
    cout << "3. Exit Program" << endl;
    cin >> menuOption;
    cin.ignore();
    switch (menuOption)
    {
    case 1:
    {
        string userMsg;
        string userKeyword;
        cout << "What is the message to be encrypted?" << endl;
        cout << "Message: ";
        getline(cin, userMsg);
        cout << "What is the keyword for the encryption?" << endl;
        cout << "Keyword: ";
        getline(cin, userKeyword);
        string key = cypher.generateKey(userMsg, userKeyword);
        string encryptedMsg = cypher.encrypt(userMsg, key);
        cout << "Encrypted Message: " + encryptedMsg << endl;
        cout << "Restart the program for more encryption and decryption." << endl;
        break;
    }
        
    case 2:
    {
        string encryptedMsg;
        string keyword;
        cout << "What is the encrypted messaged to be decrypted?" << endl;
        getline(cin, encryptedMsg);
        cout << "What is the keyword?" << endl;
        getline(cin, keyword);
        string key = cypher.generateKey(encryptedMsg, keyword);
        string decryptedMsg = cypher.decrypt(encryptedMsg, key);
        cout << "Decrypted Message: " + decryptedMsg << endl;
        cout << "Restart the program for more encryption and decryption." << endl;
        break;
    }  
    case 3:
        cout << "Exiting program. . ." << endl;
    default:
        cout << "Exiting program. . ." << endl;
        break;
    }
    
    return 0;
}