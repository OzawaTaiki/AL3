#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>

class BaseCharacter {
public:
	virtual void Initialize(const std::vector<Model*>& _models);
	virtual void Update();
	virtual void Draw(const ViewProjection& _viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; };

protected:
	std::vector<Model*> models_;
	WorldTransform worldTransform_;
};
