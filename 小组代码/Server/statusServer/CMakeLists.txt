cmake_minimum_required(VERSION 3.29)
project(statusServer)

set(CMAKE_CXX_STANDARD 14)
#添加头文件搜索路径
include_directories(/usr/local/include)
#添加库文件搜索路径
include_directories(/usr/include)
link_directories(/usr/local/lib)
include_directories(/usr/include/jsoncpp)
link_directories(/usr/lib/x86_64-linux-gnu)

# 设置gRPC和Protobuf的头文件路径
include_directories("/usr/local/include/grpc")
include_directories("/usr/local/include/google/protobuf")
#设置hiredis库头文件和库文件
include_directories(/usr/include/hiredis)

# 设置gRPC和Protobuf的库文件路径
link_directories("/usr/local/lib")
link_directories("/usr/local/lib")
find_library(MYSQLCPPCONN_LIB mysqlcppconn PATHS /usr/lib/x86_64-linux-gnu)
find_package(absl REQUIRED)
# 查找Boost库
#find_package(Boost 1.70 REQUIRED COMPONENTS system filesystem)
#find_package(Boost 1.86 REQUIRED COMPONENTS system filesystem)
find_package(Boost REQUIRED)

add_executable(statusServer main.cpp
        AsioIOServicePool.cpp
        AsioIOServicePool.h
        ChatGrpcClient.cpp
        ChatGrpcClient.h
        ConfigMgr.cpp
        ConfigMgr.h
        const.h
        MysqlDao.cpp
        MysqlDao.h
        MysqlMgr.cpp
        MysqlMgr.h
        RedisMgr.cpp
        RedisMgr.h
        Singleton.h
        StatusServiceImpl.cpp
        StatusServiceImpl.h
        message.grpc.pb.cc
        message.pb.cc)

# 链接Boost库
target_link_libraries(statusServer
        /usr/local/lib/libboost_system.so.1.86.0
        /usr/local/lib/libboost_filesystem.so.1.86.0
        /usr/local/lib/libboost_thread.so.1.86.0
        pthread)

target_link_libraries(statusServer /usr/lib/x86_64-linux-gnu/libjsoncpp.so)
# 链接gRPC和Protobuf库
target_link_libraries(statusServer
        grpc++        # gRPC C++ 库
        grpc          # gRPC 库
        grpc++_reflection # gRPC 反射库
        gpr           # gRPC 支持库
        protobuf      # Protobuf 库
        pthread       # POSIX 线程库，gRPC 需要
        ssl           # OpenSSL 库，gRPC 可能需要
        crypto        # OpenSSL 库，gRPC 可能需要
        protobuf        # Protobuf 核心库
        absl::base
        absl::strings
        absl::status

)
# 链接其他库
target_link_libraries(statusServer
        /usr/lib/x86_64-linux-gnu/libjsoncpp.so
        grpc++        # gRPC C++ 库
        grpc          # gRPC 库
        grpc++_reflection # gRPC 反射库
        gpr           # gRPC 支持库
        ssl           # OpenSSL 库
        crypto        # OpenSSL 库
        protobuf      # Protobuf 核心库
        absl::base
        absl::strings
        absl::status
        absl::synchronization
        -lpthread
        -lrt
        -lz  # 添加 zlib 库
        -lcares  # 添加 c-ares 库
        -lre2  # 添加 re2 库
        -lupb  # 添加 upb 库
        -laddress_sorting  # 添加 Address Sorting 库
        /usr/local/lib/libabsl_stacktrace.a
        /usr/local/lib/libabsl_symbolize.a
        /usr/local/lib/libabsl_debugging_internal.a
        /usr/local/lib/libabsl_demangle_internal.a
        /usr/local/lib/libabsl_malloc_internal.a
        /usr/local/lib/libabsl_cord.a
        /usr/local/lib/libabsl_str_format_internal.a
        /usr/local/lib/libabsl_spinlock_wait.a
        /usr/local/lib/libabsl_strings_internal.a
        /usr/local/lib/libabsl_int128.a
        /usr/local/lib/libabsl_throw_delegate.a
        /usr/local/lib/libabsl_bad_optional_access.a
        /usr/local/lib/libabsl_raw_logging_internal.a
        /usr/local/lib/libabsl_log_severity.a
        /usr/local/lib/libabsl_time.a
        /usr/local/lib/libabsl_base.a
)

target_link_libraries(statusServer hiredis)
target_link_libraries(statusServer ${MYSQLCPPCONN_LIB})

