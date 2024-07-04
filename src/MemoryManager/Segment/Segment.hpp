#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <string>

class Segment{
  public:
    Segment(std::string pName, int start, int size, bool isFree, Segment* next);
    
    void        Fragment(std::string processName, int size);
    void        Union();
    bool        IsFree();
    void        Free();
    int         Size();
    Segment*    Next();
    std::string ProcessName();
    
  private:
    std::string m_Process;
    bool        m_IsFree;
    int         m_Size;
    int         m_Start;

    Segment*   m_Next;
};

#endif
