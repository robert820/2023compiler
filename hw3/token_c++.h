#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
class Token
{
public:
    int type;
    bool returnByFun = false;
    union
    {
        int _int;
        int vtype;
        double _real;
        int _bool;
        std::string _str;
        void *_ptr;
    };
};
#endif