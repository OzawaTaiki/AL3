#pragma once

#include <Model.h>
#include <WorldTransform.h>

class Skydoom {
public:
	~Skydoom();

	void Initialze(Model* _model);
	void Update();
	void Draw(ViewProjection& _viewProjection);

private:
	void ImGui();

	WorldTransform worldTransform;
	Model* model = nullptr;
};
