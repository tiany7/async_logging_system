//
// Created by tiany on 2022/8/16.
//

#ifndef EFFICIENT_LOGGING_SYSTEM_FASTLOG_H
#define EFFICIENT_LOGGING_SYSTEM_FASTLOG_H
#include <iostream>
#include <string>
#include <regex>
#include <set>
#include "async_logger.h"
#include "util.h"
template<typename T>
class modifyArgLog
{
public:
    modifyArgLog(T const& r, std::vector<std::string> &nameList) : ref(r)
    {
        name = nameList[0];
        nameList.erase(nameList.begin());
    }

    friend std::ostream& operator<< (std::ostream & os, const modifyArgLog<T>   &s) {
        if (s.name.find('\"') != std::string::npos)
            return os <<s.name<<", ";
        return os << s.name << " = " << s.ref <<", ";
    }
private:
    T const& ref;
    std::string name;
};

template<typename ...Args>
void testLog(std::ostringstream & os, const char* dir, const char* func, int lineno,  const std::string &name, Args && ...args)
{
    os<< dir<<":"<< func <<"():" << lineno << ":  ";

    //  name是XLOG参数的string形式
    //  运用正则表达式将传入的变长参数名解析分割到vector中
    std::regex re { "\\s{0,},\\s{0,}" };
    std::vector<std::string> nameList = std::vector<std::string> {
            std::sregex_token_iterator(name.begin(), name.end(), re, -1), std::sregex_token_iterator() };

    //  运用折叠表达式将变长参数输出
    (os << ... << modifyArgLog(args, nameList)) << std::endl;
}
template <typename T>
std::ostream & operator <<(std::ostream &os,
                           const std::map<std::string, T> &m)
{
    os<<"{";
    for (const auto &p : m)
    {
        os << p.first << ": ";
        for (auto x : p.second) os << x << ' ';
        os << std::endl;
    }
    os<<"}";
    return os;
}

template < typename F, typename S >
std::ostream& operator << ( std::ostream& os, const std::pair< F, S > & p ) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template < typename T >
std::ostream &operator << ( std::ostream & os, const std::vector< T > &v ) {
    os << "{";
    typename std::vector< T > :: const_iterator it;
    for( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "}";
}

template < typename T >
std::ostream &operator << ( std::ostream & os, const std::set< T > &v ) {
    os << "[";
    typename std::set< T > :: const_iterator it;
    for ( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "]";
}

template < typename F, typename S >
std::ostream &operator << ( std::ostream & os, const std::map< F, S > &v ) {
    os << "[";
    typename std::map< F , S >::const_iterator it;
    for( it = v.begin(); it != v.end(); it++ ) {
        if( it != v.begin() ) os << ", ";
        os << "<"<<it -> first << " , " << it -> second<<">" ;
    }
    return os << "]";
}

//  编译器定义的一个局部静态变量,用于存放函数的名字
//  __FUNCTION__ ：函数名
//  __TIME__ ：文件运行的时间
//  __LINE__ ：所在行数
//  __FILE__：文件的名字
//  XLOG可以在函数中快速打印变量的值，方便定位信息
//  #args为变量名
//  如果可变参数被忽略或为空，“##”操作将使预处理器去除掉它前面的那个逗号，避免报错
#define XLOG(logger, args...) do{ \
    std::ostringstream str;      \
    str<<GetTimeMs()<<" "; \
    str<<std::this_thread::get_id(); \
    str<<"XLOG ";                       \
    testLog(str, __FILE__, __func__,__LINE__ , #args, ##args); \
    logger.write_one(str.str()); \
}while(0)
#endif //EFFICIENT_LOGGING_SYSTEM_FASTLOG_H
