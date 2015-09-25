ADD_CUSTOM_COMMAND( OUTPUT SVN_REVISION
                    COMMAND ${CMAKE_ROOT}/getSVNversion.sh
                    WORKING_DIRECTORY ${CMAKE_ROOT}
                    COMMENT "Creates/updates header SVN Revision Header"
                    )