#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
uniform float _Time;
out vec2 UV;
float circleSDF(vec2 p, float r){
    return length(p)-r;
}

void main(){


	UV = vUV;
	vec2 circlePos = vec2(cos(_Time),sin(_Time));
float circleRadius = 0.1;
float d = circleSDF(UV - circlePos,circleRadius);

	gl_Position = vec4(vPos * d,1.0);
}