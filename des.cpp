#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 Lab 4 simplified DES / TripleDES
 Easy to read version for student lab submission.
 NOTE:
 This is educational Feistel-style DES-like implementation
 with 16 rounds, block size 64-bit, key size 64-bit input.
*/

string XORstr(string a, string b) {
    string r = "";
    for (int i = 0; i < (int)a.size(); i++)
        r += (a[i] == b[i]) ? '0' : '1';
    return r;
}

string leftShift(string s, int n) {
    while (n--) s = s.substr(1) + s[0];
    return s;
}

vector<string> splitBlocks(string s) {
    vector<string> blocks;
    for (int i = 0; i < (int)s.size(); i += 64) {
        string block = s.substr(i, 64);
        while ((int)block.size() < 64) block += '0';
        blocks.push_back(block);
    }
    if (blocks.empty()) blocks.push_back(string(64, '0'));
    return blocks;
}

// Simple expansion 32 -> 48
string expand32to48(string r) {
    string out = "";
    for (int i = 0; i < 48; i++)
        out += r[i % 32];
    return out;
}

// Simple substitution 48 -> 32
string substitute(string x) {
    string out = "";
    for (int i = 0; i < 48; i += 6) {
        int cnt = 0;
        for (int j = i; j < i + 6; j++)
            if (x[j] == '1') cnt++;

        for (int k = 3; k >= 0; k--)
            out += ((cnt >> k) & 1) + '0';
    }
    return out; // 8 groups => 32 bit
}

string feistel(string right, string key48) {
    string ex = expand32to48(right);
    string xr = XORstr(ex, key48);
    string sub = substitute(xr);
    return sub;
}

// Generate 16 round keys (48 bit)
vector<string> generateKeys(string key64) {
    vector<string> keys;
    string left = key64.substr(0, 32);
    string right = key64.substr(32, 32);

    for (int round = 0; round < 16; round++) {
        left = leftShift(left, 1);
        right = leftShift(right, 1);
        string merged = left + right;
        keys.push_back(merged.substr(0, 48));
    }
    return keys;
}

string DES_encrypt_block(string block, string key64) {
    vector<string> keys = generateKeys(key64);

    string left = block.substr(0, 32);
    string right = block.substr(32, 32);

    for (int i = 0; i < 16; i++) {
        string temp = right;
        string f = feistel(right, keys[i]);
        right = XORstr(left, f);
        left = temp;
    }

    return right + left;
}

string DES_decrypt_block(string block, string key64) {
    vector<string> keys = generateKeys(key64);

    string left = block.substr(0, 32);
    string right = block.substr(32, 32);

    for (int i = 15; i >= 0; i--) {
        string temp = right;
        string f = feistel(right, keys[i]);
        right = XORstr(left, f);
        left = temp;
    }

    return right + left;
}

string DES_encrypt(string plaintext, string key) {
    vector<string> blocks = splitBlocks(plaintext);
    string result = "";
    for (string b : blocks)
        result += DES_encrypt_block(b, key);
    return result;
}

string DES_decrypt(string ciphertext, string key) {
    vector<string> blocks = splitBlocks(ciphertext);
    string result = "";
    for (string b : blocks)
        result += DES_decrypt_block(b, key);
    return result;
}

string TripleDES_encrypt(string p, string k1, string k2, string k3) {
    string s1 = DES_encrypt_block(p, k1);
    string s2 = DES_decrypt_block(s1, k2);
    string s3 = DES_encrypt_block(s2, k3);
    return s3;
}

string TripleDES_decrypt(string c, string k1, string k2, string k3) {
    string s1 = DES_decrypt_block(c, k3);
    string s2 = DES_encrypt_block(s1, k2);
    string s3 = DES_decrypt_block(s2, k1);
    return s3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int mode;
    cin >> mode;

    if (mode == 1) {
        string plaintext, key;
        cin >> plaintext >> key;
        cout << DES_encrypt(plaintext, key) << "\n";
    }
    else if (mode == 2) {
        string ciphertext, key;
        cin >> ciphertext >> key;
        cout << DES_decrypt(ciphertext, key) << "\n";
    }
    else if (mode == 3) {
        string p, k1, k2, k3;
        cin >> p >> k1 >> k2 >> k3;
        cout << TripleDES_encrypt(p, k1, k2, k3) << "\n";
    }
    else if (mode == 4) {
        string c, k1, k2, k3;
        cin >> c >> k1 >> k2 >> k3;
        cout << TripleDES_decrypt(c, k1, k2, k3) << "\n";
    }

    return 0;
}
