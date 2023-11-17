
#version 450

out vec4 FragColor;

in Surface{
	vec2 UV;
	vec3 Pos;
	vec3 Normal;
}fs_in;

uniform sampler2D _Texture;

struct Light
{
	vec3 position;
	vec3 color;
};

#define MAX_LIGHTS 4
uniform Light _Lights[MAX_LIGHTS];

uniform float ambientK; 
uniform float diffuseK; 
uniform float specular; 
uniform float shininess; 

uniform int numLights;
uniform vec3 camPos;




void main(){
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(0);
	for(int i = 0; i < numLights; i++)
	{
	
	vec3 w = normalize(_Lights[i].position - fs_in.Pos);
		vec3 v = normalize(camPos - fs_in.Pos);
		vec3 h = normalize((w + v)); 
		vec3 spec  = _Lights[i].color * pow(max(dot(h,normal),0),shininess);
		vec3 diffuse = _Lights[i].color * diffuseK * max(dot(w, normal),0);
		vec3 ambient = _Lights[i].color * ambientK;
		lightColor += ambient + diffuse + spec;
	}
	vec3 finalColor = texture(_Texture,fs_in.UV).rgb * lightColor;
	FragColor = vec4(finalColor, 1);
	
}
