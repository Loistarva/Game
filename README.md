# Game
 (1) 
Tên : Lê Tuấn Thành
MSV : 24021626
 (2)
Chủ đề game : game endless run hướng về phía trước theo 5 làn đường, có thể truy cập vào nhiều màn hình khác nhau
 (3) 
Ngưỡng điểm tự đánh giá : 10đ
 (4) 
các lý do : 
1. 
- sử dụng biến playing, menu và quit để xử lý các màn hình khác nhau : Menu chính, màn hình chơi game, màn hình pause game, màn hình game over
- Tự Nghĩ, Tự vẽ và tự tìm cách làm chuyển đổi trạng thái của nút bấm (default, hovering, pressed) mỗi nút lại có một màu khác nhau đều là tự vẽ
-Tự làm các phần liên quan tới thuật toán chạy, tự lên ý tưởng cho background chạy chéo, nghĩ ra cách lưu trữ texture vào vector và ánh xạ các index của vector tới từng loại kẻ địch, nút bấm. Nghĩ ra thuật toán giúp game khó dần mà vẫn giữ nhịp độ game, áp dụng phương trình đường thẳng để vẽ hình
- Tìm hiểu về phương pháp lấy random theo mt19937 giúp sinh số ngẫu nhiên tốt hơn,
nghĩ ra thuật toán giới hạn lượng kẻ địch trên màn hình số lượng kẻ địch tối thiểu với từng mốc điểm
- phần graphics có lấy từ code mẫu nhưng đã phát triển thêm, tự nạp chồng hàm ứng với nhiều mục đích khác nhau
- tự làm hoàn toàn phần Player, Button, Font, Media, background;
- chỉ nhờ AI giới thiệu các phương pháp tối ưu hơn sau khi đã cơ bản tạo một thuật toán hoạt động được hoặc nhờ AI chỉ ra những lỗi sai nghiêm trọng

2. Các nguồn tham khảo
- https://www.youtube.com/watch?v=jzasDqPmtPI - Phương pháp cố định FPS
- https://www.youtube.com/watch?v=JI5SYZMnfmE - Xem cách tổ chức code ( nhưng không hiểu và cũng không dùng nhiều)
- https://www.freepik.com/premium-vector/pixel-art-illustration-spooky-ghost-pixelated-ghost-scary-spooky-ghost-pixelated-game_86581007.htm - Hình mẫu lấy Con ma gốc để vẽ ra các con ma khác
- Nhờ AI vẽ rồi tự chỉnh sửa lại : MenuKnight, runningKnight, 2 cánh rừng
- Tham khảo nhiều tranh trên mạng rồi tự vẽ : Nút bấm
- Phần mềm sử dụng để vẽ : Aseprite

Nguồn âm Thanh :
- https://www.nhaccuatui.com/bai-hat/hopes-and-dreams-undertale-ost-toby-fox.ixcabSdknLPy.html
- https://www.nhaccuatui.com/bai-hat/memory-undertale-ost-toby-fox.tZNxYiIYrq9M.html
- https://www.nhaccuatui.com/bai-hat/save-the-world-undertale-ost-toby-fox.6fnpLTaHNXzy.html
- https://www.nhaccuatui.com/bai-hat/his-theme-undertale-ost-toby-fox.sp4bb8FkJY8j.html
- https://www.nhaccuatui.com/bai-hat/fallen-down-reprise-toby-fox.up2tKM08Ohpf.html
- https://www.nhaccuatui.com/bai-hat/once-upon-a-time-undertale-ost-toby-fox.WMrdiKnIN3FK.html
- Tất cả đều là nhạc của TobyFox

- Tiếng bị thương : https://pixabay.com/sound-effects/search/hurt/
- Tiếng click chuột : lấy từ file bài tập lớn của https://www.youtube.com/watch?v=JI5SYZMnfmE

Checklisk khi chấm bài
(danh sách dưới đây liệt kê tính năng để giáo viên dễ chấm bài chứ không có nghĩa các bạn cần làm hết mới được 10 nhé)


Dùng các lệnh vẽ hình: có

Texture : có

Background : có

Event bàn phím : có

Event chuột : có

Animation (hoạt hình) :có, có tạo hoạt ảnh chạy, hoạt ảnh chuyển làn của nhân vật, hoạt ảnh cuộn background

Xử lý va chạm ; có

Score (có tính điểm) : có

Lưu bảng điểm : có

Sound : có

Sound on off : có

Background music : có

Font : có

Menu : có

Pause/Resume : có

Status bar / lives (mạng/máu...) : có

Các điểm nổi bật khác : Quái random khó dần theo thời gian, mỗi nút có 3 trạng thái riêng biệt, có từng bản nhạc nên ứng với từng mốc điểm, thay đổi màn hình nếu đạt được HighScore

Code viết dễ đọc (gv đánh giá)

Hiểu rõ code (gv đánh giá)

