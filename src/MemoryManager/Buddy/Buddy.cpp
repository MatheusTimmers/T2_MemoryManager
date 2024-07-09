#include "./Buddy.hpp"

Buddy::Buddy(std::string name, int size, BuddyState state) {
  this->m_pName     = name;
  this->m_Size      = size;
  this->m_State     = state;
  this->m_AllocSize = 0;

  this->m_Parent     = nullptr;
  this->m_LeftChild  = nullptr;
  this->m_RightChild = nullptr;
}

std::string Buddy::toString() {
  if (this->m_State == BuddyState::FREE) {
    return "*" + std::to_string(this->m_Size) + "|";
  } else {
    return this->m_pName + std::to_string(this->m_AllocSize) + " " + std::to_string(this->m_Size) + "|";
  }
}
