#ifndef KO_HH_INCLUDED
#define KO_HH_INCLUDED

#include <functional>
class KoComposer {
  std::function<void(char32_t)> emit;

  char32_t buf, last;

public:
  inline KoComposer(std::function<void(char32_t)> emit) : emit(emit) {}
  void write(int);
  inline char32_t pending() const { return buf; }
};

#endif
