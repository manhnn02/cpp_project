#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <functional>
using namespace std;

// Hàm băm mật khẩu (chỉ mang tính minh họa; không dùng cho bảo mật cao)
inline string hashPassword(const string &password) {
    return to_string(hash<string>{}(password));
}

//--- Cấu trúc dữ liệu ---
struct Wallet {
    int points;
    Wallet() : points(0) {}  // khởi tạo mặc định số điểm = 0
};

struct Account {
    string username;
    string passwordHashed;  // lưu mật khẩu đã băm
    Wallet wallet;
    
    Account() {}
    
    // Khởi tạo tài khoản, mật khẩu được chuyển qua dạng băm
    Account(const string &uname, const string &password)
        : username(uname), passwordHashed(hashPassword(password)) {}
    
    // Hàm xác thực: so sánh username và băm lại mật khẩu đầu vào
    bool authenticate(const string &uname, const string &password) const {
        return uname == username && passwordHashed == hashPassword(password);
    }
};

#endif // ACCOUNT_H
