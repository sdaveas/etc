include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(CommSquareLibs FileReader.hpp Regex.hpp)
target_link_libraries(CommSquareLibs)
set_property(TARGET CommSquareLibs PROPERTY CXX_STANDARD 17)
