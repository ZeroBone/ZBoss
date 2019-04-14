#ifndef ZBOSS_CONTAINER_HPP
#define ZBOSS_CONTAINER_HPP

#include "node.hpp"
#include "../math/vector.hpp"
#include "../math/matrix.hpp"

namespace zboss {

    class ContainerNode : public Node {

        private:

        float scale;
        float cachedAngle;

        Vector<float> relativePosition;

        // this position is calculated automatically, should not be changed manually
        Vector<float> absolutePosition;

        Matrix<float, 3, 3> rotation;
        Matrix<float, 3, 3> offset;
        Matrix<float, 3, 3> cachedTransform;
        Matrix<float, 3, 3> cachedParentTransform;

        public:

        explicit ContainerNode() : Node(NODE_CONTAINER) {}

        inline Vector<float> getPosition() const;
        inline void setPosition(int x, int y);
        inline Vector<float> getAbsolutePosition();
        inline Matrix<float, 3, 3> getCachedTransform() const;

        private:
        inline void cachePosition();

    };

}

#endif //ZBOSS_CONTAINER_HPP