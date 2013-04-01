#ifndef BUFFER_H
#define BUFFER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>

template <typename T>
class Buffer {
    std::vector<T> m_vecData;
    size_t m_availaibleSize;
    size_t m_readPosition;
    size_t m_writePosition;
    T* t_Ptr;
    
    size_t t_i;
public:
    //Constructor with initial size in 8 kb
    Buffer(short initialsize=8)
    {
        m_writePosition=0;
        m_readPosition=0;
        m_vecData.reserve(initialsize*1024); //8kb
        m_availaibleSize=m_vecData.capacity() - m_vecData.size();
    }

    //starts Write pointer from zero ann resizes the buffer
    const T* resizeWriteFromStart(size_t p_size)
    {
        if(m_vecData.capacity() <= p_size)
        {
            m_vecData.reserve( (m_vecData.capacity()+ p_size) *2) ;
        } 
        m_vecData.resize(p_size);
        m_availaibleSize=m_vecData.capacity() - m_vecData.size();
        m_writePosition=0;
        t_Ptr= &m_vecData[m_writePosition];
        return t_Ptr;
    }
    
    //pointer of the data stored or NULL if empty
    const T* getDataToWrite(size_t p_size)
    {
        if(m_availaibleSize >= p_size)
        {   
            m_vecData.resize(m_vecData.size()+ p_size);
        } else {
            m_vecData.reserve( (m_vecData.capacity() + p_size) * 2);
            m_vecData.resize(m_vecData.size()+ p_size);
        }
        m_availaibleSize=m_vecData.capacity() - m_vecData.size();
        t_Ptr= &m_vecData[m_writePosition];
        m_writePosition+=p_size;
        return t_Ptr;
    }

    
    //pointer of the data stored or NULL if empty
    const T * data()
    {
        if(m_vecData.size()>0)
            return &m_vecData[0];
        return 0;
    }
    
    //sets new data , erases old
    void setData(T * p_data, size_t p_size)
    { 
        if(m_vecData.capacity() < p_size)
            m_vecData.reserve(p_size * 1.25);
        m_vecData.clear();
        m_vecData.insert(m_vecData.begin(), p_data,  p_data + p_size);
        m_availaibleSize=m_vecData.capacity() - m_vecData.size();
        m_readPosition=0;
    }
    
    //inserts  new data , erases old
    void PushData(T * p_data, size_t p_size)
    { 
        if(m_availaibleSize < p_size)
            m_vecData.reserve(p_size * 1.25);
        m_vecData.clear();
        m_vecData.insert(m_vecData.begin(), p_data,  p_data + p_size);
    }

    //gets the data and increases the current read position
    //Returns ZERO if no data or Pop size larger than availaible
    T* PopNextData(size_t p_size)
    {
        if(m_vecData.size()==0)
            return 0;
         else {   
            if(m_readPosition>m_vecData.size())
                return 0;
            if(m_readPosition+p_size>m_vecData.size())
                return 0;
        }
        t_Ptr=&m_vecData[m_readPosition];
        m_readPosition+=p_size;
        return t_Ptr;
    }

};
typedef Buffer<char> octetBuffer;

#endif //BUFFER_H