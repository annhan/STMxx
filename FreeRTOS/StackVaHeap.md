Bộ nhớ Stack
-----------------

Bộ nhớ Stack được dùng khi thực hiện 1 luồng (1 thread) của chương trình. Khi ứng dụng bắt đầu được thực thi các biến cục bộ, địa chỉ hàm , biến tham chiếu đối tượng được lưu trữ trong các khối Stack, tùy theo thứ tự gọi mà các thành phần đẩy vào stack được sắp xếp theo đúng thứ tự. Khi 1 phương thức kết thúc cũng là lúc các giá trị biến và các tham chiếu đối tương được hủy bỏ — và địa chỉ hàm cũng được hủy bỏ ngay sau đó. Stack lưu trữ dung lượng thấp hơn rất nhiều so với heap
Stack: LIFO

Lưu trữ biến nguyên thủy cục bộ
Biến tham chiếu đối tượng cục bộ
Địa chi hàm
Con trỏ hàm: cái này là con trỏ tham chiếu
Bộ nhớ lưu trữ thấp hơn nhiều so với Heap, tồn tại trong thời gian ngắn



Bộ nhớ Heap
---------------

Bộ nhớ Heap dùng để cấp phát bộ nhớ cho đối tượng, biến toàn cục. Bất cứ khi nào khai báo đối tượng thì các giá trị của đối tượng  sẽ được lưu trữ trong Heap (chú ý giá trị đối tượng chứ ko phải biến tham chiếu đối tượng) và có thể truy cập bất cứ khi nào trong chương trình. Khi kết thúc 1 phương thức Heap, các biến tham chiếu đối tượng bị hủy trong stack và các tham chiếu tới các dữ liệu lưu trong Heap cũng bị hủy bỏ -> C# dùng bộ thu gom rác Gabage Collection để thực hiện kiểm tra các tham chiếu.. nếu ko còn tham chiếu nào tới biến lưu trữ trên vùng nhớ Heap sẽ được thu gom.
Heap: Cơ chế phức tạp

Lưu trữ biến nguyên thủy toàn cục
Lưu trữ đối tượng: Vùng nhớ có kiểu dữ liệu đối tượng khai báo ( trong vùng nhớ đó chứa thêm các thuộc tính giá trị là các biến được định nghĩa trong đối tượng)
Con trỏ hàm: Các con trỏ cần thiết cho việc triệu gọi các biến trong vùng nhớ Heap
Bộ nhớ tồn tại trong suốt quá trình thực thi chương trình

Stack Size FreeSTOS
-------------------

- Chinh sữa giá trị vùng nhớ stack và heap trong file statup.
- Tăng vùng nhớ Heap thì vùng nhớ stack nhỏ lại và ngược lại.
- VD 1 Tack có stack size là 128 byte stack thì nó sẽ chiếm 128*4 byte bộ nhớ RAM.
