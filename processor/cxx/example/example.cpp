#include "example.h"

namespace my_namespace {
class my_override : public my_abc {
  public:
    void my_virtual_func(int param) override { return; }
};
bool my_func(my_typedef a, my_enum b) { return true; }
} // namespace my_namespace