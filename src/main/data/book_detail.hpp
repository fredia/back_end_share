//
// Created by fredia on 19-4-11.
//

#ifndef BACK_END_SHARE_BOOK_DETAIL_HPP
#define BACK_END_SHARE_BOOK_DETAIL_HPP

#include "../../include/iguana/json.hpp"
#include "../../include/mysql-orm/qualifier.hpp"

struct book_detail {
    int id;
    std::string name;
    std::string path;
    std::string imag;
    int publisher_id;
    int64_t created_time;
    int is_deleted;
};

REFLECTION(book_detail, id, name, path, imag, publisher_id, created_time, is_deleted);
orm_auto_key autok{"id"};
orm_not_null not_null{{"id", "name"}};
#endif //BACK_END_SHARE_BOOK_DETAIL_HPP
