#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

out Surface{
	vec2 UV;
	vec3 Pos;
	vec3 Normal;
}vs_out;

uniform mat4 _Model;
uniform mat4 _ViewProjection;

void main(){
	vs_out.UV = vUV;
	vs_out.Pos = (_Model * vec4(vPos,1.0)).xyz;
	vs_out.Normal = (_Model * vec4(vNormal,0.0)).xyz;
	gl_Position = _ViewProjection * _Model * vec4(vPos,1.0);
}