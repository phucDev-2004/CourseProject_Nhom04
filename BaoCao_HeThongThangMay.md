# BÁO CÁO BÀI TẬP LỚN: MÔ PHỎNG HỆ THỐNG QUẢN LÝ THANG MÁY
**Môn học:** Cấu trúc dữ liệu và Giải thuật (DSA)
**Nhóm thực hiện:** Nhóm 04

---

## 1. MÔ TẢ ĐỀ TÀI
Đề tài xây dựng một chương trình mô phỏng quá trình hoạt động và lập lịch di chuyển của một thang máy trong tòa nhà dựa trên các yêu cầu (request) của hành khách. Mục tiêu của hệ thống là tối ưu hóa quãng đường di chuyển của thang máy, đảm bảo đưa đón khách hợp lý, tuân thủ giới hạn về tải trọng, và không để xảy ra tình trạng đói (starvation) yêu cầu.

## 2. CẤU TRÚC DỮ LIỆU ĐƯỢC SỬ DỤNG
Hệ thống sử dụng các cấu trúc dữ liệu cốt lõi sau để giải quyết bài toán:

### 2.1. Hàng đợi ưu tiên (Priority Queue - cài đặt bằng Heap trên Mảng)
Thay vì sử dụng hàng đợi FIFO thông thường, hệ thống chia các yêu cầu chờ ở các tầng thành 2 hàng đợi ưu tiên nhằm tối ưu quá trình đón khách theo từng chiều di chuyển:
- **UpQueue (Min-Heap):** Quản lý danh sách khách hàng có nhu cầu đi **LÊN**. Min-Heap đảm bảo khách hàng ở tầng thấp nhất (gần nhất với thang máy đang đi lên) sẽ được lấy ra (pop) đầu tiên.
- **DownQueue (Max-Heap):** Quản lý danh sách khách hàng có nhu cầu đi **XUỐNG**. Max-Heap đảm bảo khách hàng ở tầng cao nhất (gần nhất với thang máy đang đi xuống) sẽ được lấy ra đầu tiên.

### 2.2. Danh sách liên kết đơn (Singly Linked List)
- **Mục đích:** Quản lý danh sách hành khách **đang ở trong cabin** thang máy (`cabinPassengers`).
- **Ưu điểm:** Khách hàng có thể lên và xuống ở nhiều tầng khác nhau. Sử dụng LinkedList giúp thao tác thêm khách (insert) và xóa khách khi đến tầng (remove) diễn ra linh hoạt, không cần phải dịch chuyển phần tử hay cấp phát lại bộ nhớ liên tục như khi dùng mảng tĩnh.

---

## 3. THUẬT TOÁN LẬP LỊCH (LOOK ALGORITHM)
Hệ thống áp dụng thuật toán **LOOK** (một biến thể tối ưu của thuật toán SCAN thường dùng trong lập lịch đĩa/thang máy).
- **Hoạt động cốt lõi:** Thang máy di chuyển theo một hướng cố định (LÊN hoặc XUỐNG). Trên đường đi, thang sẽ dừng lại để đón những khách cùng chiều và trả khách nếu đến tầng đích.
- **Đổi hướng thông minh:** Khác với SCAN (phải chạy đến tầng cao nhất hoặc thấp nhất của tòa nhà rồi mới quay đầu), thuật toán LOOK có khả năng "nhìn" (look ahead) vào danh sách yêu cầu. Thang máy sẽ đổi hướng ngay lập tức nếu không còn hành khách nào ở phía trước (cả trong cabin lẫn người đang chờ ngoài sảnh) theo hướng hiện tại.

---

## 4. PHẠM VI VÀ GIỚI HẠN CỦA ĐỀ TÀI (SCOPE & LIMITATIONS)
Để đảm bảo tính khả thi trong khuôn khổ bài tập môn học, hệ thống được thiết kế với các phạm vi và ràng buộc cụ thể như sau:

### 4.1. Những tính năng đã hoàn thiện (In-Scope)
- **Mô phỏng thuật toán LOOK chính xác:** Xử lý chuẩn xác việc đón khách, trả khách, và đổi hướng thông minh không bị dư thừa quãng đường.
- **Quản lý quá tải (Capacity/Weight Management):** Thang máy có giới hạn tải trọng (kg). Khi số lượng khách vượt quá tải trọng, hệ thống sẽ từ chối đưa thêm khách vào cabin; khách bị từ chối sẽ tự động được trả lại vào hàng đợi chờ để phục vụ ở lượt sau.
- **Cấu trúc 2 Queue độc lập:** Tránh được tình trạng quét mảng liên tục. Thang đi hướng nào chỉ cần tương tác lấy khách từ Queue của hướng đó.
- **Nguồn dữ liệu:** Cho phép đọc các thông số (tải trọng, tầng khởi tạo, danh sách các request) trực tiếp từ File Text định dạng chuẩn (`TestData_04.txt`, `DemoData_04.txt`).
- **UI Console chi tiết:** In ra đầy đủ tiến trình chạy, tải trọng thay đổi, log sự kiện trả/đón khách, và trạng thái thang máy tại các thời điểm quan trọng.

### 4.2. Những điểm giới hạn / Ràng buộc (Out-of-Scope / Limitations)
- **Hệ thống đơn thang (Single Elevator):** Chỉ mô phỏng một buồng thang máy duy nhất. Chưa hỗ trợ việc điều phối thuật toán phân chia công việc cho cụm nhiều thang máy (Multi-elevator scheduling).
- **Mô phỏng Offline (Static Simulation):** Toàn bộ các yêu cầu của hành khách được nạp một lần từ đầu chương trình thông qua file text. Hệ thống chưa hỗ trợ mô phỏng thời gian thực (Real-time/Online), tức là không có cơ chế thêm người chờ ngẫu nhiên trong lúc thang đang chạy.
- **Không mô phỏng thời gian thực tế:** Hệ thống chạy theo các "bước logic" (steps) thay vì giả lập độ trễ thời gian vật lý (thời gian đóng/mở cửa, số giây di chuyển qua từng tầng, thời gian chờ của khách).
- **Cấu trúc dữ liệu tĩnh một phần:** Danh sách Heap trong `PriorityQueue` đang được cấp phát mảng cố định với sức chứa (capacity) là 100 phần tử, do đó chưa hỗ trợ linh hoạt cho tập dữ liệu có số lượng yêu cầu khổng lồ (>100).
- **Bỏ qua kích thước (thể tích) cabin:** Chỉ xét giới hạn về mặt trọng lượng (Cân nặng - kg), giả định trong buồng thang luôn đủ diện tích đứng cho khách nếu chưa vượt mốc số kg giới hạn.

---

## 5. TỔNG KẾT
Chương trình đã vận dụng thành công và kết hợp tốt các cấu trúc dữ liệu (`LinkedList`, `Heap/Priority Queue`) vào một bài toán thực tế. Thuật toán phân luồng LOOK với thiết kế 2 hàng đợi Up/Down riêng biệt đã giúp tăng hiệu suất tìm kiếm người cần phục vụ, ngăn chặn các vòng lặp vô ích và phản ánh tương đối chính xác hoạt động của một thang máy tiêu chuẩn. Đề tài đạt được đầy đủ các mục tiêu trong phạm vi ràng buộc đã đề ra.
