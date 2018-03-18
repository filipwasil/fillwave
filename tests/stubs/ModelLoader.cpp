
#include <fillwave/loaders/ModelLoader.h>

namespace flw {
namespace flf {

//template<>
//TModelLoader<ModelLoaderTraitsTinyObjLoader>::TModelLoader() {
//  // nothing
//}
//
//template<>
//TModelLoader<ModelLoaderTraitsTinyObjLoader>::~TModelLoader() {
//  // nothing
//}

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
