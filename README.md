# Hệ Thống Quản Lý Tài Khoản

Hệ thống quản lý tài khoản đơn giản được viết bằng C++, cho phép người dùng đăng ký tài khoản, đăng nhập, quản lý điểm số và chuyển điểm giữa các người dùng trong hệ thống.

## Tính Năng

### Người Dùng Thông Thường
- Đăng ký tài khoản mới
- Đăng nhập vào hệ thống
- Xem số điểm hiện tại
- Đổi tên tài khoản
- Đổi mật khẩu
- Chuyển điểm cho người dùng khác
- Đăng xuất

### Quản Trị Viên (Admin)
- Đăng nhập với tài khoản admin (adminadminpass)
- Hiển thị danh sách tất cả tài khoản
- Thêm mới người dùng
- Xóa tài khoản người dùng

## Cấu Trúc Dự Án

### Lớp Account
Lớp này đại diện cho một tài khoản người dùng trong hệ thống:
- Lưu trữ tên người dùng, mật khẩu đã được mã hóa và số điểm
- Cung cấp phương thức xác thực người dùng

### Lớp AccountManager
Lớp này quản lý tất cả tài khoản trong hệ thống:
- Lưu trữ tài khoản trong một unordered_map
- Đọc/ghi dữ liệu tài khoản từ/vào tệp
- Quản lý đăng ký và đăng nhập người dùng
- Quản lý chuyển điểm giữa các tài khoản
- Ghi nhật ký các giao dịch chuyển điểm

## Cách Sử Dụng

### Biên Dịch

```bash
g++ -o account_system account_system.cpp -std=c++11
```

### Chạy Chương Trình

```bash
./account_system
```

### Menu Chính
Khi chạy chương trình, bạn sẽ thấy menu chính với các lựa chọn:
1. Đăng ký
2. Đăng nhập người dùng
3. Đăng nhập admin
4. Thoát

### Đăng Nhập Admin
- Tên đăng nhập: admin
- Mật khẩu: adminpass

## Lưu Trữ Dữ Liệu

Dữ liệu tài khoản được lưu trữ trong tệp `./data/accounts_data.txt`

Nhật ký giao dịch được lưu trữ trong tệp `./transaction_logs/trannsactions.log`

## Bảo Mật

- Mật khẩu được mã hóa (hash) trước khi lưu trữ
- Hệ thống xác thực người dùng trước khi cho phép thực hiện các hành động
- Các ràng buộc được áp dụng để đảm bảo giao dịch hợp lệ (ví dụ: không thể chuyển điểm cho chính mình, không thể chuyển số điểm lớn hơn số điểm hiện có, v.v.)

## Điểm Mở Rộng Trong Tương Lai

1. Thêm giao diện đồ họa người dùng
2. Bổ sung thêm các loại giao dịch khác
3. Cải thiện tính năng bảo mật (mã hóa mạnh hơn, xác thực hai yếu tố)
4. Thêm tính năng khôi phục mật khẩu
5. Thêm các cấp quyền người dùng khác nhau