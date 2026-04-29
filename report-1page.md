# Report 1 page - Lab 4 DES / TripleDES
## Mục tiêu

Mục tiêu của bài lab là tìm hiểu nguyên lý hoạt động của thuật toán mã hóa DES và TripleDES. Sinh viên thực hành xây dựng chương trình mã hóa, giải mã dữ liệu nhị phân, xử lý nhiều block dữ liệu và áp dụng padding cho block cuối. Qua đó hiểu rõ cách bảo vệ dữ liệu bằng mật mã khối.

## Cách làm / Method

Chương trình được viết bằng C++ và chỉnh sửa từ file code gốc `des.cpp`. Nhóm bổ sung menu chọn chế độ gồm:

1. DES Encrypt  
2. DES Decrypt  
3. TripleDES Encrypt  
4. TripleDES Decrypt  

Chương trình nhận dữ liệu từ bàn phím thông qua `stdin`. Nếu plaintext dài hơn 64 bit thì tự động chia thành nhiều block 64 bit. Block cuối nếu thiếu sẽ được thêm số 0 (zero padding).

Đối với TripleDES, chương trình thực hiện theo mô hình:

E(K3, D(K2, E(K1, P)))

Ngoài ra nhóm bổ sung các file test shell để kiểm tra tự động các trường hợp mã hóa, giải mã, sai key và thay đổi ciphertext.

## Kết quả / Result

Chương trình biên dịch và chạy thành công bằng `g++`, `make` và `cmake`.

Các test chính đã thực hiện:

- DES mã hóa dữ liệu 1 block thành công.
- DES giải mã trả lại plaintext ban đầu.
- Multi-block hoạt động đúng với zero padding.
- TripleDES mã hóa và giải mã đúng dữ liệu đầu vào.
- Wrong key test cho kết quả sai khác plaintext ban đầu.
- Tamper ciphertext test cho dữ liệu giải mã bị lỗi.

Ví dụ:

Plaintext:

10101010

Sau mã hóa thu được ciphertext nhị phân hợp lệ.

Sau giải mã bằng đúng key thu lại:

10101010

## Kết luận / Conclusion

Qua bài lab, em hiểu được nguyên lý cơ bản của DES và TripleDES, cách chia block dữ liệu, padding và kiểm tra tính đúng đắn của mã hóa đối xứng.

Hạn chế hiện tại là chương trình mới mô phỏng ở mức học tập, chưa tối ưu bảo mật và chưa áp dụng đầy đủ DES chuẩn với S-box phức tạp.

Trong tương lai có thể mở rộng bằng cách cài đặt DES chuẩn hoàn chỉnh, hỗ trợ file input/output, chế độ CBC/ECB và nâng cấp sang AES.
