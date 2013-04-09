#ifndef CSTRALGO_H
#define CSTRALGO_H
#include <string>

class cstralgo
{
public:
    cstralgo();
    ~cstralgo();
 
static inline int tolower(int c) 
{
    switch(c)
    {
      case 'A':return  'a';
      case 'B':return  'b';
      case 'C':return  'c';
      case 'D':return  'd';
      case 'E':return  'e';
      case 'F':return  'f';
      case 'G':return  'g';
      case 'H':return  'h';
      case 'I':return  'i';
      case 'J':return  'j';
      case 'K':return  'k';
      case 'L':return  'l';
      case 'M':return  'm';
      case 'N':return  'n';
      case 'O':return  'o';
      case 'P':return  'p';
      case 'Q':return  'q';
      case 'R':return  'r';
      case 'S':return  's';
      case 'T':return  't';
      case 'U':return  'u';
      case 'V':return  'v';
      case 'W':return  'w';
      case 'X':return  'x';
      case 'Y':return  'y';
      case 'Z':return  'z';
    };
    return c;
}

static inline void tolowerRef(char &c) 
{
    switch(c)
    {
      case 'A':c='a'; return;
      case 'B':c='b'; return;
      case 'C':c='c'; return;
      case 'D':c='d'; return;
      case 'E':c='e'; return;
      case 'F':c='f'; return;
      case 'G':c='g'; return;
      case 'H':c='h'; return;
      case 'I':c='i'; return;
      case 'J':c='j'; return;
      case 'K':c='k'; return;
      case 'L':c='l'; return;
      case 'M':c='m'; return;
      case 'N':c='n'; return;
      case 'O':c='o'; return;
      case 'P':c='p'; return;
      case 'Q':c='q'; return;
      case 'R':c='r'; return;
      case 'S':c='s'; return;
      case 'T':c='t'; return;
      case 'U':c='u'; return;
      case 'V':c='v'; return;
      case 'W':c='w'; return;
      case 'X':c='x'; return;
      case 'Y':c='y'; return;
      case 'Z':c='z'; return;
    };
    return ;
}

static inline void tolowerPtr(char *p) 
{
    switch(*p)
    {
      case 'A':*p='a'; return;
      case 'B':*p='b'; return;
      case 'C':*p='c'; return;
      case 'D':*p='d'; return;
      case 'E':*p='e'; return;
      case 'F':*p='f'; return;
      case 'G':*p='g'; return;
      case 'H':*p='h'; return;
      case 'I':*p='i'; return;
      case 'J':*p='j'; return;
      case 'K':*p='k'; return;
      case 'L':*p='l'; return;
      case 'M':*p='m'; return;
      case 'N':*p='n'; return;
      case 'O':*p='o'; return;
      case 'P':*p='p'; return;
      case 'Q':*p='q'; return;
      case 'R':*p='r'; return;
      case 'S':*p='s'; return;
      case 'T':*p='t'; return;
      case 'U':*p='u'; return;
      case 'V':*p='v'; return;
      case 'W':*p='w'; return;
      case 'X':*p='x'; return;
      case 'Y':*p='y'; return;
      case 'Z':*p='z'; return;
    };
    return ;
}

static inline int toupper(int c) 
{
    switch(c)
    {
      case 'a':return  'A';
      case 'b':return  'B';
      case 'c':return  'C';
      case 'd':return  'D';
      case 'e':return  'E';
      case 'f':return  'F';
      case 'g':return  'G';
      case 'h':return  'H';
      case 'i':return  'I';
      case 'j':return  'J';
      case 'k':return  'K';
      case 'l':return  'L';
      case 'm':return  'M';
      case 'n':return  'N';
      case 'o':return  'O';
      case 'p':return  'P';
      case 'q':return  'Q';
      case 'r':return  'R';
      case 's':return  'S';
      case 't':return  'T';
      case 'u':return  'U';
      case 'v':return  'V';
      case 'w':return  'W';
      case 'x':return  'X';
      case 'y':return  'Y';
      case 'z':return  'Z';
    };
    return c;
}

static inline void toupperRef(char &c) 
{
    switch(c)
    {
      case 'a':c='A';return;
      case 'b':c='B';return;
      case 'c':c='C';return;
      case 'd':c='D';return;
      case 'e':c='E';return;
      case 'f':c='F';return;
      case 'g':c='G';return;
      case 'h':c='H';return;
      case 'i':c='I';return;
      case 'j':c='J';return;
      case 'k':c='K';return;
      case 'l':c='L';return;
      case 'm':c='M';return;
      case 'n':c='N';return;
      case 'o':c='O';return;
      case 'p':c='P';return;
      case 'q':c='Q';return;
      case 'r':c='R';return;
      case 's':c='S';return;
      case 't':c='T';return;
      case 'u':c='U';return;
      case 'v':c='V';return;
      case 'w':c='W';return;
      case 'x':c='X';return;
      case 'y':c='Y';return;
      case 'z':c='Z';return;
    };
    return ;
}

static inline void toupperPtr(char *p) 
{
    switch(*p)
    {
      case 'a':*p='A';return;
      case 'b':*p='B';return;
      case 'c':*p='C';return;
      case 'd':*p='D';return;
      case 'e':*p='E';return;
      case 'f':*p='F';return;
      case 'g':*p='G';return;
      case 'h':*p='H';return;
      case 'i':*p='I';return;
      case 'j':*p='J';return;
      case 'k':*p='K';return;
      case 'l':*p='L';return;
      case 'm':*p='M';return;
      case 'n':*p='N';return;
      case 'o':*p='O';return;
      case 'p':*p='P';return;
      case 'q':*p='Q';return;
      case 'r':*p='R';return;
      case 's':*p='S';return;
      case 't':*p='T';return;
      case 'u':*p='U';return;
      case 'v':*p='V';return;
      case 'w':*p='W';return;
      case 'x':*p='X';return;
      case 'y':*p='Y';return;
      case 'z':*p='Z';return;
    };
    return ;
}

static inline void tolowerFromTo(char *c, char* ec)
{for(;c!=ec;c++)cstralgo::tolowerPtr(c); };
static inline void tolowerLen(char *c, size_t l)
{for(char* c2=c;c2<c+l;c2++)tolowerPtr(c2); };
static inline void tolowerStr(std::string& s)
{char* c=const_cast<char*>(s.c_str());
 size_t l = s.size();
    for(char* c2=c;c2<c+l;c2++)cstralgo::tolowerPtr(c2); 
};


static inline void toupperFromTo(char *c, char* ec)
{for(;c!=ec;c++)cstralgo::toupperPtr(c); };
static inline void toupperLen(char *c, size_t l)
{for(char* c2=c;c2<c2+l;c2++)toupperPtr(c2); };
static inline void toupperStr(std::string& s)
{char* c=const_cast<char*>(s.c_str());
 size_t l = s.size();
    for(char* c2=c;c2<c+l;c2++)cstralgo::toupperPtr(c2); 
};

};
#endif // CSTRALGO_H

