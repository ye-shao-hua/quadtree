#pragma once

namespace quadtree {
class Node;
class NodeViewer {
public:
  NodeViewer();
  NodeViewer(Node* node);
  NodeViewer(const NodeViewer &that);
  NodeViewer(NodeViewer&& that);
  NodeViewer &operator=(const NodeViewer &that);
  NodeViewer &operator=(NodeViewer &&that);
  const Node *operator->() const;
  Node *operator->();
  [[nodiscard]] const Node &operator*() const;
  [[nodiscard]] Node &operator*();
  [[nodiscard]] bool viewable() const;
  [[nodiscard]] bool unviewable() const;
  [[nodiscard]] Node* data();

protected:
  Node* _node;
};
} // namespace quadtree
