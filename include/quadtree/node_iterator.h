#pragma once

namespace std {

struct random_access_iterator_tag;

}

namespace quadtree {
class Node;
class NodeViewer;
class NodeIterator {
public:
  using index_type = unsigned int;
  using iterator_category = std::random_access_iterator_tag;
  using value_type = NodeViewer;
  using difference_type = int;
  using reference = NodeViewer &;
  using pointer = NodeViewer *;

public:
  NodeIterator() = delete;
  NodeIterator(const NodeIterator &that);
  NodeIterator(NodeViewer node[], index_type index);
  NodeIterator &operator=(const NodeIterator &that);
  NodeIterator &operator=(NodeIterator &&that) = delete;
  NodeIterator &operator++();
  NodeIterator operator++(int);
  NodeIterator &operator--();
  index_type operator-(const NodeIterator &that) const;
  NodeIterator operator+(int offset) const;
  NodeIterator operator-(int offset) const;
  [[nodiscard]] bool operator==(const NodeIterator &that) const {
    return _index == that._index;
  }
  [[nodiscard]] bool operator!=(const NodeIterator &that) const {
    return !(_index == that._index);
  }
  [[nodiscard]] bool operator<(const NodeIterator &that) const;
  [[nodiscard]] NodeViewer &operator*();
  NodeViewer &operator[](index_type index);

private:
  NodeViewer *_node;
  index_type _index;
};
} // namespace quadtree
