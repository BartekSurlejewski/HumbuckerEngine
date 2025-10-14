#pragma once

struct Mesh
{
	Mesh(float vertices[])
	{
		this->vertices = vertices;
	};

	float vertices[];
};
