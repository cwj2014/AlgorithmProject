#include "algorithm_impl_test.h"
#include <mysql/mysql.h>

void mysqlTest(){
    MYSQL mysql;  
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql_init(&mysql);
    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *passwd = "cai123456";
    const char *db = "yiibaidb";
    unsigned int port = 3306;
    if(mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, 0)){
        std::cout << "mysql_real_connect success\n";
        if(!mysql_query(&mysql, "select orderNumber, status from orders;")){
            std::cout << "mysql_query failed\n";
        }
        if((result = mysql_store_result(&mysql)) != NULL){
            int cols = mysql_num_fields(result);
            int rows = mysql_num_rows(result);
            std::cout << "search "<<rows<<" rows"<<std::endl;
            MYSQL_FIELD* fields = NULL;
            while((fields = mysql_fetch_field(result))!=NULL){
                std::cout <<fields->name;
                std::cout <<"********|";
            }
            std::cout << "\n";
            while((row = mysql_fetch_row(result))!=NULL){
                for(int j=0; j<cols; j++){
                    std::cout <<row[j];
                    std::cout <<"********|";
                }
                std::cout << "\n";
            }
            // for(int i=0; i<rows; i++){
            //     row = mysql_fetch_row(result);
            //     for(int j=0; j<cols; j++){
            //         std::cout <<row[j];
            //         std::cout <<"********|";
            //     }
            //     std::cout << "\n";

            // }
        }
    }else{
        std::cout << "mysql_real_connect failed\n";
    }
    mysql_close(&mysql);
}