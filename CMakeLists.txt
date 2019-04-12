cmake_minimum_required(VERSION 3.13)
project(back_end_share)

set(CMAKE_CXX_STANDARD 17)
#添加头文件搜索路径
include_directories(/usr/include)

#添加库文件搜索路径
link_directories(/usr/lib)

find_package(Boost REQUIRED)

add_executable(back_end_share src/main/main.cpp src/main/service/book_service.hpp src/main/storage/book_storage.hpp src/main/web/book_controller.hpp src/main/data/book_detail.hpp)
target_link_libraries(back_end_share pthread boost_system uuid stdc++fs mysqlclient)