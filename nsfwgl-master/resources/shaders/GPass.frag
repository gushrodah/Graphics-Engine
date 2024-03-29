#version 410

in vec2 vTexCoord;
in vec4 vNormal;
in vec4 vPosition;
in vec4 vShadowCoord;

out vec4 FragColor;

uniform sampler2D Diffuse;
uniform vec3 camPos;

vec3 lightColor   = vec3(0.0f, 0.6f, 0.0f);
vec3 lightDir     = normalize(vec3( 1 , 1, 1));
float specPower   = 100.0f;
float shadowBias  = 0.01f;

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

vec3 ambientColor = vec3( 0.5f, 0.5f, 0.5f); 

void main()
{
	vec3 colorMap = texture(Diffuse, vTexCoord).xyz;

	// AMBIENT
	vec3 ambient  = colorMap * ambientColor;

	// DIFFUSE
	float lambert = max(0.0f, dot(vNormal.xyz, -lightDir));
	float visibility = max(1.0f,dot(normalize(vNormal.xyz), lightDir));

	vec3 l_color = visibility * colorMap * lightColor;
	
	//
	vec3 reflectVec = normalize(reflect(lightDir, vNormal.xyz));
	vec3 eye  = normalize(camPos - vPosition.xyz);

	float temp = max(0.0f, dot(reflectVec, eye));
	float specTerm = pow(temp, specPower); 
	vec3 specular = visibility * ambientColor * specTerm * lightColor;

	FragColor = vec4(ambient + l_color + specular ,1);
	//FragColor = vec4(visibility,visibility,visibility,1);
}