#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
in layout(location = 3) vec3 vtangent;

out layout(location = 0) vec3 oposition;
out layout(location = 1) vec2 otexcoord;
out layout(location = 2) vec4 oshadowcoord;
out layout(location = 3) mat3 otbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 shadowVP;

uniform struct Material
{
	uint params;

	vec3 albedo;
	vec3 specular;
	vec3 emissive;
	float shininess;

	vec2 offset;
	vec2 tiling;

} material;



uniform vec3 ambientLight;

void main()
{
	otexcoord = (vtexcoord * material.tiling) + material.offset;
	mat4 modelView = view * model;
	
	// convert position and normal to world-view space
	oposition = vec3(modelView * vec4(vposition, 1));
	vec3 normal = normalize(mat3(modelView) * vnormal);
	vec3 tangent = normalize(mat3(modelView) * vtangent);
	vec3 bitangent = cross(normal, tangent);

	oshadowcoord = shadowVP * model * vec4(vposition, 1);

	otbn = mat3(tangent, bitangent, normal);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
