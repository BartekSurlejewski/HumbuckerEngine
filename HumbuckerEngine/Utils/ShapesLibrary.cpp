#include "ShapesLibrary.h"

std::vector<float> Square::Vertices =
{
	// positions	  // colors
	0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0, // top right
	0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0, // bottom left
	-0.5f, 0.5f, 0.0f, 1.0, 1.0, 1.0 // top left
};

std::vector<unsigned int> Square::Indices =
{
	0, 1, 3, // First triangle
	1, 2, 3 // Second triangle
};

std::vector<float> Cube::Vertices =
{
	// positions	  // colors
	// Front
	0.5f, 0.5f, -0.5f, 1.0, 0.0, 0.0, // top right
	0.5f, -0.5f, -0.5f, 0.0, 1.0, 0.0, // bottom right
	-0.5f, -0.5f, -0.5f, 0.0, 0.0, 1.0, // bottom left
	-0.5f, 0.5f, -0.5f, 1.0, 1.0, 1.0, // top left
	// Back
	- 0.5f, 0.5f, 0.5f, 1.0, 1.0, 1.0, // top right
	-0.5f, -0.5f, 0.5f, 0.0, 0.0, 1.0, // bottom right
	0.5f, -0.5f, 0.5f, 0.0, 1.0, 0.0, // bottom left
	0.5f, 0.5f, 0.5f, 1.0, 0.0, 0.0, // top left
};

std::vector<unsigned int> Cube::Indices =
{
	// Front Wall
	0, 1, 3, // First triangle
	1, 2, 3, // Second triangle
	// Right Wall
	7, 6, 0,
	6, 1, 0,
	// Back Wall
	4, 5, 7,
	5, 6, 7,
	// Left Wall
	3, 2, 4,
	2, 5, 4,
	// Up Wall
	7, 0, 4,
	0, 3, 4,
	// Down Wall
	6, 1, 5,
	1, 2, 5
};
