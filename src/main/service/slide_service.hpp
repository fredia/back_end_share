//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_SLIDE_SERVICE_HPP
#define BACK_END_SHARE_SLIDE_SERVICE_HPP

#include "../storage/slide_storage.hpp"

class slide_service {
public:
    slide_service() {

    }

    void create_slide_detail_table() {
        ss.create_slide_detail_table();
    }

    void
    add_slide_detail(const std::string &name, const std::string &path, const std::string &img, const int usr_id) {
        ss.add_slide_detail(name, path, img, usr_id);
    }

    std::vector<slide_detail> get_slide_detail_by_id(int id) {
        return ss.get_slide_detail_by_id(id);
    }

    std::vector<slide_detail> get_slide_detail_by_publisher(int usr_id) {
        return ss.get_slide_detail_by_publisher(usr_id);
    }

    std::vector<slide_detail> get_slide_detail_list() {
        return ss.get_slide_detail_list();
    }

    void mark_deleted(int id) {
        std::vector<slide_detail> sv = ss.get_slide_detail_by_id(id);
        if (sv.size() != 1) {
            std::cerr << "slide not exist" << std::endl;
            return;
        }
        sv[0].is_deleted = 1;
        ss.update(sv[0]);
    }

private:
    slide_storage ss;
};

#endif //BACK_END_SHARE_SLIDE_SERVICE_HPP
