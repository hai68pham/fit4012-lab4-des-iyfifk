# FIT4012 - Lab 4: DES / TripleDES

## Giới thiệu

Đây là bài thực hành Lab 4 môn FIT4012 với nội dung xây dựng chương trình mô phỏng thuật toán mã hóa DES và TripleDES bằng ngôn ngữ C++.

Chương trình hỗ trợ mã hóa và giải mã dữ liệu nhị phân theo đúng yêu cầu đề bài, có xử lý nhiều block dữ liệu, zero padding, kiểm thử tự động và cấu trúc repo hoàn chỉnh.

---

## Mục tiêu bài lab

Sau khi hoàn thành bài thực hành, sinh viên có thể:

* Hiểu nguyên lý hoạt động của DES.
* Hiểu mô hình TripleDES.
* Mã hóa và giải mã dữ liệu nhị phân.
* Xử lý plaintext dài hơn 64 bit.
* Áp dụng zero padding.
* Viết test tự động.
* Tổ chức project GitHub có CI.

---

## Cấu trúc repo

.
├── des.cpp
├── README.md
├── report-1page.md
├── Makefile
├── CMakeLists.txt
├── tests/
└── logs/

---

## Chế độ hoạt động

1 = DES Encrypt
2 = DES Decrypt
3 = TripleDES Encrypt
4 = TripleDES Decrypt

---

## Cách biên dịch và chạy

### Cách 1: Dùng Makefile

```bash
make
./des
```

### Cách 2: Biên dịch trực tiếp

```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
./des
```

### Cách 3: Dùng CMake

```bash
cmake -S . -B build
cmake --build build
./build/des
```

---

## Input

Chương trình nhận dữ liệu từ bàn phím (`stdin`) theo thứ tự sau:

### Mode 1: DES Encrypt

```text
1
plaintext nhị phân
key 64-bit
```

### Mode 2: DES Decrypt

```text
2
ciphertext nhị phân
key 64-bit
```

### Mode 3: TripleDES Encrypt

```text
3
plaintext 64-bit
K1
K2
K3
```

### Mode 4: TripleDES Decrypt

```text
4
ciphertext 64-bit
K1
K2
K3
```

---

## Output

Chương trình in ra kết quả cuối cùng dưới dạng chuỗi nhị phân:

* Ciphertext sau khi mã hóa
* Plaintext sau khi giải mã

---

## Padding

Chương trình sử dụng **zero padding**:

* Nếu plaintext dài hơn 64 bit sẽ chia thành nhiều block 64 bit.
* Nếu block cuối chưa đủ 64 bit thì thêm bit `0` vào cuối.

### Hạn chế

* Không phân biệt được dữ liệu thật và bit thêm vào.
* Không phù hợp cho hệ thống thực tế.
* Chỉ dùng cho mục đích học tập.

---

## Thuật toán sử dụng

### DES

DES là thuật toán mã hóa đối xứng xử lý dữ liệu theo block 64 bit.

### TripleDES

Mã hóa:

```text
E(K3, D(K2, E(K1, P)))
```

Giải mã:

```text
D(K1, E(K2, D(K3, C)))
```

---

## Chức năng đã hoàn thành

* DES Encrypt
* DES Decrypt
* TripleDES Encrypt
* TripleDES Decrypt
* Multi-block processing
* Zero padding
* Keyboard input

---

## Tests

Thư mục `tests/` gồm:

* test_des_sample.sh
* test_encrypt_decrypt_roundtrip.sh
* test_multiblock_padding.sh
* test_tamper_negative.sh
* test_wrong_key_negative.sh

---

## Logs

Thư mục `logs/` chứa:

* Kết quả chạy chương trình
* Kết quả test
* Minh chứng đúng / sai key
* Minh chứng tamper

---

## Ethics & Safe use

* Chỉ sử dụng cho mục đích học tập.
* Không dùng để tấn công hệ thống thật.
* Không xem đây là công cụ bảo mật thương mại.
* Tôn trọng trung thực học thuật.

---

## Kết luận

Bài lab giúp sinh viên hiểu nguyên lý DES, TripleDES, xử lý block dữ liệu và rèn luyện kỹ năng lập trình C++, kiểm thử phần mềm và tổ chức project GitHub.
