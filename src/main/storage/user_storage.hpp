//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_USER_STORAGE_HPP
#define BACK_END_SHARE_USER_STORAGE_HPP

#include "../../include/mysql-orm/mysql.hpp"
#include "../data/user_detail.hpp"

class user_storage {
public:
    user_storage() {
        mysql.connect(cfg);
    }

    void create_user_detail_table() {
        mysql.create_table<user_detail>(auto_user_id, user_not_null);
    }

    void add_user(const std::string &name, const std::string &password, const std::string &imag, const int role) {
        user_detail ud{1, name, imag, password, role};
        mysql.insert<user_detail>(ud);
    }

    std::vector<user_detail> get_user_by_id(int id) {
        std::string sql = "where id=" + std::to_string(id);
        std::cout << sql << std::endl;
        return mysql.query<user_detail>(sql);
    }

    void update(const user_detail &ud) {
        std::string sql = "where id=" + std::to_string(ud.id);
        std::cout << sql << std::endl;
        mysql.update<user_detail>(ud, sql);
    }

private:
    mysql_orm::configuration cfg{"127.0.0.1", "test", "123456789", "test", 60, 1};
    mysql_orm::mysql mysql;
};

#endif //BACK_END_SHARE_USER_STORAGE_HPP
