/* =========================================================
 * Ten file : hienthi.c
 * Mo ta    : Ve so do bai do va bao cao thong ke ca truc.
 * ========================================================= */
#include "quanlybaixe.h"

/* ---------- So do bai do ---------- */
void hienThiSoDo(void) {
    printf("\n================ SO DO BAI DO XE "
           "================\n");
    printf("[Loi vao bai o vi tri Hang 1, Cot 1]\n");
    printf("Ky hieu: [ . ] = O trong | [ X ] = Da co xe\n\n");

    printf("--- KHU VUC O TO ---");
    for (int i = 0; i < ROW_OTO; ++i) {
        printf("\nHang %d: ", i + 1);
        for (int j = 0; j < COL_OTO; ++j) {
            if (gridOTo[i][j] == 0) printf("[ . ] ");
            else printf("[ X ] ");
        }
    }

    printf("\n\n--- KHU VUC XE MAY ---");
    for (int i = 0; i < ROW_XEMAY; ++i) {
        printf("\nHang %d: ", i + 1);
        for (int j = 0; j < COL_XEMAY; ++j) {
            if (gridXeMay[i][j] == 0) printf("[ . ] ");
            else printf("[ X ] ");
        }
    }
    printf("\n=================================================\n");
}

/* ---------- Thong ke ca truc ---------- */
void thongKeCaTruc(void) {
    int xeMayTrongBai = 0, oToTrongBai = 0;
    for (int i = 0; i < tongSoXeAcc; i++) {
        if (danhSachThe[i].dangTrongBai) {
            if (danhSachThe[i].loaiXe == XE_MAY) xeMayTrongBai++;
            else oToTrongBai++;
        }
    }
    printf("\n================ BAO CAO CA TRUC "
           "================\n");
    printf("- So luot xe da hoan thanh gui: %d\n",
           tongLuotXeHoanThanh);
    printf("- Xe dang con trong bai: %d "
           "(Xe may: %d, O to: %d)\n",
           xeMayTrongBai + oToTrongBai,
           xeMayTrongBai, oToTrongBai);
    printf("- Tong doanh thu hien tai: %lld VND\n", tongDoanhThu);
    printf("=================================================\n");
}
