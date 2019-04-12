//
// Created by fredia on 19-4-11.
//

#ifndef BACK_END_SHARE_BOOK_STORAGE_HPP
#define BACK_END_SHARE_BOOK_STORAGE_HPP

#include "../../include/mysql-orm/mysql.hpp"
#include "../data/book_detail.hpp"

class book_storage {
public:
    book_storage() {
        mysql.connect(cfg);
    }

    void create_book_detail_table() {
        mysql.create_table<book_detail>(autok, not_null);
    }

    void add_book_detail(const std::string name, const std::string path, const std::string img) {
        book_detail bd{1, name, path, img};//id是auto_key 随便写一个id即可
        mysql.insert(bd);
    }

    std::vector<book_detail> get_book_detail_by_name(std::string name) {
        return mysql.query<book_detail>("where name='" + name + "'");
    }

    std::vector<book_detail> get_book_detail_by_id(int id) {
        std::string sql = "where id=" + std::to_string(id);
        std::cout << sql << std::endl;
        return mysql.query<book_detail>(sql);
    }

    std::vector<book_detail> get_book_detail_list() {
        return mysql.query<book_detail>();
    }

private:
    mysql_orm::configuration cfg{"127.0.0.1", "test", "123456789", "test", 60, 1};
    mysql_orm::mysql mysql;
};


#endif //BACK_END_SHARE_BOOK_STORAGE_HPP
