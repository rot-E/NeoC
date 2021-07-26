# pthreadを使う
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_custom_target(examples)
add_dependencies(examples
    Object
    Exception
    ExceptionNested
    Defer
    DeferInFunction

    String
    Console
    Theme
    Theme2

    System

    TCPClient
    TCPServer
    TCPEchoServer
    UDPClient
    UDPServer
    UDPEchoServer

    Tuple
    List
    Stack
    Queue
    Map
    #Set

    OOPMain
    SampleCode
)

add_executable(Object Base/Object.c)
target_link_libraries(Object
    NeoC
    Threads::Threads
)

add_executable(Exception Base/Exception/Exception.c)
target_link_libraries(Exception
    NeoC
    Threads::Threads
)

add_executable(ExceptionNested Base/Exception/ExceptionNested.c)
target_link_libraries(ExceptionNested
    NeoC
    Threads::Threads
)

add_executable(Defer Base/Defer.c)
target_link_libraries(Defer
    NeoC
    Threads::Threads
)

add_executable(DeferInFunction Base/DeferInFunction.c)
target_link_libraries(DeferInFunction
    NeoC
    Threads::Threads
)

add_executable(String String.c)
target_link_libraries(String
    NeoC
    Threads::Threads
)

add_executable(Console Console/Console.c)
target_link_libraries(Console
    NeoC
    Threads::Threads
)

add_executable(Theme Console/Theme.c)
target_link_libraries(Theme
    NeoC
    Threads::Threads
)

add_executable(Theme2 Console/Theme2.c)
target_link_libraries(Theme2
    NeoC
    Threads::Threads
)

add_executable(System System.c)
target_link_libraries(System
    NeoC
    Threads::Threads
)

add_executable(TCPClient Socket/TCPClient.c)
target_link_libraries(TCPClient
    NeoC
    Threads::Threads
)

add_executable(TCPServer Socket/TCPServer.c)
target_link_libraries(TCPServer
    NeoC
    Threads::Threads
)

add_executable(TCPEchoServer Socket/TCPEchoServer.c)
target_link_libraries(TCPEchoServer
    NeoC
    Threads::Threads
)

add_executable(UDPClient Socket/UDPClient.c)
target_link_libraries(UDPClient
    NeoC
    Threads::Threads
)

add_executable(UDPServer Socket/UDPServer.c)
target_link_libraries(UDPServer
    NeoC
    Threads::Threads
)

add_executable(UDPEchoServer Socket/UDPEchoServer.c)
target_link_libraries(UDPEchoServer
    NeoC
    Threads::Threads
)

add_executable(Tuple Collection/Tuple.c)
target_link_libraries(Tuple
    NeoC
    Threads::Threads
)

add_executable(List Collection/List.c)
target_link_libraries(List
    NeoC
    Threads::Threads
)

add_executable(Stack Collection/Stack.c)
target_link_libraries(Stack
    NeoC
    Threads::Threads
)

add_executable(Queue Collection/Queue.c)
target_link_libraries(Queue
    NeoC
    Threads::Threads
)

add_executable(Map Collection/Map.c)
target_link_libraries(Map
    NeoC
    Threads::Threads
)

add_executable(Set Collection/Set.c)
target_link_libraries(Set
    NeoC
    Threads::Threads
)

add_executable(OOPMain OOP/Main.c OOP/Derived.c OOP/Base.c)
target_link_libraries(OOPMain
    NeoC
    Threads::Threads
)

add_executable(SampleCode SampleCode.c)
target_link_libraries(SampleCode
    NeoC
    Threads::Threads
)
