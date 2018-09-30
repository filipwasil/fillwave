#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flf/models/base/ITreeNode.h>
#include <flw/cmn/Containers.h>
#include <algorithm>
#include <utility>

namespace flw {
namespace flf {

/*! \class TreePtr
 * \brief Basic tree template class. Enables attaching and detaching nodes.
 *
 * \tparam T - type of the smart pointers kept in this tree
 *
 * \tparam C - base class for this node
 */

template <class T, class C = ITreeNode>
class TreePtr : public C {
public:
  TreePtr()
      : mFlagAttachedDetached(true) {
    // nothing
  }

  ~TreePtr() override = default;

  TreePtr &operator=(const TreePtr &) = delete;

  TreePtr(const TreePtr &) = delete;

  TreePtr &operator=(TreePtr &&) = default;

  TreePtr(TreePtr&& ) = default;

  void attach(std::unique_ptr<T>&& node) {
    if (node.get() == this) {
      /* User just tried to attach tree node to itself */
      abort();
    }
    node->onAttached(this);
    mChildren.push_back(std::move(node));
    mFlagAttachedDetached = true;
  }

  template <typename TNode, typename ...TArguments>
  void attachNew(TArguments ...args) {
    attach(std::make_unique<TNode>(args...));
  }

  void detach(T* node) {
    auto _compare_function = [node](std::unique_ptr<T> const& e) -> bool {
      bool found = (e.get() == node);
      if (found) {
        node->onDetached();
      }
      return found;
    };
    auto it = std::remove_if(mChildren.begin(), mChildren.end(), _compare_function);
    if (it != mChildren.end()) {
      mFlagAttachedDetached = true;
      mChildren.erase(it, mChildren.end());
    }
  }

  virtual void onAttached(ITreeNode *) {
    // nothing
  }

  virtual void onDetached() {
    // nothing
  }

  void detachChildren() {
    std::for_each(mChildren.begin(), mChildren.end(), [](std::unique_ptr<T> &e) {
      e->onDetached();
    });
    mChildren.clear();
  }

  bool isAttachedDetached() {
    bool result = mFlagAttachedDetached;
    mFlagAttachedDetached = false;
    for (auto &it : mChildren) {
      result = it->isAttachedDetached() ? true : result;
    }
    return result;
  }

  bool mFlagAttachedDetached;

protected:
  vec<std::unique_ptr<T>> mChildren;
};

} /* flf */
} /* flw */
