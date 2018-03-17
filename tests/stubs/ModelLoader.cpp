#include <fillwave/loaders/TModelLoader.h>
#include <fillwave/loaders/ModelLoaderTraits.h>

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
