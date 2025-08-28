add_executable(patient_client
  src/main.cpp
  src/App.h
  src/App.cpp
  src/net/ClientSocket.h
  src/net/ClientSocket.cpp
  src/ui/LoginWindow.h
  src/ui/LoginWindow.cpp
  src/ui/PatientHomeWindow.h
  src/ui/PatientHomeWindow.cpp
)

target_include_directories(patient_client PRIVATE src)
target_link_libraries(patient_client PRIVATE Qt5::Core Qt5::Network Qt5::Widgets smartmed_common)
