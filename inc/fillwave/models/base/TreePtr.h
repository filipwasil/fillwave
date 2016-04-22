/*
 * Tree.h
 *
 *  Created on: Jan 1, 2016
 *      Author: filip
 *
 * Fillwave C++11 graphics Engine
 *
 * Copyright (C) 2016 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This library is available free of charge for any commercial
 * or non-commercial use. However, You are obligated to put a clearly
 * visible information in Your license agreement that Your Software
 * uses Fillwave library to handle graphics management.
 * If You are interested in extra support, extra features
 * or cooperation I look forward to hearing from You.
 *
 * fillwave@gmail.com
 *
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

	void attach(T& node) {
		mChildren.push_back(node);
		mFlagAttachedDetached = true;
		node->onAttached(this);
	}

	void detach(T& node) {
		auto _compare_function =
		   [node](const T & e) -> bool {bool found = (e == node); if (found) node->onDetached(); return found;};
	auto _begin = mChildren.begin();
		auto _end = mChildren.end();
		auto it = std::remove_if(_begin, _end, _compare_function);
		if (it != _end) {
			mFlagAttachedDetached = true;
			mChildren.erase(it, _end);
		}
	}

	virtual void onAttached(ITreeNode*) {

	}

	virtual void onDetached() {

	}

	void detachChildren() {
		std::for_each(mChildren.begin(), mChildren.end(),
		[](T & e) {
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
	std::vector<T> mChildren;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_COMMON_TREE_H_ */
