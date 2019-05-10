#include <iostream>
#include "web/controller/book_controller.hpp"
#include "./storage/book_storage.hpp"
#include "web/controller/user_controller.hpp"
#include "web/controller/article_controller.hpp"
#include "web/controller/slide_controller.hpp"

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
    article_controller act;
    slide_controller sct;
    server.set_http_handler<OPTIONS, POST>("/login", &user_controller::login_handler, &uct);
    server.set_http_handler<OPTIONS, POST>("/register", &user_controller::register_handler, &uct);


    server.set_http_handler<OPTIONS, POST>("/uploadBook", &book_controller::upload_book_handler, &bct);
    server.set_http_handler<OPTIONS, GET>("/books", &book_controller::get_book_list_handler, &bct);
    server.set_http_handler<OPTIONS, GET>("/userBooks", &book_controller::get_user_book_list_handler, &bct);
    server.set_http_handler<OPTIONS, DEL>("/book", &book_controller::delete_book_handler, &bct);

    server.set_http_handler<OPTIONS, POST>("/uploadSlide", &slide_controller::upload_slide_handler, &sct);
    server.set_http_handler<OPTIONS, GET>("/slides", &slide_controller::get_book_list_handler, &sct);
    server.set_http_handler<OPTIONS, GET>("/userSlide", &slide_controller::get_user_slide_list_handler, &sct);
    server.set_http_handler<OPTIONS, DEL>("/slide", &slide_controller::delete_slide_handler, &sct);


    server.set_http_handler<OPTIONS, POST>("/uploadArticle", &article_controller::upload_article_handler, &act);
    server.set_http_handler<OPTIONS, GET>("/articles", &article_controller::get_article_list_handler, &act);
    server.set_http_handler<OPTIONS, GET>("/userArticle", &article_controller::get_user_article_list_handler, &act);
    server.set_http_handler<OPTIONS, DEL>("/article", &article_controller::delete_article_handler, &act);


    server.run();
    return 0;
}
