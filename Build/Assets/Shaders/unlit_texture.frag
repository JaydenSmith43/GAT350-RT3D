#version 430

//in layout(location = 0) vec3 color;
in layout(location = 1) vec2 texcoord;

out layout(location = 0) vec4 ocolor;

uniform vec4 color;

uniform vec2 offset;
uniform vec2 tiling;

layout(binding = 0) uniform sampler2D tex;

void main()
{
	vec4 texcolor = texture(tex, (texcoord * tiling) + offset); //.rgb turns into vec3 = rgb
	//if (texcolor.a < 0.8) discard; //does not put a pixel there AKA nothing, so llama will only be visible
	ocolor = texcolor * color; //removed vec4(parameter, 1) for both since it is a vec4
}
