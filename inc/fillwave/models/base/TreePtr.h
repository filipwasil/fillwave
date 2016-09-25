/*
 * Tree.h
 *
 *  Created on: Jan 1, 2016
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
 *
 * \tparam T - type of the smart pointers kept in this tree
 *
 * \tparam C - base class for this node
 */

template <class T, class C = ITreeNode>
class TreePtr: public C {
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
