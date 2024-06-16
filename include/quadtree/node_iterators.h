#pragma once

namespace quadtree {
class Node;
class NodeIterator;
class NodeViewer;
class NodeIterators {
public:
  using index_type = unsigned int;

public:
  NodeIterators() = delete;
  NodeIterators(NodeViewer node[], index_type size);
  NodeIterators(const NodeIterators &that);
  NodeIterators &operator=(const NodeIterators &that) = delete;
  NodeIterators &operator=(NodeIterators &&that) = delete;
  [[nodiscard]] NodeIterator begin();
  [[nodiscard]] NodeIterator end();
  [[nodiscard]] const NodeIterator begin() const;
  [[nodiscard]] const NodeIterator end() const;

private:
  NodeViewer* _node;
  index_type _size;
};
} // namespace quadtree
