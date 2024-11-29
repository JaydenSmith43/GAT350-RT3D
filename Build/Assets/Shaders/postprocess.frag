#version 430

#define INVERT_MASK     (1 << 0)
#define GRAYSCALE_MASK  (1 << 1)
#define COLORTINT_MASK  (1 << 2)
#define GRAIN_MASK		(1 << 3)
#define SCANLINE_MASK   (1 << 4)
#define EDGE_MASK		(1 << 5)

in layout(location = 1) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;
uniform float time = 0;
uniform vec3 tint_color;

uniform int selection = 1;
uniform float offset = 1.0 / 300.0;

layout(binding = 0) uniform sampler2D screenTexture;

float random(vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 invert(in vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 grayscale(in vec4 color)
{
	return vec4(vec3( (color.r + color.b + color.g) / 3), color.a );
}

vec4 grain(in vec4 color)
{
	return color * random(gl_FragCoord.xy + time);
}

vec4 scanline(in vec4 color)
{
	return (int(gl_FragCoord.y)) % 2 != 0 ? vec4(0,0,0,0) : color;
}

vec4 tint(in vec4 color)
{
	return vec4(vec3( color.rgb * tint_color ), color.a );
}

vec4 edge(in vec4 color)
{
	vec2 offsets[9] = vec2[](
        vec2(-offset,  -offset),
        vec2( 0.0f,    -offset),
        vec2( offset,  -offset),
        vec2(-offset,   0.0f),
        vec2( 0.0f,     0.0f),
        vec2( offset,   0.0f),
        vec2(-offset,  +offset),
        vec2( 0.0f,    +offset),
        vec2( offset,   offset)
    );

	float[] kernel = float[](
	1,  1,  1,
	1, -10, 1,
	1,  1,  1
	);

	vec3 sampleTex[9];
    for(int i = 0; i < 9; i++) 
	{
        sampleTex[i] = vec3(texture(screenTexture, ftexcoord.xy + offsets[i]));
    }

	vec3 col = vec3(0.0);
	for (int i = 0; i < 9; i++) col += sampleTex[i] * kernel[i];

	return vec4(col, 1);
}


void main()
{
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;

	// 0001 <-mask
	// 0001 <-params

	if (bool(params & INVERT_MASK))    postprocess = invert(postprocess); //bit operations use a single &
	if (bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	if (bool(params & GRAIN_MASK))     postprocess = grain(postprocess);
	if (bool(params & SCANLINE_MASK))  postprocess = scanline(postprocess);
	if (bool(params & COLORTINT_MASK)) postprocess = tint(postprocess);
	if (bool(params & EDGE_MASK))	   postprocess = edge(postprocess);

	ocolor = mix(basecolor, postprocess, blend);
}
