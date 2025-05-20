#include "AccountManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

bool AccountManager::registerAccount(const string &uname, const string &password) {
    if (accounts.find(uname) != accounts.end()) {
        cout << "Tên đăng nhập đã tồn tại!\n";
        return false;
    }
    accounts[uname] = Account(uname, password);
    cout << "Đăng ký tài khoản thành công!\n";
    return true;
}

Account* AccountManager::login(const string &uname, const string &password) {
    auto it = accounts.find(uname);
    if (it != accounts.end() && it->second.authenticate(uname, password)) {
        cout << "Đăng nhập thành công!\n";
        return &(it->second);
    }
    cout << "Sai tên đăng nhập hoặc mật khẩu!\n";
    return nullptr;
}

Account* AccountManager::changeUsername(const string &oldUname, const string &newUname) {
    if (accounts.find(newUname) != accounts.end()) {
        cout << "Tên đăng nhập " << newUname << " đã tồn tại!\n";
        return nullptr;
    }
    auto it = accounts.find(oldUname);
    if (it == accounts.end()) {
        cout << "Không tìm thấy tài khoản " << oldUname << "\n";
        return nullptr;
    }
    Account updated = it->second;
    updated.username = newUname;
    accounts.erase(it);
    accounts[newUname] = updated;
    cout << "Đổi tên tài khoản thành công! Tên mới: " << newUname << "\n";
    return &accounts[newUname];
}

bool AccountManager::changePassword(const string &uname, const string &newPassword) {
    auto it = accounts.find(uname);
    if (it == accounts.end()) {
        cout << "Không tìm thấy tài khoản " << uname << "\n";
        return false;
    }
    it->second.passwordHashed = hashPassword(newPassword);
    cout << "Đổi mật khẩu thành công!\n";
    return true;
}
