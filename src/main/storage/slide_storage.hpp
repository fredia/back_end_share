//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_SLIDE_STORAGE_HPP
#define BACK_END_SHARE_SLIDE_STORAGE_HPP

#include "../../include/mysql-orm/mysql.hpp"
#include "../data/slide_detail.hpp"

class slide_storage {
public:
    slide_storage() {
        mysql.connect(cfg);
    }

    void create_slide_detail_table() {
        mysql.create_table<slide_detail>(slide_autok, slide_not_null);
    }

    void add_slide_detail(const std::string &name, const std::string &path, const std::string &img, const int usr_id) {
        int64_t now_time = std::chrono::system_clock::now().time_since_epoch().count();
        slide_detail sd{1, name, path, img, usr_id, now_time, 0};//id是auto_key 随便写一个id即可
        mysql.insert<slide_detail>(sd);
    }

    std::vector<slide_detail> get_slide_detail_by_id(int id) {
        std::string sql = "where id=" + std::to_string(id);
        std::cout << sql << std::endl;
        return mysql.query<slide_detail>(sql);
    }

    std::vector<slide_detail> get_slide_detail_by_publisher(int usr_id) {
        std::string sql = "where publisher_id=" + std::to_string(usr_id);
        std::cout << sql << std::endl;
        return mysql.query<slide_detail>(sql);
    }

    std::vector<slide_detail> get_slide_detail_list() {
        return mysql.query<slide_detail>();
    }

    void update(const slide_detail &sd) {
        std::string sql = "where id=" + std::to_string(sd.id);
        mysql.update<slide_detail>(sd, sql);
    }

    ~slide_storage() {
    }

private:
    mysql_orm::configuration cfg{"127.0.0.1", "test", "123456789", "test", 60, 1};
    mysql_orm::mysql mysql;
};

#endif //BACK_END_SHARE_SLIDE_STORAGE_HPP
