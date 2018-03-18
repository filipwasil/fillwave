#include <fillwave/loaders/modelLoaderTraits/TModelLoader.h>

namespace flw {
namespace flf {

template<>
TModelLoader<ModelLoaderTraitsAssimp>::TModelLoader() {
  // nothing
}

template<>
TModelLoader<ModelLoaderTraitsAssimp>::~TModelLoader() {
  // nothing
}

} /* flf */
} /* flw */
