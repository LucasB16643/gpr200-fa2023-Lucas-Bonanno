#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _NoiseTexture;
uniform sampler2D _BrickTexture;
uniform float _Time;

void main(){
	float noise = texture(_NoiseTexture,UV).r;
vec2 uv = UV + noise *_Time * 0.1f;
FragColor = texture(_BrickTexture,uv);
}
