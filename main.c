/* =========================================================
 * Ten file : main.c
 * Mo ta    : Dinh nghia bien toan cuc, ham main va menu chinh.
 * Bien dich: gcc -Wall main.c xuly.c hienthi.c -o baixe -lm
 * ========================================================= */
#include "quanlybaixe.h"

/* ---------- Bien toan cuc ---------- */
int gridOTo[ROW_OTO][COL_OTO] = {0};
int gridXeMay[ROW_XEMAY][COL_XEMAY] = {0};
TheXe danhSachThe[MAX_XE];
int tongSoXeAcc = 0;
long long tongDoanhThu = 0;
int tongLuotXeHoanThanh = 0;

/* 80 ma tinh/thanh pho hop le */
const int MA_TINH_VALID[] = {
    11, 12, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
    43, 47, 48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
    66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
    76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
    86, 88, 89, 90, 92, 93, 94, 95, 97, 98
};
const int SO_LUONG_MA_TINH = sizeof(MA_TINH_VALID) / sizeof(MA_TINH_VALID[0]);

/* ---------- Ham main ---------- */
int main() {
    int luaChon;
    do {
        printf("\n========= HE THONG QUAN LY BAI DO XE THONG MINH =========\n");
        printf("1. Xe vao bai (Quet the & Dieu huong)\n");
        printf("2. Xe ra bai (Tinh phi & Giai phong o do)\n");
        printf("3. Xem so do bai do xe (Truc quan)\n");
        printf("4. Thong ke ca truc & Doanh thu\n");
        printf("0. Thoat chuong trinh\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1: xeVao(); break;
            case 2: xeRa(); break;
            case 3: hienThiSoDo(); break;
            case 4: thongKeCaTruc(); break;
            case 0: break;
            default: printf("Lua chon khong hop le, vui long thu lai!\n");
        }
    } while (luaChon != 0);
    return 0;
}
