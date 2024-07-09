#ifndef BUDDY_HPP
#define BUDDY_HPP

#include <string>
#include <iostream>
#include <deque>
#include <queue>
#include "../../Enums/Enums.hpp"

class Buddy {
  public:
    Buddy(std::string name, int size, BuddyState state);
    std::string toString();
    
    int         m_Size;   
    int         m_AllocSize;
    Buddy*      m_Parent; 
    Buddy*      m_LeftChild; 
    Buddy*      m_RightChild; 
    std::string m_pName; 
    BuddyState  m_State;           
};

#endif
