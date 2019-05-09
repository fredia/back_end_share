//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_ARTICLE_DETAIL_HPP
#define BACK_END_SHARE_ARTICLE_DETAIL_HPP

#include "../../include/iguana/json.hpp"
#include "../../include/mysql-orm/qualifier.hpp"

struct article_detail {
    int id;
    std::string name;
    std::string abstract;
    std::string content;
    std::string imag;
    int publisher_id;
    int64_t created_time;
    int64_t updated_time;
    int is_deleted;
};

REFLECTION(article_detail, id, name, abstract, content, imag, publisher_id, created_time, updated_time, is_deleted);
orm_auto_key autok{"id"};
orm_not_null not_null{{"id", "name"}};
#endif //BACK_END_SHARE_ARTICLE_DETAIL_HPP
