# pthreadを使う
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_custom_target(examples)
add_dependencies(examples
    Console
    Defer
    DeferInFunction
    Exception
    ExceptionNested
    List
    Map
    SampleCode
    String
    System
    TCPClient
    TCPEchoServer
    TCPServer
    Theme
    Theme2
    Tuple
    UDPClient
    UDPEchoServer
    UDPServer
)

add_executable(Console Console.c)
target_link_libraries(Console
    NeoC
    Threads::Threads
)

add_executable(Defer Defer.c)
target_link_libraries(Defer
    NeoC
    Threads::Threads
)

add_executable(DeferInFunction DeferInFunction.c)
target_link_libraries(DeferInFunction
    NeoC
    Threads::Threads
)

add_executable(Exception Exception.c)
target_link_libraries(Exception
    NeoC
    Threads::Threads
)

add_executable(ExceptionNested ExceptionNested.c)
target_link_libraries(ExceptionNested
    NeoC
    Threads::Threads
)

add_executable(List List.c)
target_link_libraries(List
    NeoC
    Threads::Threads
)

add_executable(Map Map.c)
target_link_libraries(Map
    NeoC
    Threads::Threads
)

add_executable(SampleCode SampleCode.c)
target_link_libraries(SampleCode
    NeoC
    Threads::Threads
)

add_executable(String String.c)
target_link_libraries(String
    NeoC
    Threads::Threads
)

add_executable(System System.c)
target_link_libraries(System
    NeoC
    Threads::Threads
)

add_executable(TCPClient TCPClient.c)
target_link_libraries(TCPClient
    NeoC
    Threads::Threads
)

add_executable(TCPEchoServer TCPEchoServer.c)
target_link_libraries(TCPEchoServer
    NeoC
    Threads::Threads
)

add_executable(TCPServer TCPServer.c)
target_link_libraries(TCPServer
    NeoC
    Threads::Threads
)

add_executable(Theme Theme.c)
target_link_libraries(Theme
    NeoC
    Threads::Threads
)

add_executable(Theme2 Theme2.c)
target_link_libraries(Theme2
    NeoC
    Threads::Threads
)

add_executable(Tuple Tuple.c)
target_link_libraries(Tuple
    NeoC
    Threads::Threads
)

add_executable(UDPClient UDPClient.c)
target_link_libraries(UDPClient
    NeoC
    Threads::Threads
)

add_executable(UDPEchoServer UDPEchoServer.c)
target_link_libraries(UDPEchoServer
    NeoC
    Threads::Threads
)

add_executable(UDPServer UDPServer.c)
target_link_libraries(UDPServer
    NeoC
    Threads::Threads
)
