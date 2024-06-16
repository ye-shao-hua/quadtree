#pragma
#include "node_hasher.h"

namespace quadtree {
class NodeHashtable {
public:
  NodeHashtable();
  int operator[](const Node *) const;

private:
  float alpha;
};
} // namespace quadtree
