#ifndef __HASH_TABLE__
#define __HASH_TABLE__

template<typename T>
class hash_table
{
public:
    hash_table(const unsigned long long &size = 100);
    ~hash_table();
    void insert(const T& val);
    void erase(const T &val);

    unsigned long long hash_fuction(const T &val);

private:
    unsigned long long *table;
};

template <>
class hash_table<char*>
{
public:
    hash_table(const unsigned long long &size = 100);
    ~hash_table();
    void insert(const char *const _string);
    void erase(const char *const _string);

private:
    unsigned long long hash_fuction(const char *const _string);
    unsigned long long *table;
};

#endif