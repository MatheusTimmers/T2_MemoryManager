#ifndef BuddyMemoryManager_hpp
#define BuddyMemoryManager_hpp

#include "../Buddy/Buddy.hpp"
#include <iostream>

class BuddyMemoryManager{ 
  public:
    BuddyMemoryManager(int size);

    Buddy* m_Root; 

    void        Merge(Buddy* buddy);
    bool        Alloc(std::string label, double psize);
    bool        Dealloc(std::string label);
    std::string toString();
    
};

#endif
