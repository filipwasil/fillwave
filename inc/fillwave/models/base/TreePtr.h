/*
 * Tree.h
 *
 *  Created on: Jan 1, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_COMMON_TREE_H_
#define INC_FILLWAVE_COMMON_TREE_H_

#include <fillwave/models/base/ITreeNode.h>
#include <vector>
#include <algorithm>

namespace fillwave {
namespace framework {

/*! \class TreePtr
 * \brief Basic tree template class. Enables attaching and detaching nodes.
 */

template <class T>
class TreePtr: public ITreeNode {
 public:
	TreePtr() :
		mFlagAttachedDetached(true) {

	}

	virtual ~TreePtr() = default;

	void attach(std::unique_ptr<T>&& node) {
		if (node.get() == this) {
			/* User just tried to attach entity to itself */
			abort();
		}
		node->onAttached(this);
		mChildren.push_back(std::move(node));
		mFlagAttachedDetached = true;
	}

	void detach(T* node) {
		auto _compare_function =
		   [node](const T & e) -> bool {bool found = (e == node); if (found) node->onDetached(); return found;};
	auto it = std::remove_if(mChildren.begin(), mChildren.end(), _compare_function);
		if (it != mChildren.end()) {
			mFlagAttachedDetached = true;
			mChildren.erase(it, mChildren.end());
		}
	}

	virtual void onAttached(ITreeNode*) {

	}

	virtual void onDetached() {

	}

	void detachChildren() {
		std::for_each(mChildren.begin(), mChildren.end(),
		[](std::unique_ptr<T> & e) {
			e->onDetached();
		});
		mChildren.clear();
	}

	bool isAttachedDetached() {
		bool result = mFlagAttachedDetached;
		mFlagAttachedDetached = false;
		for (auto& it : mChildren) {
			result = it->isAttachedDetached() ? true : result;
		}
		return result;
	}

	bool mFlagAttachedDetached;

 protected:
	std::vector<std::unique_ptr<T>> mChildren;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_COMMON_TREE_H_ */
