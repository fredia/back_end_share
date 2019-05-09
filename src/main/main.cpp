#include <iostream>
#include "web/controller/book_controller.hpp"
#include "./storage/book_storage.hpp"
#include "web/controller/user_controller.hpp"

int main() {
    const int max_thread_num = 4;
    sneeze::http_server server(max_thread_num);

    bool r = server.listen("0.0.0.0", "8081");
    if (!r) {
        std::cerr << "listen failed";
        return -1;
    }
    book_controller bct;
    user_controller uct;
    server.set_http_handler<OPTIONS, POST>("/login", &user_controller::login_handler, &uct);
    server.set_http_handler<OPTIONS, POST>("/register", &user_controller::register_handler, &uct);
    server.set_http_handler<OPTIONS, POST>("/upload_book", &book_controller::upload_book_handler, &bct);
    server.set_http_handler<OPTIONS, GET>("/books", &book_controller::get_book_list_handler, &bct);
    server.set_http_handler<OPTIONS, GET>("/userBooks", &book_controller::get_user_book_list_handler, &bct);
    /* server.set_http_handler<OPTIONS, DEL>("book",);
     server.set_http_handler<OPTIONS, POST>("/upload_slide",);
     server.set_http_handler<OPTIONS, GET>("/slides",);
     server.set_http_handler<OPTIONS, DEL>("slide",);
     server.set_http_handler<OPTIONS, POST>("/upload_article",);
     server.set_http_handler<OPTIONS, GET>("/articles",);
     server.set_http_handler<OPTIONS, DEL>("/article",);
     server.set_http_handler<OPTIONS, PUT>("/update_article",);

     server.set_http_handler<OPTIONS, POST>("/login",);
     server.set_http_handler<OPTIONS, POST>("/register",);
     server.set_http_handler<OPTIONS, PUT>("/",);*/
    server.run();
    return 0;
}
