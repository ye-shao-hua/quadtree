#include "../include/quadtree/quadtree.h"
#include "../include/quadtree/quadtree_iterators.h"

namespace quadtree {
Quadtree::Quadtree(const Rect &box_size) : _data(nullptr, box_size) {}
float Quadtree::operator()(float x, float y) const { return _data(x, y); }
void Quadtree::refine_global(int times) {
  for (int i = 0; i < times; ++i)
    _data.refine();
}
void Quadtree::set_value(float x, float y, float new_value) {
  if (!_data.include(x, y))
    throw "无效地址\n";
  _data.set_value(x, y, new_value);
}
void Quadtree::set_value(const Trapezium &trapezium, float new_value) {
  if (_data.include(trapezium) || trapezium.include(_data.box_size()))
    _data.set_value(trapezium, new_value);
}
Node& Quadtree::at(float x, float y) {
    return _data.at(x, y);
}
const Node& Quadtree::at(float x, float y) const {
    return _data.at(x, y);
}
QuadtreeIterators Quadtree::node_iterators() {
    return {*this};
}
} // namespace quadtree
