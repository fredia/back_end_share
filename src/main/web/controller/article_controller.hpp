//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_ARTICLE_CONTROLLER_HPP
#define BACK_END_SHARE_ARTICLE_CONTROLLER_HPP

#include <iostream>
#include "../../../include/sneeze/http_server.hpp"
#include "../../service/article_service.hpp"
#include "../../service/user_service.hpp"

using namespace sneeze;

class article_controller {
public:
    article_controller() {
        as.create_article_detail_table();
    }

    void set_res(response &res) {
        res.add_header("Access-Control-Allow-Origin", "http://localhost:8080");
        res.add_header("Access-Control-Allow-Credentials", "true");
        res.add_header("Access-Control-Allow-Headers",
                       "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Authorization , Access-Control-Request-Headers");
    }

    void upload_article_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            auto ptr = req.get_session();
            auto session = ptr.lock();

            std::string article = req.body().data();
            nlohmann::json j = nlohmann::json::parse(article);
            std::string user_id = j.at("publisher");
            std::string title = j.at("title");
            std::string abstract = j.at("abstract");
            std::string content = j.at("content");

            if (session == nullptr || session->get_data<std::string>("id") != user_id) {
                res.set_status_and_content(status_type::unauthorized, "unauthorized");
                return;
            }
            as.add_article_detail(title, abstract, content, atoi(user_id.c_str()));
            res.render_string("OK");
        }
    }

    void get_article_list_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            std::vector<article_detail> articles = as.get_article_detail_list();
            res.render_string(to_json(articles));
            return;
        }
    }

    void get_user_article_list_handler(request &req, response &res) {
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
                std::vector<article_detail> articles = as.get_article_detail_by_publisher(usr_id);
                res.render_string(to_json(articles));
            } else {
                std::vector<article_detail> articles = as.get_article_detail_list();
                res.render_string(to_json(articles));
            }
            return;
        }
    }

    void delete_article_handler(request &req, response &res) {
        set_res(res);
        if (req.get_method() == "OPTIONS") {
            res.render_string("");
        } else {
            auto ptr = req.get_session();
            auto session = ptr.lock();
            std::string user_id = req.get_query_value("user");
            std::string article_id = req.get_query_value("article");
            if (session == nullptr || session->get_data<std::string>("id") != user_id) {
                res.set_status_and_content(status_type::unauthorized, "unauthorized");
                return;
            }
            int usr_id = atoi(user_id.c_str());
            int art_id = atoi(article_id.c_str());
            std::vector<user_detail> uv = us.get_user_by_id(usr_id);
            if (uv.size() != 1) {
                res.set_status_and_content(status_type::bad_request, "bad request");
                return;
            }
            if (uv[0].role == 0) { // 普通用户
                std::vector<article_detail> articles = as.get_article_detail_by_id(art_id);
                if (articles.size() != 1) {
                    res.set_status_and_content(status_type::bad_request, "article not exist");
                    return;
                }
                if (articles[0].publisher_id != usr_id) {
                    res.set_status_and_content(status_type::forbidden, "forbidden");
                    return;
                }
                as.mark_deleted(art_id);
                res.set_status_and_content(status_type::ok, "delete success");
            } else if (uv[0].role >= 1) { //管理员，根管理员
                as.mark_deleted(art_id);
                res.set_status_and_content(status_type::ok, "delete success");
            }
            return;
        }

    }

    std::string to_json(std::vector<article_detail> &articles) {
        std::string str = "[";
        for (auto article:articles) {
            if (article.is_deleted != 1) {
                nlohmann::json ad;
                ad["title"] = article.name;
                ad["id"] = article.id;
                ad["abstract"] = article.abstract;
                ad["content"] = article.content;
                ad["createdTime"] = article.created_time;
                ad["publisher"] = article.publisher_id;
                std::string tmp = ad.dump();
                str += tmp;
                str += ",";
            }
        }
        str[str.size() - 1] = ']';
        std::cout << str << std::endl;
        return str;
    }

private:
    article_service as;
    user_service us;

};

#endif //BACK_END_SHARE_ARTICLE_CONTROLLER_HPP
