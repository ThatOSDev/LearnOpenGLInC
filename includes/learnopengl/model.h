#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

#include <stdbool.h>

typedef struct Model {
	Mesh*    meshes;
	uint32_t numMeshes;
	char*    directory;
} Model;

Model loadModel(char* path);
void model_draw(Model* model, unsigned int programID);

typedef struct aiScene    aiScene;
typedef struct aiNode     aiNode;
typedef struct aiMaterial aiMaterial;
typedef struct aiMesh     aiMesh;
typedef struct aiFace     aiFace;

uint32_t model_countMeshes(const aiNode* node);
void model_processNode(Model* model, const aiNode* node, const aiScene* scene, uint32_t* meshIndex);
Mesh model_processMesh(Model* model, const aiMesh* mesh, const aiScene* scene);
Texture* loadMaterialTextures(Model* model, const aiMaterial* mat, int32_t type, char* typeName, uint32_t* numTextures);

static Texture* cachedTextures = NULL;
static uint32_t numCachedTextures = 0;
static uint32_t sizeCachedTextures = 0;

Model loadModel(char* path)
{
	Model model;
	const aiScene* scene = aiImportFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		printf("ERROR:ASSIMP::%s\n", aiGetErrorString());
	}

	uint32_t index = strrchr(path, '/') - path;
	model.directory = calloc(index + 1, sizeof(char));
	strncpy(model.directory, path, index);
	model.directory[index] = '\0';

	uint32_t numMeshes = model_countMeshes(scene->mRootNode);
	model.meshes = calloc(numMeshes, sizeof(Mesh));
	model.numMeshes = numMeshes;

	uint32_t meshIndex = 0;
	model_processNode(&model, scene->mRootNode, scene, &meshIndex);
	return model;
}

void model_draw(Model *model, unsigned int programID)
{
	for (uint32_t i = 0; i < model->numMeshes; i++) {
		mesh_draw(&model->meshes[i], programID);
	}
}

void model_processNode(Model* model, const aiNode* node, const aiScene* scene, uint32_t* meshIndex)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++) {
		const aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		model->meshes[*meshIndex] = model_processMesh(model, mesh, scene);
		(*meshIndex)++;
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		model_processNode(model, node->mChildren[i], scene, meshIndex);
	}
}

uint32_t model_countMeshes(const aiNode* node)
{
	uint32_t result = node->mNumMeshes;

	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		result += model_countMeshes(node->mChildren[i]);
	}

	return result;
}

Mesh model_processMesh(Model* model, const aiMesh* mesh, const aiScene* scene)
{
	Vertex *vertices = calloc(mesh->mNumVertices, sizeof(Vertex));
	for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex = {0};
		vertex.position[0] = mesh->mVertices[i].x;
		vertex.position[1] = mesh->mVertices[i].y;
		vertex.position[2] = mesh->mVertices[i].z;

		vertex.normal[0] = mesh->mNormals[i].x;
		vertex.normal[1] = mesh->mNormals[i].y;
		vertex.normal[2] = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0]) {
			vertex.texCoords[0] = mesh->mTextureCoords[0][i].x;
			vertex.texCoords[1] = mesh->mTextureCoords[0][i].y;
		}
		vertices[i] = vertex;
	}

	uint32_t numIndices = 0;
	for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
		numIndices += mesh->mFaces[i].mNumIndices;
	}

	uint32_t *indices = calloc(numIndices, sizeof(uint32_t));
	uint32_t iIndices = 0;
	for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++) {
			indices[iIndices] = face.mIndices[j];
			++iIndices;
		}
	}

	uint32_t numDiffuseMaps = 0;
	uint32_t numSpecularMaps = 0;

	Texture* diffuseMaps = NULL;
	Texture* specularMaps = NULL;

	if (scene->mNumMaterials > 0)
    {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		diffuseMaps = loadMaterialTextures(model, material, aiTextureType_DIFFUSE, "texture_diffuse", &numDiffuseMaps);
		specularMaps = loadMaterialTextures(model, material, aiTextureType_SPECULAR, "texture_specular", &numSpecularMaps);
	}

	Texture* textures = NULL;
	uint32_t numTextures = numDiffuseMaps + numSpecularMaps;
	if (numTextures > 0) {
		textures = calloc(numTextures, sizeof(Texture));

		if (diffuseMaps != NULL) {
			memcpy(textures, diffuseMaps, sizeof(Texture) * numDiffuseMaps);
			free(diffuseMaps);
		}

		if (specularMaps != NULL) {
			memcpy(&textures[numDiffuseMaps], specularMaps, sizeof(Texture) * numSpecularMaps);
			free(specularMaps);
		}
	}

	Mesh result = {0};
	result.vertices = vertices;
	result.numVertices = mesh->mNumVertices;
	result.indices = indices;
	result.numIndices = numIndices;
	result.textures = textures;
	result.numTextures = numTextures;

	mesh_setup(&result);
	return result;
}

Texture* loadMaterialTextures(Model* model, const aiMaterial* mat, int32_t type, char* typeName, uint32_t* numTextures)
{
	*numTextures = aiGetMaterialTextureCount(mat, type);
	if (*numTextures == 0) {
		return NULL;
	}

	if (cachedTextures == NULL) {
		sizeCachedTextures = 2;
		cachedTextures = calloc(sizeCachedTextures, sizeof(Texture));
	}

	Texture* textures = calloc(*numTextures, sizeof(Texture));

	for (uint32_t i = 0; i < *numTextures; i++) {
		aiString str;
		aiGetMaterialTexture(mat, type, i, &str, NULL, NULL, NULL, NULL, NULL, NULL);

		Texture* cachedTexture = NULL;
		for (uint32_t iCache = 0; iCache < numCachedTextures; ++iCache) {
			if (strcmp(str.data, cachedTextures[iCache].path.data) == 0) {
				cachedTexture = &cachedTextures[iCache];
			}
		}

		if (cachedTexture == NULL)
        {
			uint32_t dirLength = strlen(model->directory);
			char* texturePath = calloc(str.length + dirLength + 2, sizeof(char));
			strcpy(texturePath, model->directory);
			strcat(texturePath, "/");
			strcat(texturePath, str.data);

			Texture texture = {0};
			texture.id = initTexture(texturePath);
			texture.type = typeName;
			texture.path = str;
			textures[i] = texture;
			free(texturePath);

			if (numCachedTextures == sizeCachedTextures) {
				sizeCachedTextures = sizeCachedTextures * 2;
				cachedTextures = realloc(cachedTextures, sizeCachedTextures * sizeof(Texture));
			}

			cachedTextures[numCachedTextures] = texture;
			++numCachedTextures;
		}
		else {
			textures[i] = *cachedTexture;
		}
	}

	return textures;
}

#endif // MODEL_H
