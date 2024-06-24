#pragma once

#include <Vector3.h>
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <vector>

class RailCamera {
public:
	void Initialize(const Vector3& _worldPos, const Vector3& _rotare);

	void Update(const Vector3& _move, const Vector3& _rotare);

	void CamulRomDraw();

	const ViewProjection& GetViewProjectoin() { return viewProjection; };

	const WorldTransform& GetWorldTransform() { return worldTransform; };

private:
	void Imgui();

	std::vector<Vector3> controlPoints;

	// ワールド変換データ
	WorldTransform worldTransform;
	// ビュープロジェクション
	ViewProjection viewProjection;
};
