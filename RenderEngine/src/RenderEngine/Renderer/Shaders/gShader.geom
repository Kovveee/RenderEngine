#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

vec3 calculateNewNormals()
{
	vec4 a = gl_in[0].gl_Position - gl_in[1].gl_Position;
	vec4 b = gl_in[1].gl_Position - gl_in[2].gl_Position;
	return cross(vec3(a.x,a.y,a.z),vec3(b.x, b.y, b.z));
}

vec3 norm;

vec3 lightPos = vec3(0,6.0,15);
vec3 lightColor = vec3(1.0);
vec3 color = vec3(0,0.6,0.7);

out vec3 calculatedColor;

void main()
{
	norm = calculateNewNormals();

	vec3 ambient = lightColor * 0.2;

	vec3 lightDir1 = normalize(lightPos - vec3(gl_in[0].gl_Position));
	vec3 lightDir2 = normalize(lightPos - vec3(gl_in[1].gl_Position));
	vec3 lightDir3 = normalize(lightPos - vec3(gl_in[2].gl_Position));

	float diff = max(dot(norm ,lightDir1), 0);
	vec3 diffuse = lightColor *diff;

	calculatedColor = (diffuse + ambient) * color;

	gl_Position = projection * view * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = projection * view * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position =  projection * view * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}