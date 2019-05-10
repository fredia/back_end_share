//
// Created by fredia on 19-4-11.
//

#ifndef BACK_END_SHARE_BOOK_CONTROLLER_HPP
#define BACK_END_SHARE_BOOK_CONTROLLER_HPP

#include <iostream>
#include "../../../include/sneeze/http_server.hpp"
#include "../../service/book_service.hpp"
#include "../../service/user_service.hpp"

using namespace sneeze;

class book_controller {
public:
    book_controller() {
        bs.create_book_detail_table();
    }

    void set_res(response &res) {
        res.add_header("Access-Control-Allow-Origin", "http://localhost:8080");
        res.add_header("Access-Control-Allow-Credentials", "true");
        res.add_header("Access-Control-Allow-Headers",
                       "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Authorization , Access-Control-Request-Headers");
    }

    void upload_book_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            assert(req.get_content_type() == content_type::multipart);
            std::string name = req.get_query_value("name");
            auto &files = req.get_upload_files();
            auto ptr = req.get_session();
            auto session = ptr.lock();
            std::string user_id = req.get_query_value("user");
            if (session == nullptr || session->get_data<std::string>("id") != user_id) {
                res.set_status_and_content(status_type::unauthorized, "unauthorized");
                return;
            }
            int usr_id = atoi(user_id.c_str());
            if (files.size() != 2) {
                res.set_status_and_content(status_type::bad_request, "must upload 2 files!!!");
                return;
            }
            std::cout << files[0].get_file_path() << " " << files[1].get_file_path() << std::endl;
            bs.add_book_detail(name, files[0].get_file_path(), files[1].get_file_path(), usr_id);
            res.render_string("OK");
        }
    }

    void get_book_list_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            std::vector<book_detail> books = bs.get_book_detail_list();
            res.render_string(to_json(books));
            return;
        }
    }

    void get_user_book_list_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            auto ptr = req.get_session();
            auto session = ptr.lock();
            std::string user_id = req.get_query_value("user");
            if (session == nullptr || session->get_data<std::string>("id") != user_id) {
                res.set_status_and_content(status_type::unauthorized, "unauthorized");
                return;
            }
            int usr_id = atoi(user_id.c_str());
            std::vector<user_detail> uv = us.get_user_by_id(usr_id);
            if (uv.size() != 1) {
                res.set_status_and_content(status_type::bad_request, "bad request");
                return;
            }
            if (uv[0].role == 0) {
                std::vector<book_detail> books = bs.get_book_detail_by_publisher(usr_id);
                res.render_string(to_json(books));
            } else {
                std::vector<book_detail> books = bs.get_book_detail_list();
                res.render_string(to_json(books));
            }
            return;
        }
    }

    void delete_book_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            auto ptr = req.get_session();
            auto session = ptr.lock();
            std::string user_id = req.get_query_value("user");
            std::string book_id = req.get_query_value("book");
            if (session == nullptr || session->get_data<std::string>("id") != user_id) {
                res.set_status_and_content(status_type::unauthorized, "unauthorized");
                return;
            }
            int usr_id = atoi(user_id.c_str());
            int bok_id = atoi(book_id.c_str());
            std::vector<user_detail> uv = us.get_user_by_id(usr_id);
            if (uv.size() != 1) {
                res.set_status_and_content(status_type::bad_request, "bad request");
                return;
            }
            if (uv[0].role == 0) { // 普通用户
                std::vector<book_detail> books = bs.get_book_detail_by_id(bok_id);
                if (books.size() != 1) {
                    res.set_status_and_content(status_type::bad_request, "book not exist");
                    return;
                }
                if (books[0].publisher_id != usr_id) {
                    res.set_status_and_content(status_type::forbidden, "forbidden");
                    return;
                }
                bs.mark_deleted(bok_id);
                res.set_status_and_content(status_type::ok, "delete success");
            } else if (uv[0].role >= 1) { //管理员，根管理员
                bs.mark_deleted(bok_id);
                res.set_status_and_content(status_type::ok, "delete success");
            }
            return;
        }

    }

    std::string to_json(std::vector<book_detail> &books) {
        std::string baseUrl = "http://101.200.60.173:8081";
        std::string str = "[";
        for (auto book:books) {
            if (book.is_deleted != 1) {
                nlohmann::json bd;
                bd["name"] = book.name;
                bd["id"] = book.id;
                bd["path"] = baseUrl + book.path.substr(1);
                bd["imag"] = baseUrl + book.imag.substr(1);
                bd["createdTime"] = book.created_time;
                bd["publisher"] = book.publisher_id;
                std::string tmp = bd.dump();
                str += tmp;
                str += ",";
            }
        }
        str[str.size() - 1] = ']';
        std::cout << str << std::endl;
        return str;
    }

private:
    book_service bs;
    user_service us;
};

#endif //BACK_END_SHARE_BOOK_CONTROLLER_HPP
