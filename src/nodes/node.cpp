#include <zboss/nodes/node.hpp>

namespace zboss {

    Node* Node::findFirstParentByType(node_type_t type) {

        Node* result = parent;

        while (result != nullptr) {

            if (result->type == type) {
                return result;
            }

            result = result->parent;

        }

        return nullptr;

    }

}