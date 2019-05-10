cmake_minimum_required(VERSION 3.13)
project(back_end_share)

set(CMAKE_CXX_STANDARD 17)
#添加头文件搜索路径
include_directories(/usr/include)

#添加库文件搜索路径
link_directories(/usr/lib)

find_package(Boost REQUIRED)

add_executable(back_end_share src/main/main.cpp src/main/service/book_service.hpp src/main/storage/book_storage.hpp src/main/web/controller/book_controller.hpp src/main/data/book_detail.hpp src/main/web/dataVO/bookVO.hpp src/main/data/user_detail.hpp src/main/data/slide_detail.hpp src/main/data/article_detail.hpp src/main/web/controller/slide_controller.hpp src/main/web/controller/article_controller.hpp src/main/web/logic/book_logic.hpp src/main/web/logic/slide_logic.hpp src/main/web/logic/article_logic.hpp src/main/web/dataVO/slideVO.hpp src/main/web/dataVO/articleVO.hpp src/main/web/controller/user_controller.hpp src/main/web/dataVO/userVO.hpp src/main/web/logic/user_logic.hpp src/main/service/slide_service.hpp src/main/service/article_service.hpp src/main/service/user_service.hpp src/main/storage/user_storage.hpp src/main/storage/slide_storage.hpp src/main/storage/article_storage.hpp src/main/configuration/mysql_config.hpp)
target_link_libraries(back_end_share pthread boost_system uuid stdc++fs mysqlclient)