#ifndef ZBOSS_NODE_HPP
#define ZBOSS_NODE_HPP

#include <vector>

namespace zboss {

    typedef enum {
        NODE_NODE,
        NODE_CONTAINER
    } node_type_t;

    class Node {

        private:

        std::vector<Node*> children;
        node_type_t type;
        Node* parent;
        bool visible = true;

        public:

        explicit Node(node_type_t type) : type(type) {}

        Node* findFirstParentByType(node_type_t type);

        virtual void onRender() {}

    };

}

#endif //ZBOSS_NODE_HPP