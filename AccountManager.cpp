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

void AccountManager::saveToFile(const string &filename) const {
    ofstream ofs(filename);
    if (!ofs) {
        cout << "Không thể mở file để lưu dữ liệu!\n";
        return;
    }
    for (const auto &entry : accounts) {
        ofs << entry.second.username << " " 
            << entry.second.passwordHashed << " " 
            << entry.second.wallet.points << "\n";
    }
    ofs.close();
    cout << "Dữ liệu đã được lưu vào file: " << filename << "\n";
}

void AccountManager::loadFromFile(const string &filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cout << "File dữ liệu không tồn tại. Khởi tạo hệ thống mới.\n";
        return;
    }
    string line;
    while (getline(ifs, line)) {
        if (line.empty())
            continue;
        istringstream iss(line);
        string uname, pwdHashed;
        int pts;
        if (!(iss >> uname >> pwdHashed >> pts))
            continue;
        Account acc;
        acc.username = uname;
        acc.passwordHashed = pwdHashed;
        acc.wallet.points = pts;
        accounts[uname] = acc;
    }
    ifs.close();
    cout << "Dữ liệu đã được tải từ file: " << filename << "\n";
}