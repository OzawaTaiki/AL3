#include "WorldTransform.h"
#include "MatrixFunction.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MatrixFunction::MakeAffineMatrix(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ = matWorld_ * parent_->matWorld_;
	}

	TransferMatrix();
}
