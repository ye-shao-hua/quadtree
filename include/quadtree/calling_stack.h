#pragma once

namespace quadtree {
class CallingStack {
public:
  using index_type = unsigned int;
public:
  CallingStack();
  void push(index_type calling_index);
  void pop();
  [[nodiscard]] index_type top() const;
  [[nodiscard]] bool empty() const;

private:
  index_type _data[64];
  index_type _index;
};
} // namespace quadtree
