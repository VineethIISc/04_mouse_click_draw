#include "Shader.h"
#include "TestTriangle.h"

TestTriangle::TestTriangle(): VBO(0), VAO(0), objectShader(NULL)
{
	//number of vertices
	numVertices = 3; 
	
	//create vertices
	init();

	
}


TestTriangle::~TestTriangle()
{
	if (VAO)
		glDeleteVertexArrays(1, &VAO);
	if (VBO)
		glDeleteBuffers(1, &VBO);

}

GLuint TestTriangle::getVBO()
{
	return VBO;
}

GLuint TestTriangle::getVAO()
{
	return VAO;
}

void TestTriangle::init()
{
	//create three vertices for the triangle
	vertices.push_back(Vector3f(0.5f, 0.0f, 0.0f));
	vertices.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	vertices.push_back(Vector3f(0.0f, 1.0f, 0.0f));

	//create three vertices for the triangle
	colors.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	colors.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	colors.push_back(Vector3f(0.0f, 0.0f, 1.0f));
}

void TestTriangle::loadData()
{
	//create vertex array objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//allocate memory in GPU
	GLsizeiptr VertexSize = sizeof(Vector3f) * numVertices;
	GLsizeiptr ColorSize = sizeof(Vector3f) * numVertices;
	GLsizeiptr TotalSize = VertexSize + ColorSize;
	glBufferData(GL_ARRAY_BUFFER, TotalSize, NULL, GL_STATIC_DRAW);

	//pass vertex position and color data
	GLintptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, VertexSize, vertices[0]);
	offset += VertexSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, ColorSize, colors[0]);

	//assign vertex attrib pointer and information about data
	glEnableVertexAttribArray(0);		//position
	glEnableVertexAttribArray(1);		//color
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(VertexSize));

	//unbind VAO, VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//create shader do after 
	objectShader = new Shader("shaders/vsTestTriangle.txt", "shaders/fsTestTriangle.txt");
}

void TestTriangle::render()
{
	//bind the shader program
	objectShader->Bind();

	//bind the VAO and call draw function
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glBindVertexArray(0);
	objectShader->Unbind();
}

