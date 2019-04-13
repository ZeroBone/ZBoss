#ifndef ZBOSS_NODE_HPP
#define ZBOSS_NODE_HPP

namespace zboss {

    class Node {

        private:

        std::vector<Node*> children;
        int type;
        Node* parent;
        bool visible = true;

        public:

        Node(int type) : type(type) {}

        virtual void onRender() {}

    };

}

#endif //ZBOSS_NODE_HPP