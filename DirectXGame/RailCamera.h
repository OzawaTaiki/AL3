#pragma once

#include <ViewProjection.h>
#include <WorldTransform.h>

class RailCamera {
public:
	void Initialize(const Vector3& _worldPos, const Vector3& _rotare);

	void Update(const Vector3& _move, const Vector3& _rotare);

	const ViewProjection& GetViewProjectoin() { return viewProjection; };

	const WorldTransform& GetWorldTransform() { return worldTransform; };

private:
	void Imgui();
	bool isStop;

	// ワールド変換データ
	WorldTransform worldTransform;
	// ビュープロジェクション
	ViewProjection viewProjection;
};
