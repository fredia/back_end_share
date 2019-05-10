//
// Created by fredia on 19-5-9.
//

#ifndef BACK_END_SHARE_ARTICLE_SERVICE_HPP
#define BACK_END_SHARE_ARTICLE_SERVICE_HPP

#include "../storage/article_storage.hpp"

class article_service {
public:
    article_service() {

    }

    void create_article_detail_table() {
        as.create_article_detail_table();
    }

    void add_article_detail(const std::string &name, const std::string &abstract, const std::string &content,
                            const int usr_id) {
        as.add_artilce_detail(name, abstract, content, usr_id);
    }

    std::vector<article_detail> get_article_detail_by_id(int id) {
        return as.get_article_detail_by_id(id);
    }

    std::vector<article_detail> get_article_detail_by_publisher(int usr_id) {
        return as.get_article_detail_by_publisher(usr_id);
    }

    std::vector<article_detail> get_article_detail_list() {
        return as.get_book_detail_list();
    }

    void update(article_detail &ad) {
        as.update(ad);
    }

    void mark_deleted(int id) {
        std::vector<article_detail> av = as.get_article_detail_by_id(id);
        if (av.size() != 1) {
            std::cerr << "article not exist" << std::endl;
            return;
        }
        av[0].is_deleted = 1;
        as.update(av[0]);
    }

private:
    article_storage as;
};

#endif //BACK_END_SHARE_ARTICLE_SERVICE_HPP
