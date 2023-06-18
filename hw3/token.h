#ifndef TOKEN_H
#define TOKEN_H
typedef struct Token
{
    int type;
    bool returnByFun;
    union
    {
        int _int;
        int vtype;
        double _real;
        int _bool;
        char *_str;
        void *_ptr;
    };
} Token;
#endif