// khai báo phiên bản 4.6
#version 460

// biến đầu vào
// nhận dữ giá trị từ vertex shader
in vec4 fragment_color;

// biến đầu ra
out vec4 out_Color;

void main(void)
{
	// lấy màu cho đầu ra
	out_Color = fragment_color;
}


