add_library(smartmed_common
  src/Protocol.cpp
  src/Utils.cpp
)

target_include_directories(smartmed_common PUBLIC include)
target_link_libraries(smartmed_common PUBLIC Qt5::Core)
