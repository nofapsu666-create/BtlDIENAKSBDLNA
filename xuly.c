/* =========================================================
 * Ten file : xuly.c
 * Mo ta    : Hang doi, kiem tra bien so, BFS tim cho trong,
 *            tinh phi, ghi lich su, xe vao, xe ra.
 * ========================================================= */
#include "quanlybaixe.h"

/* ---------- Hang doi cho BFS ---------- */
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void pushQueue(Queue *q, Point p) {
    q->data[q->rear++] = p;
}

Point popQueue(Queue *q) {
    return q->data[q->front++];
}

/* ---------- Kiem tra bien so ---------- */
int isKyTuSeriHopLe(char c) {
    c = toupper(c);
    // Cac chu cai bi loai tru: I, O, Q, R, W
    if (c == 'I' || c == 'O' || c == 'Q' ||
        c == 'R' || c == 'W') return 0;
    if (c >= 'A' && c <= 'Z') return 1;
    return 0;
}

int isMaTinhHopLe(int ma) {
    for (int i = 0; i < SO_LUONG_MA_TINH; i++) {
        if (MA_TINH_VALID[i] == ma) return 1;
    }
    return 0;
}

int kiemTraBienSoHopLe(const char *bienSo, LoaiXe loai) {
    int len = strlen(bienSo);
    if (len < 6 || len > 12) return 0;

    // 1. Kiem tra 2 chu so ma tinh
    if (!isdigit(bienSo[0]) || !isdigit(bienSo[1])) return 0;
    int maTinh = (bienSo[0]-'0')*10 + (bienSo[1]-'0');
    if (!isMaTinhHopLe(maTinh)) return 0;

    int idx = 2;
    // 2. Kiem tra se-ri chu cai theo loai xe
    if (loai == O_TO) {
        if (!isKyTuSeriHopLe(bienSo[idx])) return 0;
        idx += 1;
    } else {
        if (!isKyTuSeriHopLe(bienSo[idx]) ||
            !isKyTuSeriHopLe(bienSo[idx + 1])) return 0;
        idx += 2;
    }

    // 3. Bo qua dau gach ngang '-' neu co
    if (bienSo[idx] == '-') idx++;

    // 4. Kiem tra phan chu so con lai
    int countDigits = 0;
    while (idx < len) {
        if (isdigit(bienSo[idx])) countDigits++;
        else if (bienSo[idx] != '.') return 0;
        idx++;
    }
    if (countDigits < 4 || countDigits > 5) return 0;
    return 1;
}

/* ---------- BFS tim o trong gan cong nhat ---------- */
int timViTriTrongGanNhat(LoaiXe loai, int *outR, int *outC) {
    int maxR = (loai == O_TO) ? ROW_OTO : ROW_XEMAY;
    int maxC = (loai == O_TO) ? COL_OTO : COL_XEMAY;
    int visited[10][10] = {0};

    Queue q;
    initQueue(&q);
    Point pStart = {0, 0};
    pushQueue(&q, pStart);
    visited[0][0] = 1;

    int dr[] = {-1, 1, 0, 0};   // len, xuong, trai, phai
    int dc[] = {0, 0, -1, 1};

    while (!isEmpty(&q)) {
        Point curr = popQueue(&q);

        int isOccupied = (loai == O_TO)
            ? gridOTo[curr.r][curr.c]
            : gridXeMay[curr.r][curr.c];
        if (isOccupied == 0) {
            *outR = curr.r;
            *outC = curr.c;
            return 1;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            if (nr >= 0 && nr < maxR && nc >= 0 && nc < maxC
                && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                Point nextP = {nr, nc};
                pushQueue(&q, nextP);
            }
        }
    }
    return 0;   // khong con o trong
}

/* ---------- Tinh phi ---------- */
long long tinhPhi(LoaiXe loai, double soGio) {
    int gioTron = (int)ceil(soGio);
    if (gioTron <= 0) gioTron = 1;

    if (gioTron <= 2) {
        return 0;
    }
    int gioPhuTroi = gioTron - 2;

    if (loai == XE_MAY) {
        return (long long)gioPhuTroi * 5000;
    } else {
        return (long long)gioPhuTroi * 10000;
    }
}

/* ---------- Ghi lich su ra tep ---------- */
void ghiLichSuFile(TheXe tx, long long tienPhi) {
    FILE *f = fopen("lich_su_bai_xe.txt", "a");
    if (f != NULL) {
        char tVao[80], tRa[80];
        struct tm *tmVao = localtime(&tx.thoiGianVao);
        strftime(tVao, sizeof(tVao), "%Y-%m-%d %H:%M:%S", tmVao);
        struct tm *tmRa = localtime(&tx.thoiGianRa);
        strftime(tRa, sizeof(tRa), "%Y-%m-%d %H:%M:%S", tmRa);

        fprintf(f, "Ma the: %s | Bien so: %s | Loai: %s | "
                   "Vao: %s | Ra: %s | Phi: %lld VND\n",
                tx.maThe, tx.bienSo,
                (tx.loaiXe == O_TO ? "O to" : "Xe may"),
                tVao, tRa, tienPhi);
        fclose(f);
    }
}

/* ---------- Xe vao bai ---------- */
void xeVao(void) {
    if (tongSoXeAcc >= MAX_XE) {
        printf("\nLOI: He thong da dat gioi han "
               "luu tru du lieu!\n");
        return;
    }
    TheXe tx;
    printf("Nhap ma the xe: ");
    scanf("%s", tx.maThe);

    for (int i = 0; i < tongSoXeAcc; i++) {
        if (strcmp(danhSachThe[i].maThe, tx.maThe) == 0
            && danhSachThe[i].dangTrongBai) {
            printf("LOI: Ma the dang duoc su dung trong bai!\n");
            return;
        }
    }

    int loai;
    printf("Loai xe (1: Xe may, 2: O to): ");
    if (scanf("%d", &loai) != 1 || (loai != 1 && loai != 2)) {
        printf("LOI: Loai xe khong hop le!\n");
        while (getchar() != '\n');   // xoa bo dem nhap
        return;
    }
    tx.loaiXe = (LoaiXe)loai;

    printf("Nhap bien so xe (VD: 29A-567.89 hoac 29AB-123.45): ");
    scanf("%s", tx.bienSo);
    if (!kiemTraBienSoHopLe(tx.bienSo, tx.loaiXe)) {
        printf("LOI: Bien so xe khong hop le theo quy dinh!\n");
        printf("Luu y:\n");
        printf("- Ma tinh gom 2 chu so va phai thuoc danh sach quy dinh.\n");
        printf("- O to co 1 chu cai se-ri, xe may co 2 chu cai se-ri.\n");
        printf("- Phan so gom 4 den 5 chu so (co the co dau '-' va '.').\n");
        return;
    }

    int r, c;
    if (!timViTriTrongGanNhat(tx.loaiXe, &r, &c)) {
        printf("RAT TIEC: Khu vuc do xe nay da DAY!\n");
        return;
    }
    tx.rowPos = r;
    tx.colPos = c;
    if (tx.loaiXe == O_TO) gridOTo[r][c] = 1;
    else gridXeMay[r][c] = 1;

    tx.thoiGianVao = time(NULL);
    tx.dangTrongBai = 1;
    danhSachThe[tongSoXeAcc++] = tx;

    char timeBuf[80];
    struct tm *tmInfo = localtime(&tx.thoiGianVao);
    strftime(timeBuf, sizeof(timeBuf),
             "%Y-%m-%d %H:%M:%S", tmInfo);
    printf("=> CHAP NHAN XE VAO!\n");
    printf("- Bien so: %s (Hop le)\n", tx.bienSo);
    printf("- Thoi gian vao: %s\n", timeBuf);
    printf("- Dieu huong vi tri do: Khu %s -> Hang %d, Cot %d\n",
           (tx.loaiXe == O_TO ? "O to" : "Xe may"), r + 1, c + 1);
}

/* ---------- Xe ra bai ---------- */
void xeRa(void) {
    char maThe[20];
    printf("Quet ma the xe: ");
    scanf("%s", maThe);

    for (int i = 0; i < tongSoXeAcc; i++) {
        if (strcmp(danhSachThe[i].maThe, maThe) == 0
            && danhSachThe[i].dangTrongBai) {
            danhSachThe[i].thoiGianRa = time(NULL);
            danhSachThe[i].dangTrongBai = 0;

            if (danhSachThe[i].loaiXe == O_TO)
                gridOTo[danhSachThe[i].rowPos]
                       [danhSachThe[i].colPos] = 0;
            else
                gridXeMay[danhSachThe[i].rowPos]
                         [danhSachThe[i].colPos] = 0;

            double soGiay = difftime(danhSachThe[i].thoiGianRa,
                                     danhSachThe[i].thoiGianVao);
            double soGio = soGiay / 3600.0;

            long long tienPhi =
                tinhPhi(danhSachThe[i].loaiXe, soGio);
            tongDoanhThu += tienPhi;
            tongLuotXeHoanThanh++;

            printf("=> XAC NHAN XE RA!\n");
            printf("- Bien so: %s\n", danhSachThe[i].bienSo);
            printf("- Thoi gian gui: %.2f gio "
                   "(%d giay thuc te)\n",
                   soGio, (int)soGiay);
            printf("- Phi gui xe: %lld VND\n", tienPhi);

            ghiLichSuFile(danhSachThe[i], tienPhi);
            return;
        }
    }
    printf("LOI: Khong tim thay thong tin xe "
           "tuong ung trong bai!\n");
}
