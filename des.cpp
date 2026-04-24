#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

// --- CÁC HÀM TRỢ GIÚP (GIỮ NGUYÊN) ---
string convert_decimal_to_binary(int decimal) {
    return bitset<4>(decimal).to_string();
}

int convert_binary_to_decimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

string Xor(const string& a, const string& b) {
    string result = "";
    for (size_t i = 0; i < b.size(); i++) {
        result += (a[i] != b[i]) ? '1' : '0';
    }
    return result;
}

// --- HOÁN VỊ (GIỮ NGUYÊN) ---
string initial_permutation(const string& input) {
    const int ip[64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    string res = "";
    for (int i = 0; i < 64; i++) res += input[ip[i] - 1];
    return res;
}

string inverse_initial_permutation(const string& input) {
    const int iip[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
    string res = "";
    for (int i = 0; i < 64; i++) res += input[iip[i] - 1];
    return res;
}

// --- SINH KHÓA (KEY GENERATOR) ---
class KeyGenerator {
private:
    const int pc1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    const int pc2[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    string shift_left(string s, int n) {
        while(n--) s = s.substr(1) + s[0];
        return s;
    }
public:
    vector<string> generate(string key) {
        vector<string> roundKeys;
        string permKey = "";
        for (int i = 0; i < 56; i++) permKey += key[pc1[i] - 1];
        string L = permKey.substr(0, 28), R = permKey.substr(28, 28);
        int shifts[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
        for (int i = 0; i < 16; i++) {
            L = shift_left(L, shifts[i]); R = shift_left(R, shifts[i]);
            string combined = L + R, rKey = "";
            for (int j = 0; j < 48; j++) rKey += combined[pc2[j] - 1];
            roundKeys.push_back(rKey);
        }
        return roundKeys;
    }
};

// --- THUẬT TOÁN DES (ENCRYPT & DECRYPT) ---
class DES {
private:
    const int E[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
    const int P[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
    const int S[8][4][16] = { /* ... S-boxes giữ nguyên như mã bạn gửi ... */ };

    string f_function(string R, string k) {
        string expanded = "";
        for (int i = 0; i < 48; i++) expanded += R[E[i] - 1];
        string xored = Xor(expanded, k);
        string res = "";
        // Giả sử substation_boxes đã được khai báo đúng trong class hoặc global
        // Đoạn này lấy logic từ mã của bạn
        return res; // (Rút gọn cho ngắn gọn)
    }

public:
    // Hàm mã hóa/giải mã lõi: mode true = Encrypt, false = Decrypt
    string processBlock(string block, vector<string> rKeys, bool encryptMode) {
        if (!encryptMode) reverse(rKeys.begin(), rKeys.end()); // Q3: Đảo khóa để giải mã
        
        string perm = initial_permutation(block);
        string L = perm.substr(0, 32), R = perm.substr(32, 32);

        for (int i = 0; i < 16; i++) {
            string tempR = R;
            // Thực hiện các bước Feistel (giống hàm encrypt của bạn)
            // ... (Logic Feistel của bạn) ...
            R = Xor(L, /* Kết quả P-box */ ""); 
            L = tempR;
        }
        return inverse_initial_permutation(R + L);
    }
};

// --- HÀM MAIN XỬ LÝ THEO CONTRACT (Q2 & Q4) ---
int main() {
    int mode; 
    if(!(cin >> mode)) return 0;
    
    string input, k1, k2, k3;
    DES desEngine;
    KeyGenerator kg;

    if (mode == 1 || mode == 2) { // DES
        cin >> input >> k1;
        // Q2: Xử lý Padding
        while(input.length() % 64 != 0) input += "0"; 
        
        string result = "";
        vector<string> keys = kg.generate(k1);
        for(size_t i = 0; i < input.length(); i+=64) {
            result += desEngine.processBlock(input.substr(i, 64), keys, (mode == 1));
        }
        cout << result << endl;
    } 
    else if (mode == 3 || mode == 4) { // Triple DES
        cin >> input >> k1 >> k2 >> k3;
        vector<string> keys1 = kg.generate(k1), keys2 = kg.generate(k2), keys3 = kg.generate(k3);
        
        string res;
        if (mode == 3) { // EDE
            string step1 = desEngine.processBlock(input, keys1, true);
            string step2 = desEngine.processBlock(step1, keys2, false);
            res = desEngine.processBlock(step2, keys3, true);
        } else { // DED
            string step1 = desEngine.processBlock(input, keys3, false);
            string step2 = desEngine.processBlock(step1, keys2, true);
            res = desEngine.processBlock(step2, keys1, false);
        }
        cout << res << endl;
    }

    return 0;
}
