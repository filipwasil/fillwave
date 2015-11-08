macro(COPY_ASSETS target)
set(ASSETS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/assets/")

add_custom_target(
        assets_${target}
        COMMAND cp -r ${ASSETS_DIRECTORY}/*  ${CMAKE_CURRENT_BINARY_DIR}/
)

add_dependencies(${target} assets_${target})
endmacro(COPY_ASSETS)