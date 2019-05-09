//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_USER_CONTROLLER_HPP
#define BACK_END_SHARE_USER_CONTROLLER_HPP

#include <iostream>
#include "../../../include/sneeze/http_server.hpp"
#include "../../service/user_service.hpp"

using namespace sneeze;

class user_controller {
public:
    user_controller() {

    }

    void login_handler(request &req, response &res) {
        res.add_header("Access-Control-Allow-Origin", "http://localhost:8080");
        res.add_header("Access-Control-Allow-Credentials", "true");
        res.add_header("Access-Control-Allow-Methods", "OPTIONS, GET, PUT, POST, DELETE");
        if (req.get_method() == "OPTIONS") {
            res.add_header("Access-Control-Allow-Headers", "Authorization,content-type");
            res.render_string("");
        } else {
            std::string loginForm = req.body().data();
            nlohmann::json j = nlohmann::json::parse(loginForm);
            std::string usr_id = j.at("id");
            std::string password = j.at("password");
            if (us.auth(atoi(usr_id.c_str()), password)) {
                std::string ustr =usr_id;
                auto session = res.start_session();
                session->set_data("id", usr_id);
                session->set_max_age(3600);
                res.set_status_and_content(status_type::ok, "login success");
            } else {
                res.set_status_and_content(status_type::unauthorized, "login fail");
            }
        }
    }

    void register_handler(request &req, response &res) {
        std::string loginForm = req.body().data();
        nlohmann::json j = nlohmann::json::parse(loginForm);
        std::string name = j.at("name");
        std::string password = j.at("password");
        std::string imag = "";
        us.add_user(name, password, imag);
    }

    void delete_handler(request &req, response &res) {
    }

private:
    user_service us;

};

#endif //BACK_END_SHARE_USER_CONTROLLER_HPP
