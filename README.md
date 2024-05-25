# Tetris-SDL2
# 1. Self Introduction:
+ Họ và tên : Đinh Minh Vũ
+ MSV : 23020648
+ Bài tập lớn : Tetris (2324II_INT2215_21 - LTNC)

# 2. Game Introduction :
+ Tetris (tiếng Nga: Тетрис), hay còn gọi là trò chơi xếp hình, là một trò chơi điện tử đầu tiên được thiết kế và phát triển bởi nhà khoa học máy tính người Liên Xô Alexey Pajitnov
+ Trò chơi có bảy loại khối hình: I (thẳng đứng), J, L, O (vuông), S, T, Z. Ta thấy mỗi khối gạch được cấu tạo từ 4 hình vuông nhỏ xếp lại với nhau.
+ Các hình khác được tạo ra khi xoay các khối cơ bản này các góc tương ứng 90 độ, 180 độ, 270 độ.
+ Mục tiêu của trò chơi là di chuyển các khối gạch đang rơi từ từ xuống trong kích thước hình chữ nhật 20 hàng x 10 cột (trên màn hình). Chỗ nào có gạch rồi thì không di chuyển được tới vị trí đó. Người chơi xếp những khối hình sao cho khối hình lấp đầy 1 hàng ngang để ghi điểm và hàng ngang ấy sẽ biến mất.

![Tetris_Boxshot](https://github.com/MinhVuNateHiggers/Tetris-SDL2/assets/162534780/24f2b22e-0679-4739-b2dc-d205922d33e2)



# ***Control:***
Enter : Chơi game

↑ : Xoay các khối theo chiều kim đồng hồ

← → : Di chuyển sang trái và phải

↓ : Di chuyển xuống dưới 1 ô

Spacebar : Thả khối hình xuống chỗ sâu nhất

M : Tắt/Bật nhạc nền

Esc : Thoát game

# 3. Hướng dẫn cài đặt 

*Tải file zip rồi giải nén vào 1 thư mục tự chọn*
*Sau đó mở project bằng CodeBlocks ( Đã cài đặt thư viện SDL2, SDL_mixer, SDL_ttf )*

# Extras
***Nguồn tham khảo :***

+ Core logic của game và công thức xoay các khối hình được tham khảo từ kênh youtube [Yearning](https://www.youtube.com/@YearningCpp) và [Kisielewski]
+ Sử dụng AI (Chat GPT) để sửa lỗi và tối ưu hoá các đoạn code
+ Âm thanh và phông chữ tìm kiếm trên Google

***Kế hoạch cải thiện trong tương lai***
+ Thiết kế thêm pause menu
+ Thêm hình ảnh cho game thêm sống động (Thiết kế lại Menu và màn hình Game Over )
+ Thêm các hiệu ứng âm thanh trong việc di chuyển và hạ thẳng xuống
+ Thêm các chế độ chơi mới cụ thể như là trong một thời gian nhất định phải giải xong 1 hay nhiều hàng


