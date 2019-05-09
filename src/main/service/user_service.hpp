//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_USER_SERVICE_HPP
#define BACK_END_SHARE_USER_SERVICE_HPP

#include <string>
#include "../storage/user_storage.hpp"

class user_service {
public:
    user_service() {

    }

    bool auth(int id, std::string password) {
        std::vector<user_detail> uv = us.get_user_by_id(id);
        if (uv.size() != 1) {
            return false;
        }
        return uv[0].password == password;
    }

    void add_user(const std::string name, const std::string password, const std::string imag) {
        us.add_user(name, password, imag, 0);//普通用户
    }

    void grant_role(int id, int role) {
        std::vector<user_detail> uv = us.get_user_by_id(id);
        if (uv.size() != 1) {
            std::cerr << "user not exist" << std::endl;
            return;
        }
        uv[0].role = role;
        us.update(uv[0]);
    }

    std::vector<user_detail> get_user_by_id(int id) {
        return us.get_user_by_id(id);
    }


private:
    user_storage us;
};

#endif //BACK_END_SHARE_USER_SERVICE_HPP
