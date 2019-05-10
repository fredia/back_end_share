//
// Created by fredia on 19-4-11.
//

#ifndef BACK_END_SHARE_BOOK_SERVICE_HPP
#define BACK_END_SHARE_BOOK_SERVICE_HPP

#include "../storage/book_storage.hpp"

class book_service {
public:
    book_service() {

    }

    void create_book_detail_table() {
        bs.create_book_detail_table();
    }

    void
    add_book_detail(const std::string &name, const std::string &path, const std::string &img, const int usr_id) {
        bs.add_book_detail(name, path, img, usr_id);
    }

    std::vector<book_detail> get_book_detail_by_id(int id) {
        return bs.get_book_detail_by_id(id);
    }

    std::vector<book_detail> get_book_detail_by_publisher(int usr_id) {
        return bs.get_book_detail_by_publisher(usr_id);
    }

    std::vector<book_detail> get_book_detail_list() {
        return bs.get_book_detail_list();
    }

    void mark_deleted(int id) {
        std::vector<book_detail> bv = bs.get_book_detail_by_id(id);
        if (bv.size() != 1) {
            std::cerr << "book not exist" << std::endl;
            return;
        }
        bv[0].is_deleted = 1;
        bs.update(bv[0]);
    }

private:
    book_storage bs;
};

#endif //BACK_END_SHARE_BOOK_SERVICE_HPP
