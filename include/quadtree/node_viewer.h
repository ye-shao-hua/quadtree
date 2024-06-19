#pragma once

namespace quadtree {
class Node;
class NodeViewer {
public:
  NodeViewer();
  NodeViewer(const Node *node);
  NodeViewer(const NodeViewer &that);
  NodeViewer(NodeViewer &&that);
  NodeViewer &operator=(const NodeViewer &that);
  NodeViewer &operator=(NodeViewer &&that);
  const Node *operator->() const;
  Node *operator->();
  [[nodiscard]] const Node &operator*() const = delete;
  [[nodiscard]] Node &operator*() = delete;
  [[nodiscard]] bool viewable() const;
  [[nodiscard]] bool unviewable() const;
  //[[nodiscard]] Node *data();
  [[nodiscard]] bool operator==(const NodeViewer that) const;
  [[nodiscard]] bool operator!=(const NodeViewer that) const;

protected:
  Node *_node;
};
} // namespace quadtree
