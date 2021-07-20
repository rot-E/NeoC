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
    Map
    SampleCode
    String
    System
    TCPClient
    TCPEchoServer
    TCPServer
    Theme
    Theme2
    UDPClient
    UDPEchoServer
    UDPServer
)

add_executable(Console Console.c)
target_link_libraries(Console NeoC)

add_executable(Defer Defer.c)
target_link_libraries(Defer NeoC)

add_executable(DeferInFunction DeferInFunction.c)
target_link_libraries(DeferInFunction NeoC)

add_executable(Exception Exception.c)
target_link_libraries(Exception NeoC)

add_executable(ExceptionNested ExceptionNested.c)
target_link_libraries(ExceptionNested NeoC)

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
target_link_libraries(String NeoC)

add_executable(System System.c)
target_link_libraries(System NeoC)

add_executable(TCPClient TCPClient.c)
target_link_libraries(TCPClient NeoC)

add_executable(TCPEchoServer TCPEchoServer.c)
target_link_libraries(TCPEchoServer NeoC)

add_executable(TCPServer TCPServer.c)
target_link_libraries(TCPServer NeoC)

add_executable(Theme Theme.c)
target_link_libraries(Theme NeoC)

add_executable(Theme2 Theme2.c)
target_link_libraries(Theme2 NeoC)

add_executable(UDPClient UDPClient.c)
target_link_libraries(UDPClient NeoC)

add_executable(UDPEchoServer UDPEchoServer.c)
target_link_libraries(UDPEchoServer NeoC)

add_executable(UDPServer UDPServer.c)
target_link_libraries(UDPServer NeoC)