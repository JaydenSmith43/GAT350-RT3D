#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 ftexcoord;

out layout(location = 0) vec2 otexcoord;

uniform struct Material
{
	vec3 albedo;

	vec2 offset;
	vec2 tiling;

} material;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	otexcoord = (ftexcoord * material.tiling) + material.offset;

	//get world position
	vec3 position = model[3].xyz;

	//get size
	vec2 size = vec2(length(model[0]), length(model[1]));

	//get view right direction
	vec3 right = vec3(view[0][0], view[1][0], view[2][0]);

	//get view up direction
	vec3 up = vec3(view[0][1], view[1][1], view[2][1]);

	//set vertex position (local) using world position and view direction
	position = position + (vposition.x * right * size.x) + (vposition.y * up * size.y);

	mat4 vp = projection * view;
	gl_Position = vp * vec4(position, 1.0);
}
