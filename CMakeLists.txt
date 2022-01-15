cmake_minimum_required(VERSION 3.5)
project(color_names)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

include_directories(
  include
)

add_library(color_names SHARED
  src/color_names.cpp
)
ament_target_dependencies(color_names
  rclcpp
  std_msgs
)
ament_export_targets(export_color_names HAS_LIBRARY_TARGET)
ament_export_libraries(color_names)

add_executable(view_all
  src/view_all.cpp
)
target_link_libraries(view_all color_names)
ament_target_dependencies(view_all
  rclcpp
  std_msgs
  visualization_msgs
)

install(TARGETS
  view_all
  DESTINATION lib/color_names
)

# Install header files
install(
  DIRECTORY "include/"
  DESTINATION include
)

install(TARGETS color_names
EXPORT export_color_names
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

#############
## Install ##
#############
install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_libraries(color_names)
ament_export_include_directories(include)
ament_package()
