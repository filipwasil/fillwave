
set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Filip Wasil <fillwave@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/LICENSE.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Description.txt")
set(CPACK_PACKAGE_VERSION                 "${PROJECT_VERSION}" )
set(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION "Fillwave is a free OpenGL 3.3+ graphics engine for Linux and OSX.")

set(CPACK_PACKAGE_HOMEPAGE "filipwasil.bitbucket.org/fillwave")

set(CPACK_NSIS_COMPRESSOR "/FINAL zlib")
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_DISPLAY_NAME "Fillwave graphics engine")
set(CPACK_NSIS_INSTALLED_ICON_NAME "lib\\\\libfillwave.dll")
set(CPACK_NSIS_HELP_LINK "http://filipwasil.bitbucket.org/")
set(CPACK_NSIS_URL_INFO_ABOUT "http://filipwasil.bitbucket.org/")
set(CPACK_NSIS_CONTACT "fillwave@gmail.com")
set(CPACK_NSIS_MUI_ICON "${CMake_SOURCE_DIR}\\\\icon/icon_full.png")
set(CPACK_NSIS_MUI_UNIICON "${CMake_SOURCE_DIR}\\\\icon/icon_full.png")
set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}\\\\icon/icon_full.png")

#Argument passed as nsis compression command
#http://nsis.sourceforge.net/Docs/Chapter4.html

if(FILLWAVE_BUILD_DEB)
	set(CPACK_GENERATOR "DEB")
elseif(FILLWAVE_BUILD_RPM)
	set(CPACK_GENERATOR "RPM")
elseif(FILLWAVE_BUILD_TGZ)
	set(CPACK_GENERATOR "TGZ")
endif()