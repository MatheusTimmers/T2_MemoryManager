#include "./BuddyMemoryManager.hpp"

BuddyMemoryManager::BuddyMemoryManager(int size) {
  this->m_Root = new Buddy("", size, BuddyState::FREE);
}

void BuddyMemoryManager::Merge(Buddy* buddy) {
  if (buddy->m_State == BuddyState::DIVIDED) {
    if ((buddy->m_LeftChild != nullptr && buddy->m_RightChild != nullptr) &&
      (buddy->m_LeftChild->m_State == BuddyState::FREE && buddy->m_RightChild->m_State == BuddyState::FREE)) {
      buddy->m_State = BuddyState::FREE;
      delete buddy->m_LeftChild;
      delete buddy->m_RightChild;
      buddy->m_LeftChild = nullptr;
      buddy->m_RightChild = nullptr;
      buddy->m_AllocSize = 0;

      if (buddy->m_Parent != nullptr) {
        Merge(buddy->m_Parent);
      }
    }
  }
}

bool BuddyMemoryManager::Alloc(std::string label, double psize) {
  std::deque<Buddy*> buddies_to_visit;
  Buddy* buddy;
  buddies_to_visit.push_back(m_Root);

  while (!buddies_to_visit.empty()) {
    buddy = buddies_to_visit.back();
    buddies_to_visit.pop_back();

    if (buddy->m_State == BuddyState::DIVIDED) {
      buddies_to_visit.push_back(buddy->m_RightChild);
      buddies_to_visit.push_back(buddy->m_LeftChild);
    } else if (buddy->m_State == BuddyState::FREE) {
      if (buddy->m_Size >= psize) {
        if (buddy->m_Size / 2 >= psize) {
          buddy->m_State = BuddyState::DIVIDED;

          buddy->m_LeftChild  = new Buddy("", buddy->m_Size / 2, BuddyState::FREE);
          buddy->m_RightChild = new Buddy("", buddy->m_Size / 2, BuddyState::FREE);

          buddy->m_LeftChild->m_Parent  = buddy;
          buddy->m_RightChild->m_Parent = buddy;

          buddies_to_visit.push_back(buddy->m_RightChild);
          buddies_to_visit.push_back(buddy->m_LeftChild);
        } else {
          buddy->m_State     = BuddyState::ALLOCATED;
          buddy->m_pName     = label;
          buddy->m_AllocSize = psize;
          return true;
        }
      }
    }
  }
  return false;
}

bool BuddyMemoryManager::Dealloc(std::string label) {
  std::queue<Buddy*> buddies_to_visit;
  buddies_to_visit.push(m_Root);

  while (!buddies_to_visit.empty()) {
    Buddy* buddy = buddies_to_visit.front();
    buddies_to_visit.pop();

    if (buddy->m_State == BuddyState::DIVIDED) {
      buddies_to_visit.push(buddy->m_LeftChild);
      buddies_to_visit.push(buddy->m_RightChild);
    } else if (buddy->m_State == BuddyState::ALLOCATED) {
      if (buddy->m_pName == label) {
        buddy->m_State = BuddyState::FREE;
        buddy->m_AllocSize = 0;
        Merge(buddy->m_Parent);

        return true;
      }
    }
  }
  return false;
}

std::string BuddyMemoryManager::toString() {
  std::string repr;
  std::deque<Buddy*> buddies_to_visit;
  buddies_to_visit.push_back(m_Root);

  while (!buddies_to_visit.empty()) {
    Buddy* buddy = buddies_to_visit.back();
    buddies_to_visit.pop_back();
    
    repr += buddy->toString() + "\n";
    
    if (buddy->m_LeftChild) 
      buddies_to_visit.push_back(buddy->m_LeftChild);

    if (buddy->m_RightChild) 
      buddies_to_visit.push_back(buddy->m_RightChild);
  }
  return repr;
}
