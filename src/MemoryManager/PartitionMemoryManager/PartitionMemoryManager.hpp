#ifndef PartitionMemoryManager_hpp
#define PartitionMemoryManager_hpp

#include <string>
#include "../../Enums/Enums.hpp"
#include "../Segment/Segment.hpp"

class PartitionMemoryManager {
  public:
    PartitionMemoryManager(int size, Policy policy);
    bool Alloc(std::string label, int size);
    bool Dealloc(std::string label);

  private:
    int      m_nSize;
    Policy   m_Policy;
    Segment* m_MemorySpace;
    Segment* m_LastAlloc; // Apenas usado no circular_fit

    bool AllocWorstFit   (std::string label, int size);
    bool AllocCircularFit(std::string label, int size);
    
    Segment* GetBiggestFreeSegment();
    Segment* GetNextFreeSegment(int size);

    void PrintResults();
};

#endif 
