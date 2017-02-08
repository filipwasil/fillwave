file(GLOB SRCS *.cpp)

add_executable(testfoo ${SRCS})

target_link_libraries(test
    src
    libgtest
    libgmock
)

install(TARGETS test DESTINATION bin)

