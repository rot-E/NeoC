# オプションを用いてライブラリを共有ライブラリとしても生成出来るように
option(NEOC_BUILD_SHARED_LIBS "build NeoC as a shared library" OFF)

if (NEOC_BUILD_SHARED_LIBS)
    add_library(NeoC SHARED)
else()
    add_library(NeoC STATIC)
endif()

# NeoCライブラリを生成するために必要なソースファイル
# cmakeドキュメントで推奨していないため、GOLBやAUX_SOURCE_DIRECTORYを利用しない方法で記述した
# https://cmake.org/cmake/help/latest/command/file.html#filesystem
target_sources(NeoC
    PRIVATE
    Base/Object.c
    Base/Error.c
    Base/Memory.c
    Base/Exception/Signal.c
    Base/Exception/Exception.c
    Base/Defer.c
    Base/Environment.c

    SPEC/CC.c
    SPEC/CSI.c
    SPEC/SGR.c

    String.c
    Console.c
    System.c
    Socket.c

    Collection/Collection.c
    #Collection/Tuple.c
    #Collection/List.c
    #Collection/Stack.c
    #Collection/Queue.c
    #Collection/Map.c
    #Collection/Set.c

    #File/Directory.c
    #File/File.c
)

# NeoCライブラリを生成するために必要なヘッダファイルの場所
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
