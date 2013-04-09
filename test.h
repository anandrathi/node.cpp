#ifndef TEST_H
#define TEST_H
#include "cstralgo.h"
#include <string>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <time.h>

class Test
{
public:
    Test();
    ~Test();
void testtransform( )
{
    std::string word ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    word =word+word+word+word+word+word+word+word+word+word+word+word+word+word+word;
    std::string word2=word; 
    time_t t;
    time_t t2;
    time(&t);
    std::cout << "testtransform: start " << "\n";
    int i=0;
    for(;i<9999999;i++) 
    {    word2=word;
        std::transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
    }
    time(&t2);
    std::cout << word2 << "\n";
    std::cout << "testtransform: end " << i << ":"<< t2-t << "\n";
}
void testmytolower( )
{
    std::string word ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    word =word+word+word+word+word+word+word+word+word+word+word+word+word+word+word;
    std::string word2=word; 
    time_t t;
    time_t t2;
    time(&t);
    std::cout << "testmytolower: start " << "\n";
    int i=0;
    for(;i<9999999;i++)
    {   word2=word;
        cstralgo::tolowerStr(word2);
    }
    time(&t2);
    std::cout << word2 << "\n";
    std::cout << "testmytolower: end " << i << ":"<< t2-t << "\n";
}



};

#endif // TEST_H
