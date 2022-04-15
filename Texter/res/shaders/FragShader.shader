#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 u_Params;

uniform sampler2D u_Texture;

const float hardness = 0.1;
const int iterations = 1;
const float speed = 12.5;
const float intensity = 1.0;


#define HASHSCALE4 vec4(1031, .1030, .0973, .1099)
vec4 hash43(vec3 p)
{
	vec4 p4 = fract(vec4(p.xyzx)  * HASHSCALE4);
	p4 += dot(p4, p4.wzxy + 19.19);
	return fract((p4.xxyz + p4.yzzw)*p4.zywx);
}

float PatternDots(vec2 uv, vec2 pos, float age, float scale, float cells) {
	vec2 vD = vec2(uv - pos);
	float fD = sqrt(dot(vD, vD)) * 2.0 * (cells / 16.0);
	float fDa = 10.0 * fD;
	float freq = 300.0 * scale;
	return    max(0.0, 1.0 - fDa * fDa)
		* sin((fD*freq - age * 40.0*(scale*2.0 - 1.0))*hardness);
}


float DotsDraw(vec2 uv, float cells) {
	float height = 0.0;
	vec2 cell = floor(uv * cells);
	for (int iter = 0; iter < iterations; iter++) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				vec2 cell_t = cell + vec2(i, j);
				vec2 uv_t = uv;

				vec4 rnd_t = hash43(vec3(cell_t, float(iter)));
				vec2 pos_t = (cell_t + rnd_t.xy) / cells;
				float age_t = (u_Params.r*speed + rnd_t.z);
				float scale_t = rnd_t.w;
				height += PatternDots(uv_t, pos_t, age_t, scale_t, cells);
			}
		}
	}
	return height;
}

float Height(vec2 uv) {
	float height = 0.0;

	height += DotsDraw(uv, 8.0);
	height += DotsDraw(uv, 4.0);
	height /= 5.0;

	return height * intensity;
}

vec2 NormalCalc(vec2 uv) {
	const float eps = 0.01;
	vec2 offset = vec2(eps, 0.0);
	return vec2(
		Height(uv + offset.xy) - Height(uv - offset.xy),
		Height(uv + offset.yx) - Height(uv - offset.yx)
	);
}

vec4 full ()
{
	vec2 uv = vec2(gl_FragCoord.x / u_Params.g, gl_FragCoord.y / u_Params.b);


	float height = Height(uv);
	vec2 dudv = NormalCalc(uv);
	vec3 normal = normalize(vec3(dudv, sqrt(max(1.0 - dot(dudv, dudv), 0.0))));

	
	if (gl_FragCoord.y < u_Params.b*0.35) {
		return vec4(height*0.5 + 0.5);
	}
	else if (gl_FragCoord.y < u_Params.b*0.63) {
		return vec4(normal*0.5 + 0.5, 1);
	}
	else {
		return vec4(step(height, 0.1)*0.5 + 0.5);
	}
}





void main()

{

	color = full();
	

};