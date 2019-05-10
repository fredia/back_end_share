//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_ARTICLE_STORAGE_HPP
#define BACK_END_SHARE_ARTICLE_STORAGE_HPP

#include "../../include/mysql-orm/configuration.hpp"
#include "../../include/mysql-orm/mysql.hpp"
#include "../data/article_detail.hpp"

class article_storage {
public:
    article_storage() {
        mysql.connect(cfg);
    }

    void create_article_detail_table() {
        mysql.create_table<article_detail>();
    }

    void add_artilce_detail(const std::string &name, const std::string &abstract, const std::string &content,
                            const int usr_id) {
        int64_t now_time = std::chrono::system_clock::now().time_since_epoch().count();
        article_detail ad{1, name, abstract, content, usr_id, now_time, 0, 0};//id是auto_key 随便写一个id即可
        mysql.insert(ad);
    }

    std::vector<article_detail> get_article_detail_by_id(int id) {
        std::string sql = "where id=" + std::to_string(id);
        std::cout << sql << std::endl;
        return mysql.query<article_detail>(sql);
    }

    std::vector<article_detail> get_article_detail_by_publisher(int usr_id) {
        std::string sql = "where publisher_id=" + std::to_string(usr_id);
        std::cout << sql << std::endl;
        return mysql.query<article_detail>(sql);
    }

    std::vector<article_detail> get_book_detail_list() {
        return mysql.query<article_detail>();
    }

    void update(article_detail &ad) {
        std::string sql = "where id=" + std::to_string(ad.id);
        int64_t now_time = std::chrono::system_clock::now().time_since_epoch().count();
        ad.updated_time = now_time;
        mysql.update<article_detail>(ad, sql);
    }

    ~article_storage() {
    }

private:
    mysql_orm::configuration cfg{"127.0.0.1", "test", "123456789", "test", 60, 1};
    mysql_orm::mysql mysql;
};

#endif //BACK_END_SHARE_ARTICLE_STORAGE_HPP
