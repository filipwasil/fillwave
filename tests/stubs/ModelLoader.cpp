
#include <fillwave/loaders/ModelLoader.h>

namespace flw {
namespace flf {

#if defined(FILLWAVE_MODEL_LOADER_ASSIMP)

template<>
TModelLoader<ModelLoaderTraitsAssimp>::TModelLoader() {
  // nothing
}

template<>
TModelLoader<ModelLoaderTraitsAssimp>::~TModelLoader() {
  // nothing
}

#elif defined (FILLWAVE_MODEL_LOADER_TINYOBJLOADER)

template<>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::TModelLoader() {
  // nothing
}

template<>
TModelLoader<ModelLoaderTraitsTinyObjLoader>::~TModelLoader() {
  // nothing
}

#else

template<>
TModelLoader<ModelLoaderTraitsDefault>::TModelLoader() {
  // nothing
}

template<>
TModelLoader<ModelLoaderTraitsDefault>::~TModelLoader() {
  // nothing
}

#endif


} /* flf */
} /* flw */
