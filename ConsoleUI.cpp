#include "ConsoleUI.h"

void hienThiMenu() {
    cout << "\n============================================================\n";
    cout << "           BANG DIEU KHIEN HE THONG THANG MAY               \n";
    cout << "============================================================\n";
    cout << "  [1] Hien thi thong tin du lieu dau vao\n";
    cout << "  [2] Nap yeu cau vao Hang doi (Priority Queue)\n";
    cout << "  [3] Xem trang thai Thang may & Hang doi hien tai\n";
    cout << "  [4] Chay mo phong he thong (Thuat toan SCAN)\n";
    cout << "  [5] Xem danh sach ket qua tra khach\n";
    cout << "  [0] Thoat chuong trinh\n";
    cout << "------------------------------------------------------------\n";
    cout << "  Vui long nhap lua chon cua ban (0-5): ";
}

void hienThiTrangThaiThangMay(int tangHienTai, string huongDiChuyen, int taiTrongHienTai, int taiTrongToiDa) {
    cout << "\n================================================\n";
    cout << "           TRANG THAI THANG MAY HIEN TAI        \n";
    cout << "================================================\n";
    cout << "  [-] Tang hien tai  : " << tangHienTai << "\n";
    cout << "  [-] Huong di chuyen: " << huongDiChuyen << "\n";
    cout << "  [-] Tai trong      : " << taiTrongHienTai << " / " << taiTrongToiDa << " kg\n";
    cout << "================================================\n";
}

void hienThiDanhSachKhach(int soLuongKhachCho, int soLuongKhachTrongThang) {
    cout << "\n------------------------------------------------------------\n";
    cout << "  [DANH SACH KHACH DANG CHO DO LUU TRONG PRIORITY QUEUE]\n";
    if (soLuongKhachCho == 0) {
        cout << "   -> Hien khong co khach nao dang cho o cac tang.\n";
    } else {
        cout << "   -> He thong dang co " << soLuongKhachCho << " yeu cau cho xu ly.\n";
    }
    
    cout << "\n  [DANH SACH KHACH TRONG CABIN LUU TRONG LINKED LIST]\n";
    if (soLuongKhachTrongThang == 0) {
        cout << "   -> Thang may dang trong, chua co hanh khach.\n";
    } else {
        cout << "   -> Thang may dang cho " << soLuongKhachTrongThang << " hanh khach.\n";
    }
    cout << "------------------------------------------------------------\n";
}
