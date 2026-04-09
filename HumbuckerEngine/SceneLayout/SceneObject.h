#pragma once
#include <memory>


struct Transform;

namespace Rendering_General
{
	struct Mesh;
}

class SceneObject
{
public:
	std::unique_ptr<Transform> Transform;

	std::shared_ptr<Rendering_General::Mesh> getMesh() const { return mesh; }
	void setMesh(const std::shared_ptr<Rendering_General::Mesh> &mesh) { this->mesh = mesh; }

private:
	std::shared_ptr<Rendering_General::Mesh> mesh;
};
