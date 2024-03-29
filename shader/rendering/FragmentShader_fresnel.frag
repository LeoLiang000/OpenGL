#version 330 core

struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot{
vec3 pos;
	vec3 color;
	vec3 dirToLight;
	//float constant;
	//float linear;
	//float quadratic;
	float cosInner;
	float cosOuter;
};

//in vec3 vertexColor;
//in vec2 TexCoord;
in vec3 fragPos;
in vec4 fragPosLightSpace;
in vec3 normal;
in vec2 texCoord;

uniform Material material;
uniform LightDirectional lightD;
uniform LightDirectional lightD1;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;
uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightDirUniform;
uniform vec3 viewPos;
uniform sampler2D shadowMap;
uniform samplerCube skybox;
uniform float fresnel_ratio;

out vec4 FragColor;


// this is function is made for calculating fresnel term
// the code is refering to learnopengl (https://learnopengl.com/PBR/Lighting)
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0f - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main() 
{
	vec3 finalResult = vec3(0, 0, 0);
	vec3 uNormal = normalize(normal);
	vec3 dirToCamera = normalize(viewPos - fragPos);

	// calculate fresnel term
	vec3 albedo = vec3(0.5f);
	float metallic = 0.3f;
	vec3 F0 = vec3(0.04);
	F0	= mix(F0, albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(uNormal, dirToCamera), 0.0), F0);

	// calculate the proportion of reflection and refraction
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;

	// set the ratio for calculating refraction (this is not used for reflection)
	//float ratio = 1.00 / 1.52;
	// the direction from the fragment to camera
	vec3 I = normalize(fragPos - viewPos);
	// get the refraction and  the refraction direction
	vec3 Reflect = reflect(I, normalize(uNormal));
	vec3 Refract = refract(I, normalize(uNormal), fresnel_ratio);

	// sum up the refraction and the reflection
	FragColor = vec4(kS * texture(skybox, Reflect).rgb, 1.0f);
	FragColor += vec4(kD * texture(skybox, Refract).rgb, 1.0f);


}

