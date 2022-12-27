#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"

class Database
{
    User parse_user;
    public:
    Database() : parse_user{} {}
    void fill_in_object();
};

#endif // DATABASE_H
