#ifndef ZBOSS_CONTAINER_HPP
#define ZBOSS_CONTAINER_HPP

namespace zboss {

    class ContainerNode : public Node {

        public:

        explicit ContainerNode() : Node(NODE_CONTAINER) {}

        explicit ContainerNode(node_type_t type) : Node(type) {}

    };

}

#endif //ZBOSS_CONTAINER_HPP