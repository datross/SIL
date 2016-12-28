#include "node_pool.h"

using namespace sil;
using namespace function;

Node_pool::Node_pool() {
}

Node_pool::~Node_pool() {
}

void Node_pool::push(Node_ptr p) {
    nodes.push_front(p);
}