#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "Account.h"
#include <unordered_map>
#include <string>

class AccountManager {
private:
    std::unordered_map<std::string, Account> accounts; // key là username
public:
    // Các hàm nghiệp vụ dành cho người dùng
    bool registerAccount(const std::string &uname, const std::string &password);
    Account* login(const std::string &uname, const std::string &password);
    bool transferPoints(const std::string &sender, const std::string &recipient, int amount);
    Account* changeUsername(const std::string &oldUname, const std::string &newUname);
    bool changePassword(const std::string &uname, const std::string &newPassword);
    
    // Các hàm hỗ trợ admin
    void displayAllAccounts() const;
    bool removeAccount(const std::string &uname);
    
    // Các hàm lưu/tải dữ liệu từ file
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
    
    // Hiển thị thông tin một tài khoản
    void displayAccount(const std::string &uname) const;
};

#endif // ACCOUNT_MANAGER_H
