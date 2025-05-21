#include "headers/account_manager.h"
#include <iostream>
#include <limits>
using namespace std;

void userMenu(AccountManager &am, Account* currentUser) {
    int choice;
    do {
        cout << "\n==== MENU NGƯỜI DÙNG ====\n";
        cout << "1. Xem số điểm\n";
        cout << "2. Đổi tên tài khoản\n";
        cout << "3. Đổi mật khẩu\n";
        cout << "4. Chuyển điểm cho người khác\n";
        cout << "5. Đăng xuất\n";
        cout << "Chọn một tùy chọn: ";
        cin >> choice;
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1:
                cout << "Số điểm hiện tại: " << currentUser->wallet.points << "\n";
                break;
            case 2: {
                string newUname;
                cout << "Nhập tên đăng nhập mới: ";
                cin >> newUname;
                Account* updated = am.changeUsername(currentUser->username, newUname);
                if (updated)
                    currentUser = updated;
                break;
            }
            case 3: {
                string newPwd;
                cout << "Nhập mật khẩu mới: ";
                cin >> newPwd;
                am.changePassword(currentUser->username, newPwd);
                break;
            }
            case 4: {
                string recipient;
                int amount;
                cout << "Nhập tên người nhận: ";
                cin >> recipient;
                cout << "Nhập số điểm muốn chuyển: ";
                cin >> amount;
                am.transferPoints(currentUser->username, recipient, amount);
                break;
            }
            case 5:
                cout << "Đăng xuất thành công!\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
                break;
        }
    } while (choice != 5);
}

void adminMenu(AccountManager &am) {
    int choice;
    do {
        cout << "\n==== MENU ADMIN ====\n";
        cout << "1. Hiển thị danh sách tài khoản\n";
        cout << "2. Thêm mới người dùng\n";
        cout << "3. Xóa tài khoản\n";
        cout << "4. Quay lại\n";
        cout << "Chọn một tùy chọn: ";
        cin >> choice;
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1:
                am.displayAllAccounts();
                break;
            case 2: {
                string uname, pwd;
                cout << "Nhập tên tài khoản mới: ";
                cin >> uname;
                cout << "Nhập mật khẩu: ";
                cin >> pwd;
                if (am.registerAccount(uname, pwd))
                    cout << "Tài khoản mới được tạo thành công.\n";
                break;
            }
            case 3: {
                string uname;
                cout << "Nhập tên tài khoản cần xóa: ";
                cin >> uname;
                am.removeAccount(uname);
                break;
            }
            case 4:
                cout << "Quay lại menu chính.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
                break;
        }
    } while (choice != 4);
}

void mainMenu() {
    AccountManager am;
    const string filename = "./data/accounts_data.txt";
    am.loadFromFile(filename);
    int choice;
    do {
        cout << "\n==== MENU CHÍNH ====\n";
        cout << "1. Đăng ký\n";
        cout << "2. Đăng nhập người dùng\n";
        cout << "3. Đăng nhập admin\n";
        cout << "4. Thoát\n";
        cout << "Chọn một tùy chọn: ";
        cin >> choice;
        if (!cin) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: {
                string uname, pwd;
                cout << "Nhập tên đăng nhập: ";
                cin >> uname;
                cout << "Nhập mật khẩu: ";
                cin >> pwd;
                if (am.registerAccount(uname, pwd))
                    am.saveToFile(filename);
                break;
            }
            case 2: {
                string uname, pwd;
                cout << "Nhập tên đăng nhập: ";
                cin >> uname;
                cout << "Nhập mật khẩu: ";
                cin >> pwd;
                Account* currentUser = am.login(uname, pwd);
                if (currentUser) {
                    userMenu(am, currentUser);
                    am.saveToFile(filename);
                }
                break;
            }
            case 3: {
                string uname, pwd;
                cout << "Nhập tên admin: ";
                cin >> uname;
                cout << "Nhập mật khẩu admin: ";
                cin >> pwd;
                if (uname == "admin" && pwd == "adminpass") {
                    cout << "Đăng nhập admin thành công!\n";
                    adminMenu(am);
                    am.saveToFile(filename);
                } else {
                    cout << "Thông tin admin không chính xác!\n";
                }
                break;
            }
            case 4:
                cout << "Thoát hệ thống.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
                break;
        }
    } while (choice != 4);
    am.saveToFile(filename);
}

int main() {
    mainMenu();
    return 0;
}
