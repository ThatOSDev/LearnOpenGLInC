#ifndef MESH_H
#define MESH_H

#include <cglm/cglm.h>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <string.h>
#include <stdio.h>

#include <learnopengl/shader.h>

typedef struct aiString aiString;
typedef float vec2f[2];

typedef struct Vertex {
	vec3  position;
	vec3  normal;
	vec2f texCoords;
} Vertex;

typedef struct Texture {
	uint32_t id;
	char* type;
	aiString path;
} Texture;

typedef struct Mesh {
	Vertex *vertices;
	uint32_t numVertices;
	uint32_t *indices;
	uint32_t numIndices;
	Texture *textures;
	uint32_t numTextures;
	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;
} Mesh;

typedef uint32_t TextureImage;

void mesh_draw(Mesh *mesh, unsigned int programID);
void mesh_setup(Mesh *mesh);
TextureImage initTexture(const char* imageName);

void mesh_setup(Mesh *mesh)
{
	glGenVertexArrays(1, &mesh->VAO);
	glGenBuffers(1, &mesh->VBO);
	glGenBuffers(1, &mesh->EBO);

	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

	glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vertex), mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->numIndices * sizeof(uint32_t), mesh->indices, GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// tex coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

void mesh_draw(Mesh *mesh, unsigned int programID)
{
	uint32_t iDiffuse = 1;
	uint32_t iSpecular = 1;

	for (uint32_t i = 0; i < mesh->numTextures; i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		Texture *texture = &mesh->textures[i];
		int number = 0;
		if (strcmp("texture_diffuse", texture->type) == 0) {
			number = iDiffuse;
			++iDiffuse;
		}
		else if (strcmp("texture_specular", texture->type) == 0) {
			number = iSpecular;
			++iSpecular;
		}

		char materialUniformName[256];
		sprintf(materialUniformName, "material.%s%i", texture->type, number);
		glGetUniformLocation(programID, materialUniformName);
		setInt(programID, materialUniformName, i);
		glBindTexture(GL_TEXTURE_2D, texture->id);
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

TextureImage initTexture(const char* imageName)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imageName, &width, &height, &nrChannels, 0);
	if (!data) {
		printf("Failed to load texture : %s\n", imageName);
		return 0;
	}

	GLenum format = GL_RGB;
	if (nrChannels == 1) {
		format = GL_RED;
	}
	else if (nrChannels == 3) {
		format = GL_RGB;
	}
	else if (nrChannels == 4) {
		format = GL_RGBA;
	}

	TextureImage texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return texture;
}

#endif // MESH_H
