#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject(VertVec& verts, IndVec& indices, NormalVec& normals) {
	count = indices.size();
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenBuffers(1, &nbo);

	bind();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
	
	unbind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexArrayObject::~VertexArrayObject() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &nbo);
	glDeleteVertexArrays(1, &vao);
}

void VertexArrayObject::bind() {
	glBindVertexArray(vao);
}

void VertexArrayObject::unbind() {
	glBindVertexArray(0);
}

void VertexArrayObject::draw() {
	bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0L);
	unbind();
}
