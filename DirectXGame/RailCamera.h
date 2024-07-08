#pragma once

#include <ViewProjection.h>
#include <WorldTransform.h>

class RailCamera {
public:
	void Initialize(const Vector3& _worldPos, const Vector3& _rotare);

	void Update();

	const ViewProjection& GetViewProjectoin() { return viewProjection; };

	const WorldTransform& GetWorldTransform() { return worldTransform; };

	void SetPosition(const Vector3& _pos);
	void SetTranslate(const Vector3& _move, const Vector3& _rotare);

	void SetParent(const WorldTransform* _parent) { worldTransform.parent_ = _parent; };


private:
	void Imgui();
	bool isStop;

	// ワールド変換データ
	WorldTransform worldTransform;
	// ビュープロジェクション
	ViewProjection viewProjection;
};
