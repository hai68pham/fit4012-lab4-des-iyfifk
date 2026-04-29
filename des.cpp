#include <bits/stdc++.h>
using namespace std;

// XOR 2 chuỗi nhị phân
string xor_str(string a, string b) {
    string res = "";
    for (int i = 0; i < a.size(); i++) {
        res += (a[i] == b[i]) ? '0' : '1';
    }
    return res;
}

// Hàm giả lập DES (đơn giản hóa)
string fake_des_encrypt(string block, string key) {
    return xor_str(block, key.substr(0, block.size()));
}

string fake_des_decrypt(string block, string key) {
    return xor_str(block, key.substr(0, block.size()));
}

// Padding zero
vector<string> split_blocks(string s) {
    vector<string> blocks;
    for (int i = 0; i < s.size(); i += 64) {
        string block = s.substr(i, 64);
        while (block.size() < 64) block += '0';
        blocks.push_back(block);
    }
    return blocks;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int mode;
    cin >> mode;

    if (mode == 1) {
        string plaintext, key;
        cin >> plaintext >> key;

        vector<string> blocks = split_blocks(plaintext);
        string result = "";

        for (auto &b : blocks) {
            result += fake_des_encrypt(b, key);
        }

        cout << result << "\n";
    }

    else if (mode == 2) {
        string ciphertext, key;
        cin >> ciphertext >> key;

        vector<string> blocks = split_blocks(ciphertext);
        string result = "";

        for (auto &b : blocks) {
            result += fake_des_decrypt(b, key);
        }

        cout << result << "\n";
    }

    else if (mode == 3) {
        string p, k1, k2, k3;
        cin >> p >> k1 >> k2 >> k3;

        string step1 = fake_des_encrypt(p, k1);
        string step2 = fake_des_decrypt(step1, k2);
        string step3 = fake_des_encrypt(step2, k3);

        cout << step3 << "\n";
    }

    else if (mode == 4) {
        string c, k1, k2, k3;
        cin >> c >> k1 >> k2 >> k3;

        string step1 = fake_des_decrypt(c, k3);
        string step2 = fake_des_encrypt(step1, k2);
        string step3 = fake_des_decrypt(step2, k1);

        cout << step3 << "\n";
    }

    return 0;
}
