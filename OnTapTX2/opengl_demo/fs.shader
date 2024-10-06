#version 460

in vec3
position_eye,
normal_eye;

uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color;

void main() {
	//-----------ch? ð?nh các v? trí-------------
		// v? trí ngu?n sáng trong th? gi?i
	vec3 light_position_world = vec3(0.0, 0.0, 2.0);
	// bi?n ð?i v? trí ngu?n sáng sang eye space
	vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 1.0));

	// v? trí viewer
	vec3 postion_viewer = vec3(0.0, 0.0, 0.0);

	// chu?n hóa normal_eye
	vec3 n_eye = normalize(normal_eye);

	// tính vector kho?ng cách t? ngu?n sáng ð?n m?t
	// hý?ng vector hý?ng t? vertex ð?n ngu?n sáng
	// = v? trí Light - v? trí Vertex
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	// chu?n hóa vector kho?ng cách t? ngu?n sáng ð?n m?t
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);

	// tính vector kho?ng cách v? trí viewer và vertex
	// = v? trí viewer - v? trí vertex
	vec3 surface_to_viewer_eye = postion_viewer - position_eye;
	// chu?n hóa	
	surface_to_viewer_eye = normalize(surface_to_viewer_eye);

	// --------------cý?ng ð? ánh sáng khu?ch tán-----------------------
		// tính cosin góc gi?a vector hý?ng ánh sáng và vector pháp tuy?n: l.n
	float dot_prod = dot(direction_to_light_eye, n_eye);
	// l?y giá tr? >=0 ð? lo?i b? giá tr? âm ?ng v?i góc >90 ð?
	dot_prod = max(dot_prod, 0.0);

	// cý?ng ð? ánh sáng ð?n
	// màu tr?ng m?
	vec3 Ld = vec3(0.7, 0.7, 0.7);

	// h? s? ph?n x? khu?ch tán
	// màu cam
	vec3 Kd = vec3(1.0, 0.5, 0.0);

	// cý?ng ð? ánh sáng khu?ch tán cu?i cùng
	vec3 Id = Ld * Kd * dot_prod;

	// -----------------cý?ng ð? ánh sáng ph?n x?-------------------		
	// blinn	
		// tính vector half way
	vec3 half_way_eye = surface_to_viewer_eye + direction_to_light_eye;
	// chu?n hóa vector half way
	half_way_eye = normalize(half_way_eye);

	// tính cosin góc gi?a vector half_way_eye và vector pháp tuy?n: n.h
	float dot_prod_specular = dot(half_way_eye, n_eye);
	// l?y giá tr? >=0 ð? lo?i b? giá tr? âm ?ng v?i góc >90 ð?
	dot_prod_specular = max(dot_prod_specular, 0.0);

	// h? s? sáng bóng
	float specular_exponent = 100.0;
	// tính m? v?i h? s? sáng bóng
	float specular_factor = pow(dot_prod_specular, specular_exponent);

	// ánh sáng ph?n x?
	// màu tr?ng
	vec3 Ls = vec3(1.0, 1.0, 1.0);

	// h? s? ph?n x?
	// ph?n x? toàn ph?n, màu tr?ng
	vec3 Ks = vec3(1.0, 1.0, 1.0);

	// cý?ng ð? ánh sáng ph?n x? cu?i cùng
	vec3 Is = Ls * Ks * specular_factor;

	// --------------cý?ng ð? ánh sáng môi trý?ng---------------
		// ánh sáng môi trý?ng
		// màu xám
	vec3 La = vec3(0.2, 0.2, 0.2);

	// h? s? môi trý?ng
	// ph?n chi?u hoàn toàn
	vec3 Ka = vec3(1.0, 1.0, 1.0);

	// cý?ng ð? ánh sáng môi trý?ng cu?i cùng
	vec3 Ia = La * Ka;

	// ------------mau cuoi cung------------
	//out_color = fragment_color;
	//out_color = vec4(Is + Id + Ia, 1.0);
	out_color = vec4(Is + Id + Ia, 1.0) * fragment_color;
}
