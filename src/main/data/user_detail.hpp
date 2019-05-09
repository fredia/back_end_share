//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_USER_DETAIL_HPP
#define BACK_END_SHARE_USER_DETAIL_HPP

#include "../../include/iguana/json.hpp"
#include "../../include/mysql-orm/qualifier.hpp"

struct user_detail {
    int id;
    std::string name;
    std::string imag; //头像
    std::string password;
    int role;//角色：-1代表被封禁 0：普通用户 1：管理员 2：根管理员（只有一个，系统自动分配）
};
REFLECTION(user_detail, id, name, imag, password, role);
orm_auto_key auto_user_id{"id"};
orm_not_null user_not_null{{"id", "name"}};
#endif //BACK_END_SHARE_USER_DETAIL_HPP
