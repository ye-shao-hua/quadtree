#include "../include/quadtree/counter.h"

namespace quadtree{
    Counter::Counter(int count) : _count(count) {}
    void Counter::increase() {
        ++_count;
    }
    void Counter::decrease() {
        --_count;
    }
    int Counter::use_count() const {
        return _count;
    }
}
