#pragma once
#include "node_viewer.h"

namespace quadtree {
class Node;
class NodeViewer;
class NodeAccessor : public NodeViewer {
public:
  NodeAccessor();
  NodeAccessor(Node *node);
  NodeAccessor(const NodeAccessor &that) = delete;
  NodeAccessor(NodeAccessor &&that);
  NodeAccessor &operator=(const NodeAccessor &that) = delete;
  NodeAccessor &operator=(NodeAccessor &&that);
  ~NodeAccessor();
  const Node *operator->() const;
  Node *operator->();
  [[nodiscard]] const Node &operator*() const = delete;
  [[nodiscard]] Node &operator*() = delete;
  [[nodiscard]] bool accessible() const;
  [[nodiscard]] bool unaccessible() const;
  [[nodiscard]] NodeViewer view();
  [[nodiscard]] const NodeViewer view() const;

private:
  //Node *_node;
};
} // namespace quadtree
