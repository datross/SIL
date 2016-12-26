#include "node_pool.h"

using namespace sil;
using namespace function;

Node_pool::Node_pool() {
}

Node_pool::~Node_pool() {
}

void Node_pool::push(Expression_ptr p) {
    expressions.push_front(p);
}

void Node_pool::push(Statement_ptr p) {
    statements.push_front(p);
}