//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_USER_LOGIC_HPP
#define BACK_END_SHARE_USER_LOGIC_HPP

#include <string>
#include "../../service/user_service.hpp"

class user_logic {
public:
    user_logic() {

    }

    bool auth(int id, std::string password) {
        return us.auth(id, password);
    }

    int register_user(const std::string &name, const std::string &password, const std::string &imag) {
        us.add_user(name, password, imag);
    }

private:
    user_service us;
};

#endif //BACK_END_SHARE_USER_LOGIC_HPP
