# 项目介绍
本项目（综合性资源共享平台后端）是毕设项目（基于c++的web轻量级框架的设计与实现）的后台部分，毕设的重点部分在与web框架的设计与实现，综合性资源共享平台是对该框架可用性的一次实验验证。

主要工作如下：
- web框架
    - mysql-orm
    - sneeze(http服务器)
- 基于web框架的综合性资源共享平台(RestFul,前后端分离)
    - 后端(MVC三层架构)
    - 前端(VUE)
## web框架(SQUIRREL)

SQUIRREL框架是基于C++17标准实现的轻量级web框架,有以下特点:

- header only，方便使用
- 组件式结构，易于扩展
- RESTful风格的HTTP接口
- 支持AOP
- 支持上传下载文件
- 支持HTTP缓存
- 支持session,cookie



架构：
![](https://github.com/fredia/back_end_share/blob/master/imag/squirrel.png)

1. http组件： [sneeze](https://github.com/fredia/sneeze)
2. ORM组件： [mysql-orm](https://github.com/fredia/mysql-orm)

组件之间是松耦合的，每个模块都可单独使用，具体安装使用见[sneeze](https://github.com/fredia/sneeze)
 ，[mysql-orm](https://github.com/fredia/mysql-orm)

## 基于web框架的综合性资源共享平台

综合性资源共享平台主要包括 图书，课件，文章 三个部分，用户无需登陆（待定，是否要实现用户登陆功能）可自由预览，下载，上传这三类资源。

目前只实现了图书的上传接口(http://101.200.60.173/#/upload)

架构

![](https://github.com/fredia/back_end_share/blob/master/imag/all.png)
### 后端(MVC三层架构)

项目结构：


        ├── include
        │   ├── iguana
        │   ├── mysql-orm
        │   └── sneeze
        ├── main
        │   ├── data
        │   │   └── book_detail.hpp
        │   ├── main.cpp
        │   ├── service
        │   │   └── book_service.hpp
        │   ├── storage
        │   │   └── book_storage.hpp
        │   └── web
        │       └── book_controller.hpp
        └── test


### 前端(VUE)
项目部署在阿里云轻量级服务器上，地址：http://101.200.60.173/ 

![](https://github.com/fredia/back_end_share/blob/master/imag/vue_book.png)