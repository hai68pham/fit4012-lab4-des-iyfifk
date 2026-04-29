# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

Mục tiêu của bài lab là tìm hiểu nguyên lý hoạt động của thuật toán mã hóa DES và TripleDES, đồng thời thực hành xây dựng chương trình mã hóa và giải mã dữ liệu nhị phân bằng ngôn ngữ C++. Thông qua bài lab, sinh viên hiểu cách hoạt động của mật mã khối, cơ chế chia block dữ liệu, xử lý khóa và áp dụng padding khi dữ liệu không đủ kích thước chuẩn.

## Cách làm / Method

Chương trình được phát triển từ file gốc `des.cpp` và bổ sung đầy đủ các chức năng cần thiết. Hệ thống hỗ trợ 4 chế độ hoạt động:

1. DES Encrypt  
2. DES Decrypt  
3. TripleDES Encrypt  
4. TripleDES Decrypt  

Chương trình nhận dữ liệu từ bàn phím thông qua `stdin` theo đúng submission contract của đề bài.

Đối với DES, dữ liệu plaintext nếu dài hơn 64 bit sẽ được chia thành nhiều block 64 bit để xử lý tuần tự. Nếu block cuối chưa đủ 64 bit thì chương trình tự động thêm số 0 ở cuối (zero padding).

Đối với TripleDES, chương trình sử dụng ba khóa độc lập K1, K2, K3 và thực hiện theo mô hình EDE:

E(K3, D(K2, E(K1, P)))

Khi giải mã, chương trình thực hiện quy trình ngược lại để khôi phục plaintext ban đầu.

Ngoài phần chương trình chính, nhóm còn xây dựng các file test shell để kiểm tra tự động những trường hợp quan trọng như mã hóa đúng, giải mã đúng, sai khóa và dữ liệu bị thay đổi.

## Kết quả / Result

Chương trình biên dịch và chạy thành công bằng các công cụ:

- `g++`
- `make`
- `cmake`

Các chức năng chính đều hoạt động đúng:

- Mã hóa DES cho 1 block dữ liệu thành công.
- Giải mã DES trả lại đúng plaintext ban đầu.
- Xử lý plaintext nhiều block chính xác.
- Zero padding hoạt động đúng với block cuối.
- TripleDES mã hóa và giải mã đúng dữ liệu đầu vào.
- Wrong key test cho kết quả khác plaintext.
- Tamper test cho kết quả giải mã sai lệch.

Ví dụ kiểm thử:

Plaintext:

10101010

Sau khi mã hóa thu được ciphertext nhị phân hợp lệ.

Sau khi giải mã bằng đúng key:

10101010

Kết quả cho thấy chương trình đảm bảo tính thuận nghịch của mã hóa đối xứng.

## Kết luận / Conclusion

Qua bài lab này, em hiểu rõ hơn cấu trúc hoạt động của thuật toán DES và TripleDES, đặc biệt là nguyên lý Feistel Network, cách sinh round keys, xử lý block dữ liệu và vai trò của padding trong mật mã khối.

Bài lab cũng giúp rèn luyện kỹ năng lập trình C++, tổ chức project trên GitHub, viết test tự động và làm việc với CI.

Hạn chế hiện tại là chương trình vẫn mang tính học thuật, chưa tối ưu hiệu năng và chưa triển khai đầy đủ chuẩn DES thương mại.

Trong tương lai có thể mở rộng bằng cách cài đặt DES chuẩn hoàn chỉnh, hỗ trợ đọc ghi file, bổ sung CBC/ECB mode và nghiên cứu các thuật toán hiện đại hơn như AES.
