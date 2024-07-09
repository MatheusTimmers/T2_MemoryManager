#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>

enum Policy{
  WORST_FIT,
  CIRCULAR_FIT
};

enum Commands{
  In,
  Out
};

struct Process {
  std::string ProcessName;
  int         MemorySize;
};

enum BuddyState {
  DIVIDED,
  FREE,
  ALLOCATED
};

#endif
