project(Engineering_robot_vision CXX)
cmake_minimum_required(VERSION 3.0)

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(home /home/lqx/code/Engineering_robot_vision)

# 查找OpenCV库和yaml-cpp库
find_package(OpenCV REQUIRED)
find_package(Eigen3 3.3 REQUIRED)
find_package(Ceres REQUIRED)

file(GLOB all ${home}/*.cpp)

message(${all})

# 添加可执行文件
add_executable(main ${all})

# 链接所需的库
target_link_libraries(main
    ${OpenCV_LIBS}
)