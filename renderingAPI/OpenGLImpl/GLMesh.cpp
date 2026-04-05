#include "GLMesh.h"

namespace ve
{
	GLMesh::GLMesh(const Mesh* mesh)
	{
		glGenVertexArrays(1, &info.VAO);
		glBindVertexArray(info.VAO);
		info.indexCount = static_cast<GLsizei>(mesh->GetIndices().size());

		std::vector<float> interleavedVertices; // This should be interleaved vertex data (position, texcoord, normal)
		interleavedVertices.reserve(mesh->GetVertices().size() + mesh->GetTexCoords().size() + mesh->GetNormals().size());
		for(auto i = 0; i < mesh->GetVertices().size() / 4; i++) // Assuming 4 components for position
		{
			// Position
			interleavedVertices.push_back(mesh->GetVertices()[i * 4]);
			interleavedVertices.push_back(mesh->GetVertices()[i * 4 + 1]);
			interleavedVertices.push_back(mesh->GetVertices()[i * 4 + 2]);
			interleavedVertices.push_back(mesh->GetVertices()[i * 4 + 3]);
			// TexCoord
			interleavedVertices.push_back(mesh->GetTexCoords()[i * 2]);
			interleavedVertices.push_back(mesh->GetTexCoords()[i * 2 + 1]);
			// Normal
			interleavedVertices.push_back(mesh->GetNormals()[i * 3]);
			interleavedVertices.push_back(mesh->GetNormals()[i * 3 + 1]);
			interleavedVertices.push_back(mesh->GetNormals()[i * 3 + 2]);
		}

		buildVBO(interleavedVertices);
		buildEBO(mesh->GetIndices());
		buildAttributes();

		Unbind();
	}

	GLMesh::GLMesh()
	{
		glGenVertexArrays(1, &info.VAO);
		glBindVertexArray(info.VAO);
		info.indexCount = 0;
		buildVBO({});
		buildEBO({});
		buildAttributes();
		Unbind();
	}


	GLMesh::~GLMesh()
	{
		// Here we would delete the VAO, VBO, and EBO
	}

	void GLMesh::buildEBO(const std::vector<unsigned int>& indices)
	{
		//EBO
		glGenBuffers(1, &info.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}


	void GLMesh::buildVBO(const std::vector<float>& vertices)
	{
		//VBO
		glGenBuffers(1, &info.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, info.VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	}
	void GLMesh::buildAttributes()
	{
		//ATTRIBS
		// Position
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		// TexCoord
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(4 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// Normal
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}


	void GLMesh::Bind() const
	{
		glBindVertexArray(info.VAO);
	}
	void GLMesh::Unbind() const
	{
		glBindVertexArray(0);
	}

	GLsizei GLMesh::GetIndexCount() const
	{
		return info.indexCount;
	}
}