add_executable(med_server
  src/main.cpp
  src/ServerConfig.h
  src/ServerConfig.cpp
  src/TcpServer.h
  src/TcpServer.cpp
  src/ClientSession.h
  src/ClientSession.cpp
  src/Router.h
  src/Router.cpp
  src/handlers/AuthHandler.h
  src/handlers/AuthHandler.cpp
  src/models/User.h
  src/redis/RedisStore.h
  src/redis/RedisStore.cpp
)

target_include_directories(med_server PRIVATE src)

# 链接 Qt
target_link_libraries(med_server PRIVATE Qt5::Core Qt5::Network smartmed_common)

# 链接 Redis（优先 pkg-config）
find_package(PkgConfig REQUIRED)
pkg_check_modules(HIREDIS REQUIRED hiredis)

target_include_directories(med_server PRIVATE ${HIREDIS_INCLUDE_DIRS});
target_link_libraries(med_server PRIVATE ${HIREDIS_LIBRARIES});

pkg_check_modules(REDIS_PLUS_PLUS QUIET redis++)
if (REDIS_PLUS_PLUS_FOUND)
  target_include_directories(med_server PRIVATE ${REDIS_PLUS_PLUS_INCLUDE_DIRS});
  target_link_libraries(med_server PRIVATE ${REDIS_PLUS_PLUS_LIBRARIES});
else()
  target_link_libraries(med_server PRIVATE redis++);
endif()
