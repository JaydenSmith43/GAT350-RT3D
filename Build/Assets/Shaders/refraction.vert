#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out layout(location = 0) vec3 otexcoord;

uniform float ior = 1.55;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 vreflect(vec3 i, vec3 n)
{
	return i - (n * dot(n, i)) * 2;
}

void main()
{
	//transform vertex position/normal to world space
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	//inverse will convert from viewspace to world space
	//last column of mat4 is position
	vec3 viewPosition = inverse(view)[3].xyz; //swizzle: reorganizing elements together, 

	vec3 viewDir = normalize(position - viewPosition);

	//refract viewDir about vertex normal using index of refraction
	otexcoord = refract(viewDir, normal, 1.0 / ior); //1 is air

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(position, 1.0);
}
