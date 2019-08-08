#ifndef INTERCATIVE_DRAW_H
#define INTERCATIVE_DRAW_H
#include "CommonHeader.h"

#define TRIANGLEVERTEX 3
#define MAX_BUFF_SIZE 1000

class Shader;

class InteractiveDraw
{
public:
	InteractiveDraw();
	~InteractiveDraw();
	
	//get primitive
	int getNumberOfInputs();
	int getVerticesNumber();

	//set the vertices from mouse click
	void setVertexPosition(Vector2f& position);

	//methods for loading and rendering
	void allocateMemory();
	void render();

	//for debugging
	GLuint getVBO();
	GLuint getVAO();

private:
	std::vector<Vector3f> vertPosition;
	std::vector<Vector3f> vertColor;
	GLuint VAO, VBO;

	//number of vertics
	int numVertices;
	int verticesCounter;
	GLintptr offset;

	//load the data to GPU
	void loadData();

	//flag to start rendering
	bool drawFlag;

	//create a shader for the current object from source file
	Shader* objectShader;
};
#endif // !INTERCATIVE_DRAW_H


