#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class FollowCamera {
public:
	FollowCamera();
	~FollowCamera();

	void Initialize();
	void Update();

	void SetTarget(const WorldTransform* _target) { target_ = _target; };
	const ViewProjection& GetViewProjection() { return viewProjection_; };

private:
	ViewProjection viewProjection_;
	const WorldTransform* target_ = nullptr;
};
