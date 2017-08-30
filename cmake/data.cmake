
macro(copy_assets target)
  set (ASSETS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/assets/")

  add_custom_target (
      assets_${target}
      COMMAND cp -r ${ASSETS_DIRECTORY}/* ${CMAKE_CURRENT_BINARY_DIR}/
  )

  add_dependencies (${target} assets_${target})
endmacro(copy_assets)

macro(copy_assets_generic)
  add_custom_target (
      assets_copy_${target}
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/examples/assets ${CMAKE_CURRENT_BINARY_DIR}/
  )

  add_dependencies (${target} assets_copy_${target})
endmacro(copy_assets)

macro(copy_test_assets target)
  set (ASSETS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/glfw/data")

  add_custom_target (
      assets_${target}
      COMMAND cp -r ${ASSETS_DIRECTORY}/* ${CMAKE_CURRENT_BINARY_DIR}/
  )

  add_dependencies (${target} assets_${target})
endmacro(copy_test_assets)