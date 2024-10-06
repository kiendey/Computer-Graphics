// khai báo phiên bản
#version 460

// biến đầu vào vị trí và màu
// dùng nhận giá trị từ chương trình chính
layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

// biến đầu ra
// dùng để truyền giá trị sang fragment shader
out vec4 fragment_color;

// biến thống nhất
// dùng để truyền giá trị từ ứng dụng phía CPU đến shader phía GPU
// phạm vi toàn cục, duy nhất cho mỗi đối tượng chương trình
// được truy cập từ bất kỳ chương trình shader, bất kỳ giai đoạn nào
// giá trị được giữ lại cho đến khi được đặt lại
uniform mat4 model_mat_shader;

void main(void)
{
	// tính toán vị trí mới cho điểm đỉnh
	gl_Position = model_mat_shader * vertex_position;

	// lấy giá trị màu từ đầu vào để truyền sang fragment shader
	fragment_color = vertex_color;
}
