#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Material
{
public:
	Shader* shader;
	glm::vec3 ambient;
	unsigned int diffuse;
	unsigned int specular;
	unsigned int emission;
	float shininess;

	Material(Shader* _shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, unsigned int _emission, float _shininess);
};


