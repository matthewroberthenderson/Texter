#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 u_Params;


vec2 random2(vec2 uv)
{
	uv = vec2(dot(uv, vec2(127.1, 311.7)),
		dot(uv, vec2(269.5, 183.3)));
	return -1.0 + 2.0 * fract(sin(uv) * 43758.5453123);
}

vec4 DrawCellsProceedural()
{
	

	float cellNum = 10.;

	vec2 uv = vec2(gl_FragCoord.x / u_Params.g, gl_FragCoord.y / u_Params.b);

	//uv.x *= iResolution.x / iResolution.y;

	uv *= cellNum;

	vec2 i = floor(uv);
	vec2 f = fract(uv);

	float minDist = 1.;

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			vec2 neighbor = vec2(x, y);

			vec2 point = random2(i + neighbor);

			point = 0.5 + 0.5 * sin(u_Params.r + 6.2831 * point);

			float dist = length(neighbor + point - f);

			minDist = min(minDist, dist);
		}
	}



	float dist = length(0.5f - f);

	minDist = min(minDist, dist);


	return vec4(vec3(minDist), 1.);

}






void main()

{

	vec2 uv = vec2(gl_FragCoord.x / u_Params.g, gl_FragCoord.y / u_Params.b);
	color = DrawCellsProceedural();
	

};