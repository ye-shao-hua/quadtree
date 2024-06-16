#include "../include/quadtree/calling_stack.h"

namespace quadtree {
CallingStack::CallingStack() : _index(0) {}
void CallingStack::push(index_type calling_index) {
  _data[_index++] = calling_index;
}
void CallingStack::pop() { --_index; }
CallingStack::index_type CallingStack::top() const { return _data[_index - 1]; }
bool CallingStack::empty() const {
    return _index == 0;
}

} // namespace quadtree
