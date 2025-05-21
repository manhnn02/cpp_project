#include "headers/account_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <ctime>
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

void AccountManager::displayAccount(const string &uname) const {
    auto it = accounts.find(uname);
    if (it != accounts.end()) {
        cout << "Thông tin tài khoản:\n";
        cout << "Tên đăng nhập: " << it->second.username << "\n";
        cout << "Số điểm: " << it->second.wallet.points << "\n";
    } else {
        cout << "Không tìm thấy tài khoản!\n";
    }
}

void AccountManager::displayAllAccounts() const {
    cout << "\nDanh sách tài khoản:\n";
    if (accounts.empty()) {
        cout << "Hiện không có tài khoản nào.\n";
        return;
    }
    for (const auto &entry : accounts) {
        cout << "Tên: " << entry.first 
             << " | Số điểm: " << entry.second.wallet.points << "\n";
    }
}

bool AccountManager::removeAccount(const string &uname) {
    auto it = accounts.find(uname);
    if (it == accounts.end()) {
        cout << "Tài khoản " << uname << " không tồn tại!\n";
        return false;
    }
    accounts.erase(it);
    cout << "Tài khoản " << uname << " đã được xóa.\n";
    return true;
}

bool AccountManager::transferPoints(const string &sender, const string &recipient, int amount) {
    if (accounts.find(sender) == accounts.end()) {
        cout << "Tài khoản gửi không tồn tại!\n";
        return false;
    }
    if (accounts.find(recipient) == accounts.end()) {
        cout << "Tài khoản nhận không tồn tại!\n";
        return false;
    }
    if (sender == recipient) {
        cout << "Không thể chuyển điểm cho chính bạn!\n";
        return false;
    }
    if (amount <= 0) {
        cout << "Số điểm chuyển phải lớn hơn 0!\n";
        return false;
    }
    if (accounts[sender].wallet.points < amount) {
        cout << "Tài khoản gửi không có đủ điểm!\n";
        return false;
    }
    
    // Thực hiện giao dịch chuyển điểm
    accounts[sender].wallet.points -= amount;
    accounts[recipient].wallet.points += amount;
    cout << "Chuyển " << amount << " điểm từ " << sender 
         << " sang " << recipient << " thành công.\n";
    
    // Ghi log giao dịch chuyển điểm
    logTransaction(sender, recipient, amount);
    return true;
}

void AccountManager::logTransaction(const string &sender, const string &recipient, int amount) {
    ofstream ofs("./transaction_logs/trannsactions.log", ios::app);  // mở file ở chế độ append
    if (!ofs) {
        cerr << "Không mở được file log!" << endl;
        return;
    }
    // Lấy thời gian hiện tại
    time_t now = time(0);
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now));
    ofs << timeStr << " - Chuyển " << amount << " điểm từ " << sender 
        << " sang " << recipient << "\n";
    ofs.close();
}
