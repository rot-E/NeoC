# cmakeドキュメントで推奨していないため、GOLBやAUX_SOURCE_DIRECTORYを利用しない方法で記述した
# https://cmake.org/cmake/help/latest/command/file.html#filesystem

option(NEOC_BUILD_SHARED_LIBS "build NeoC as a shared library" OFF)

if (MYLIB_BUILD_SHARED_LIBS)
    add_library(NeoC SHARED)
else()
    add_library(NeoC STATIC)
endif()

target_sources(NeoC
    PRIVATE
    Exception/Exception.c
    Exception/Signal.c
    #File/Directory.c
    #File/File.c
    SPEC/CC.c
    SPEC/CSI.c
    SPEC/SGR.c
    Console.c
    Defer.c
    Environment.c
    Error.c
    Memory.c
    Socket.c
    String.c
    System.c
)

target_include_directories(NeoC
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

include(GNUInstallDirs)
# install NeoC library
install(TARGETS NeoC
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
# install headers
# includeフォルダの中身を全てコピーする
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)