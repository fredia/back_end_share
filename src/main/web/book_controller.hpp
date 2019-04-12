//
// Created by fredia on 19-4-11.
//

#ifndef BACK_END_SHARE_BOOK_CONTROLLER_HPP
#define BACK_END_SHARE_BOOK_CONTROLLER_HPP

#include <iostream>
#include "../../include/sneeze/http_server.hpp"
#include "../storage/book_storage.hpp"

using namespace sneeze;

class book_controller {
public:
    book_controller() {
        bs.create_book_detail_table();
    }

    void upload_book_handler(request &req, response &res) {
        res.add_header("Access-Control-Allow-Origin", "*");
        if (req.get_method() == "OPTIONS") {
            res.add_header("Access-Control-Allow-Headers", "Authorization");
            res.render_string("");
        } else {
            assert(req.get_content_type() == content_type::multipart);
            std::string name = req.get_query_value("name");
            auto &files = req.get_upload_files();
            if (files.size() != 2) {
                res.set_status_and_content(status_type::bad_request, "must upload 2 files!!!");
                return;
            }
            std::cout << files[0].get_file_path() << " " << files[1].get_file_path() << std::endl;
            bs.add_book_detail(name, files[0].get_file_path(), files[1].get_file_path());
            res.render_string("OK");
        }
    }

    void get_book_list(request &req, response &res) {
        res.add_header("Access-Control-Allow-Origin", "*");
        if (req.get_method() == "OPTIONS") {
            res.add_header("Access-Control-Allow-Headers", "Authorization");
            res.render_string("");
        } else {
            std::vector<book_detail> books = bs.get_book_detail_list();
            res.render_string(to_json(books));
        }
    }

    std::string to_json(std::vector<book_detail> &books) {
        std::string baseUrl = "http://101.200.60.173:8081";
        std::string str = "[";
        for (auto book:books) {
            nlohmann::json bd;
            bd["name"] = book.name;
            bd["id"] = book.id;
            bd["path"] = baseUrl + book.path.substr(1);
            bd["imag"] = baseUrl + book.imag.substr(1);
            std::string tmp = bd.dump();
            str += tmp;
            str += ",";
        }
        str[str.size() - 1] = ']';
        std::cout << str << std::endl;
        return str;
    }

private:
    book_storage bs;
};

#endif //BACK_END_SHARE_BOOK_CONTROLLER_HPP
