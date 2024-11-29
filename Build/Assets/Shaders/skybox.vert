#version 430

in layout(location = 0) vec3 vposition;

out layout(location = 0) vec3 otexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	otexcoord = vposition;

	mat4 vp = projection * mat4(mat3(view));
	gl_Position = vp * vec4(vposition, 1.0);
}
