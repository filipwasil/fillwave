/*
 * TreeNode.h
 *
 *  Created on: Jan 1, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_MODELS_BASE_ITREENODE_H_
#define INC_FILLWAVE_MODELS_BASE_ITREENODE_H_

#include <fillwave/common/PtrShared.h>

namespace fillwave {
namespace framework {

/*! \class ITreeNode
 * \brief Basic tree ITreeNode Interface.
 */

class ITreeNode {
 public:
	ITreeNode() = default;
	virtual ~ITreeNode() = default;
	virtual void onAttached(ITreeNode* parent) = 0;
	virtual void onDetached() = 0;
};

} /* namespace framework */
typedef framework::PtrShared<framework::ITreeNode> pITreeNode;
typedef std::unique_ptr<framework::ITreeNode> puITreeNode;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MODELS_BASE_ITREENODE_H_ */
