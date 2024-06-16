#pragma once

namespace quadtree {
class Counter {
public:
  Counter(int count = 1);
  void increase();
  void decrease();
  int use_count() const;

private:
  int _count;
};
} // namespace quadtree
