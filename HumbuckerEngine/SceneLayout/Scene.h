#pragma once
#include <memory>
#include <vector>


namespace Rendering_General
{
	struct Mesh;
}

class SceneObject;


class Scene
{

public:
	void AddMesh(const Rendering_General::Mesh &mesh) const;
private:
	std::vector<std::shared_ptr<SceneObject>> sceneObjects;
};
