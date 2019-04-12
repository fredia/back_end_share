#include <iostream>
#include "./web/book_controller.hpp"
#include "./storage/book_storage.hpp"

int main() {
    const int max_thread_num = 4;
    sneeze::http_server server(max_thread_num);

    bool r = server.listen("0.0.0.0", "8081");
    if (!r) {
        std::cerr << "listen failed";
        return -1;
    }
    book_controller bct;
    server.set_http_handler<POST, OPTIONS>("/upload_book", &book_controller::upload_book_handler, &bct);
    server.set_http_handler<GET, OPTIONS>("/books", &book_controller::get_book_list, &bct);
    server.run();
    return 0;
}
