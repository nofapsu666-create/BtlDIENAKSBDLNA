# Hệ thống Quản lý Bãi đỗ Ô tô & Xe máy Thông minh

**Bài tập lớn môn Kỹ thuật lập trình — Đề tài 19 — Nhóm 16**
Phân hiệu Trường Đại học Giao thông vận tải tại TP. Hồ Chí Minh, Khoa Công nghệ thông tin.

Chương trình console viết bằng ngôn ngữ C chuẩn, mô phỏng bãi gửi xe gồm hai khu vực độc lập (ô tô và xe máy). Chương trình quản lý xe vào/ra bằng mã thẻ, kiểm tra biển số, tự động chọn ô đỗ trống gần cổng nhất bằng thuật toán BFS, tính phí theo giờ thực tế, vẽ sơ đồ bãi, thống kê ca trực và ghi lịch sử ra tệp.

## Thành viên nhóm

| STT | Họ và tên | MSSV |
|---|---|---|
| 1 | Dương Công Luân | 6751071047 |
| 2 | Trịnh Chí Nhân | 6751071053 |
| 3 | Nguyễn Xuân Quảng Khánh | 6751071034 |
| 4 | Huỳnh Mạnh Khoa | 6751071036 |
| 5 | Nguyễn Trung Hiếu | 6751071021 |

## Cấu trúc mã nguồn

| Tệp | Nội dung |
|---|---|
| `quanlybaixe.h` | Hằng số, `enum LoaiXe`, `struct TheXe`, `Point`, `Queue`, khai báo biến toàn cục (`extern`) và nguyên mẫu hàm |
| `main.c` | Định nghĩa biến toàn cục, bảng mã tỉnh `MA_TINH_VALID`, hàm `main` và vòng lặp menu |
| `xuly.c` | Hàng đợi (`initQueue`, `isEmpty`, `pushQueue`, `popQueue`), kiểm tra biển số, BFS `timViTriTrongGanNhat`, `tinhPhi`, `ghiLichSuFile`, `xeVao`, `xeRa` |
| `hienthi.c` | `hienThiSoDo`, `thongKeCaTruc` |

## Biên dịch và chạy

Chỉ dùng thư viện chuẩn của C (`stdio`, `stdlib`, `string`, `time`, `math`, `ctype`).

**GCC / Linux / macOS / MinGW:**

```
gcc -Wall main.c xuly.c hienthi.c -o baixe -lm
./baixe
```

Tùy chọn `-lm` cần thiết để liên kết hàm `ceil` của `math.h`. Chương trình biên dịch không có cảnh báo với `-Wall`.

**Dev-C++:** tạo Console Application (C Project), dùng *Add to Project* thêm cả 4 tệp `quanlybaixe.h`, `main.c`, `xuly.c`, `hienthi.c`, rồi nhấn F11.

## Thông số bãi đỗ

| Khu vực | Hàng × Cột | Sức chứa |
|---|---|---|
| Ô tô | 4 × 5 | 20 chỗ |
| Xe máy | 5 × 6 | 30 chỗ |

Cổng ra vào chung nằm tại Hàng 1, Cột 1. Một phiên chạy lưu tối đa 100 lượt gửi (`MAX_XE`).

## Chức năng (menu)

| Lựa chọn | Chức năng | Hàm |
|---|---|---|
| 1 | Xe vào bãi: nhập mã thẻ, loại xe, biển số; hệ thống kiểm tra và điều hướng vị trí đỗ | `xeVao()` |
| 2 | Xe ra bãi: quét mã thẻ, tính thời gian, tính phí, giải phóng ô đỗ, ghi lịch sử | `xeRa()` |
| 3 | Xem sơ đồ bãi đỗ (`[ . ]` ô trống, `[ X ]` ô có xe) | `hienThiSoDo()` |
| 4 | Thống kê ca trực và doanh thu | `thongKeCaTruc()` |
| 0 | Thoát chương trình | |

## Quy định biển số

- Hai ký tự đầu là mã tỉnh/thành phố, phải thuộc danh sách 80 mã quy định (`MA_TINH_VALID`).
- Ô tô: đúng 1 chữ cái sê-ri (ví dụ `29A-567.89`). Xe máy: đúng 2 chữ cái (ví dụ `29AB-123.45`).
- Dấu gạch ngang `-` sau sê-ri là tùy chọn; phần số gồm 4 đến 5 chữ số, có thể chèn dấu chấm `.`.
- Tổng độ dài từ 6 đến 12 ký tự.

## Biểu phí

Thời gian gửi tính theo đồng hồ hệ thống, làm tròn lên theo giờ (tối thiểu 1 giờ). **2 giờ đầu miễn phí**; từ giờ thứ ba, mỗi giờ phụ trội tính:

| Loại xe | Đơn giá mỗi giờ phụ trội |
|---|---|
| Xe máy | 5.000 VNĐ |
| Ô tô | 10.000 VNĐ |

Công thức: `g = ceil(t)`, nếu `g <= 2` thì phí = 0, ngược lại phí = `(g - 2) × đơn giá`.

## Thuật toán chính

- **BFS tìm ô trống gần cổng nhất:** duyệt theo hàng đợi từ ô cổng (0,0), thứ tự hướng lên – xuống – trái – phải; độ phức tạp O(R × C).
- **Cấu trúc dữ liệu:** hai ma trận `gridOTo`, `gridXeMay` (0: trống, 1: có xe); mảng `danhSachThe` lưu từng lượt gửi bằng `struct TheXe`.
- **Thời gian thực:** `time`, `difftime`, `localtime`, `strftime`.

## Tệp lịch sử

Mỗi lượt xe ra được ghi thêm một dòng vào `lich_su_bai_xe.txt` (chế độ `"a"`), gồm mã thẻ, biển số, loại xe, giờ vào, giờ ra và phí. Ví dụ:

```
Ma the: P1 | Bien so: 29A-111.11 | Loai: O to | Vao: 2026-10-24 11:38:23 | Ra: 2026-10-24 14:48:23 | Phi: 20000 VND
```

## Kết quả thử nghiệm

Đã kiểm thử 18 ca (TC01–TC18) gồm xe vào/ra hợp lệ, thẻ trùng, loại xe sai, biển số sai, bãi đầy, các ca biên về phí (đúng 2 giờ, hơn 2 giờ một giây). Chi tiết trong Chương 4 của báo cáo.

## Hạn chế đã biết

Chưa xử lý nhập chữ tại menu, chưa giới hạn độ dài khi nhập chuỗi, chữ cái J vẫn được chấp nhận, chưa kiểm tra trùng biển số, dữ liệu xe đang gửi không được lưu khi thoát chương trình. Xem mục 4.3.2 của báo cáo.
