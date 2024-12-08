#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring> // Thư viện hỗ trợ xử lý chuỗi kiểu C

using namespace std;

// **Lớp Room**: Đại diện cho một phòng trong khách sạn.
class Room {
private:
    int roomNumber;         // Số phòng
    string roomType;        // Loại phòng (single, double, suite, etc.)
    bool isBooked;          // Trạng thái đặt phòng (true nếu đã đặt)
    string guestName;       // Tên khách hàng nếu phòng đã được đặt

public:
    // **Hàm khởi tạo Room**
    Room(int number, const string& type)
        : roomNumber(number), roomType(type), isBooked(false), guestName("") {}

    // **Getter:** Lấy thông tin phòng
    int getRoomNumber() const { return roomNumber; }
    string getRoomType() const { return roomType; }
    bool getIsBooked() const { return isBooked; }
    string getGuestName() const { return guestName; }

    // **Hàm đặt phòng**
    void bookRoom(const string& guest) {
        if (!isBooked) {
            isBooked = true;
            guestName = guest;
            cout << "Phòng " << roomNumber << " đã được đặt bởi " << guest << ".\n";
        } else {
            cout << "Phòng " << roomNumber << " đã được đặt trước đó.\n";
        }
    }

    // **Hàm hủy đặt phòng**
    void cancelBooking() {
        if (isBooked) {
            isBooked = false;
            guestName = "";
            cout << "Phòng " << roomNumber << " đã hủy đặt thành công.\n";
        } else {
            cout << "Phòng " << roomNumber << " hiện chưa được đặt.\n";
        }
    }

    // **Hàm cập nhật tên khách**
    void updateGuestName(const string& newName) {
        if (isBooked) {
            guestName = newName;
            cout << "Tên khách của phòng " << roomNumber << " đã được cập nhật thành " << newName << ".\n";
        } else {
            cout << "Phòng " << roomNumber << " chưa được đặt, không thể cập nhật tên khách.\n";
        }
    }
};

// **Lớp Hotel**: Quản lý danh sách các phòng trong khách sạn.
class Hotel {
private:
    vector<Room> rooms; // Danh sách các phòng trong khách sạn

public:
    // **Hàm khởi tạo Hotel**
    Hotel(const vector<pair<int, string>>& roomList) {
        for (const auto& roomInfo : roomList) {
            rooms.emplace_back(roomInfo.first, roomInfo.second);
        }
    }

    // **Hiển thị danh sách phòng**
    void viewRooms() const {
        cout << "\n--- Danh sách phòng ---\n";
        cout << setw(10) << "Phòng" << setw(15) << "Loại"
             << setw(15) << "Trạng thái" << setw(20) << "Khách hàng\n";

        for (const auto& room : rooms) {
            cout << setw(10) << room.getRoomNumber()
                 << setw(15) << room.getRoomType()
                 << setw(15) << (room.getIsBooked() ? "Đã đặt" : "Trống")
                 << setw(20) << (room.getIsBooked() ? room.getGuestName() : "N/A") << "\n";
        }
    }

    // **Hiển thị phòng trống**
    void viewAvailableRooms() const {
        cout << "\n--- Danh sách phòng trống ---\n";
        cout << setw(10) << "Phòng" << setw(15) << "Loại\n";
        for (const auto& room : rooms) {
            if (!room.getIsBooked()) {
                cout << setw(10) << room.getRoomNumber()
                     << setw(15) << room.getRoomType() << "\n";
            }
        }
    }

    // **Đặt phòng**
    void bookRoom(int roomNumber, const string& guestName) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                room.bookRoom(guestName);
                return;
            }
        }
        cout << "Không tìm thấy phòng số " << roomNumber << ".\n";
    }

    // **Hủy đặt phòng**
    void cancelBooking(int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                room.cancelBooking();
                return;
            }
        }
        cout << "Không tìm thấy phòng số " << roomNumber << ".\n";
    }

    // **Cập nhật tên khách hàng**
    void updateGuestName(int roomNumber, const string& newName) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                room.updateGuestName(newName);
                return;
            }
        }
        cout << "Không tìm thấy phòng số " << roomNumber << ".\n";
    }

    // **Trả phòng (check-out)**
    void checkOutRoom(int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                if (room.getIsBooked()) { // Nếu phòng đã đặt
                    room.cancelBooking(); // Hủy đặt phòng
                    cout << "Phòng " << roomNumber << " đã trả và sẵn sàng đặt lại.\n";
                } else {
                    cout << "Phòng " << roomNumber << " hiện đang trống.\n";
                }
                return;
            }
        }
        cout << "Không tìm thấy phòng số " << roomNumber << ".\n";
    }
};

// **Chương trình chính**
int main() {
    vector<pair<int, string>> roomList = {
        {101, "Single"}, {102, "Double"}, {201, "Suite"}, {202, "Double"}, {301, "Single"}
    };

    Hotel myHotel(roomList);

    int choice;
do {
    cout << "\n--- Quản lý khách sạn ---\n";
    cout << "1. Xem danh sách phòng\n";
    cout << "2. Xem phòng trống\n";
    cout << "3. Đặt phòng\n";
    cout << "4. Hủy đặt phòng\n";
    cout << "5. Cập nhật thông tin khách\n";
    cout << "6. Trả phòng\n";  // Lựa chọn trả phòng
    cout << "7. Thoát\n";
    cout << "Nhập lựa chọn: ";
    cin >> choice;

    switch (choice) {
        case 1:
            myHotel.viewRooms();  // Hiển thị danh sách phòng
            break;
        case 2:
            myHotel.viewAvailableRooms();  // Hiển thị các phòng trống
            break;
        case 3: {
            int roomNumber;
            string guestName;
            cout << "Nhập số phòng muốn đặt: ";
            cin >> roomNumber;
            cin.ignore();
            cout << "Nhập tên khách hàng: ";
            getline(cin, guestName);
            myHotel.bookRoom(roomNumber, guestName);  // Đặt phòng
            break;
        }
        case 4: {
            int roomNumber;
            cout << "Nhập số phòng muốn hủy đặt: ";
            cin >> roomNumber;
            myHotel.cancelBooking(roomNumber);  // Hủy đặt phòng
            break;
        }
        case 5: {
            int roomNumber;
            string newName;
            cout << "Nhập số phòng muốn cập nhật thông tin khách: ";
            cin >> roomNumber;
            cin.ignore();
            cout << "Nhập tên khách mới: ";
            getline(cin, newName);
            myHotel.updateGuestName(roomNumber, newName);  // Cập nhật thông tin khách
            break;
        }
        case 6: {  // Trả phòng (không thoát chương trình)
            int roomNumber;
            cout << "Nhập số phòng muốn trả: ";
            cin >> roomNumber;
            myHotel.checkOutRoom(roomNumber);  // Trả phòng
            break;
        }
        case 7:
            cout << "Cảm ơn bạn đã sử dụng hệ thống!\n";  // Thoát chương trình
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại.\n";  // Xử lý lỗi nhập
    }
} while (choice != 7);  // Vòng lặp tiếp tục cho đến khi chọn 7 để thoát
return 0;
}