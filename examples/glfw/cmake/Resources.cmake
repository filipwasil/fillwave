macro(copy_resources target)
  set (RESOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../data")
  #remember to clean the target directory
  add_custom_target (
      resources_${target}
      COMMAND cp -r ${RESOURCES_DIRECTORY}/* ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
  )

  add_dependencies (${target} resources_${target})
endmacro(copy_resources)
