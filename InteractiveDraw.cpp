#include "Shader.h"

#include "InteractiveDraw.h"



InteractiveDraw::InteractiveDraw(): VAO(0), VBO(0), objectShader(NULL), verticesCounter(0),
drawFlag(false), offset(0)
{
	//number of vertices
	numVertices = TRIANGLEVERTEX;
}


InteractiveDraw::~InteractiveDraw()
{
	if (VAO)
		glDeleteVertexArrays(1, &VAO);
	if (VBO)
		glDeleteBuffers(1, &VBO);
}

int InteractiveDraw::getNumberOfInputs()
{
	return numVertices;
}

int InteractiveDraw::getVerticesNumber()
{
	return verticesCounter;
}

void InteractiveDraw::setVertexPosition(Vector2f& position)
{
	//populate the data
	float z = 0.0f;
	
	vertPosition.push_back(Vector3f(position.x, position.y, z));
	//D std::cout << vertices[verticesCounter].x << " " << vertices[verticesCounter].y  << " " << vertices[verticesCounter].z<< std::endl;

	//color per vertices
	Vector3f redColor(1.0f, 0.0f, 0.0f);
	vertColor.push_back(redColor);
	
	//load the data if three vertices are added
	loadData();

	//increment the number of vertices
	verticesCounter++;

	//draw flag
	drawFlag = true;

	
}

GLuint InteractiveDraw::getVBO()
{
	return VBO;
}

GLuint InteractiveDraw::getVAO()
{
	return VAO;
}

void InteractiveDraw::allocateMemory()
{
	//create vertex array objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//allocate memory in GPU
	GLsizeiptr PositionSize = sizeof(Vector3f);
	GLsizeiptr ColorSize = sizeof(Vector3f);
	GLuint stride = PositionSize + ColorSize;

	GLsizeiptr TotalSize = MAX_BUFF_SIZE;
	glBufferData(GL_ARRAY_BUFFER, TotalSize, NULL, GL_STATIC_DRAW);

	//assign vertex attrib pointer and information about data
	glEnableVertexAttribArray(0);		//position
	glEnableVertexAttribArray(1);		//color
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(PositionSize));

	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//create shader do after 
	objectShader = new Shader("shaders/vsTestTriangle.txt", "shaders/fsTestTriangle.txt");
}

void InteractiveDraw::loadData()
{
	GLsizeiptr PositionSize = sizeof(Vector3f);
	GLsizeiptr ColorSize = sizeof(Vector3f);

	//bind the buffer again
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	//pass vertex position and color data
	glBufferSubData(GL_ARRAY_BUFFER, offset, PositionSize, vertPosition[verticesCounter]);
	offset += PositionSize;
	glBufferSubData(GL_ARRAY_BUFFER, offset, ColorSize, vertColor[verticesCounter]);
	offset += ColorSize;
		
	//unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	

}

void InteractiveDraw::render()
{
	if (drawFlag)
	{
		//bind the shader program
		objectShader->Bind();

		//bind the VAO and call draw function
		glBindVertexArray(VAO);

		//draw mouse points
		if (verticesCounter < (numVertices + 1))
			glDrawArrays(GL_POINTS, 0, verticesCounter);


		//if there are three verices then draw triangle
		if (verticesCounter > numVertices)
			glDrawArrays(GL_TRIANGLES, 0, verticesCounter);


		glBindVertexArray(0);
		objectShader->Unbind();
	}
}
