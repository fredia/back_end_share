//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_SLIDE_CONTROLLER_HPP
#define BACK_END_SHARE_SLIDE_CONTROLLER_HPP

#include <iostream>
#include "../../../include/sneeze/http_server.hpp"
#include "../../service/slide_service.hpp"
#include "../../service/user_service.hpp"

using namespace sneeze;

class slide_controller {
public:
    slide_controller() {
        ss.create_slide_detail_table();
    }

    void set_res(response &res) {
        res.add_header("Access-Control-Allow-Origin", "http://localhost:8080");
        res.add_header("Access-Control-Allow-Credentials", "true");
        res.add_header("Access-Control-Allow-Headers",
                       "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Authorization , Access-Control-Request-Headers");
    }

    void upload_slide_handler(request &req, response &res) {
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
            ss.add_slide_detail(name, files[0].get_file_path(), files[1].get_file_path(), usr_id);
            res.render_string("OK");
        }
    }

    void get_book_list_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            std::vector<slide_detail> slides = ss.get_slide_detail_list();
            res.render_string(to_json(slides));
            return;
        }
    }

    void get_user_slide_list_handler(request &req, response &res) {
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
                std::vector<slide_detail> slides = ss.get_slide_detail_by_publisher(usr_id);
                res.render_string(to_json(slides));
            } else {
                std::vector<slide_detail> slides = ss.get_slide_detail_list();
                res.render_string(to_json(slides));
            }
            return;
        }
    }

    void delete_slide_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            auto ptr = req.get_session();
            auto session = ptr.lock();
            std::string user_id = req.get_query_value("user");
            std::string slide_id = req.get_query_value("slide");
            if (session == nullptr || session->get_data<std::string>("id") != user_id) {
                res.set_status_and_content(status_type::unauthorized, "unauthorized");
                return;
            }
            int usr_id = atoi(user_id.c_str());
            int sld_id = atoi(slide_id.c_str());
            std::vector<user_detail> uv = us.get_user_by_id(usr_id);
            if (uv.size() != 1) {
                res.set_status_and_content(status_type::bad_request, "bad request");
                return;
            }
            if (uv[0].role == 0) { // 普通用户
                std::vector<slide_detail> slides = ss.get_slide_detail_by_id(sld_id);
                if (slides.size() != 1) {
                    res.set_status_and_content(status_type::bad_request, "slide not exist");
                    return;
                }
                if (slides[0].publisher_id != usr_id) {
                    res.set_status_and_content(status_type::forbidden, "forbidden");
                    return;
                }
                ss.mark_deleted(sld_id);
                res.set_status_and_content(status_type::ok, "delete success");
            } else if (uv[0].role >= 1) { //管理员，根管理员
                ss.mark_deleted(sld_id);
                res.set_status_and_content(status_type::ok, "delete success");
            }
            return;
        }
    }

    std::string to_json(std::vector<slide_detail> &slides) {
        std::string baseUrl = "http://101.200.60.173:8081";
        std::string str = "[";
        for (auto slide:slides) {
            if (slide.is_deleted != 1) {
                nlohmann::json sd;
                sd["name"] = slide.name;
                sd["id"] = slide.id;
                sd["path"] = baseUrl + slide.path.substr(1);
                sd["imag"] = baseUrl + slide.imag.substr(1);
                sd["createdTime"] = slide.created_time;
                sd["publisher"] = slide.publisher_id;
                std::string tmp = sd.dump();
                str += tmp;
                str += ",";
            }
        }
        str[str.size() - 1] = ']';
        std::cout << str << std::endl;
        return str;
    }

private:
    slide_service ss;
    user_service us;

};

#endif //BACK_END_SHARE_SLIDE_CONTROLLER_HPP
