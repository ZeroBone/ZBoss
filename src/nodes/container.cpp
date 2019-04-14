#include <zboss/nodes/container.hpp>

namespace zboss {

    Vector<float> ContainerNode::getPosition() const {
        return relativePosition;
    }

    void ContainerNode::setPosition(int x, int y) {

        relativePosition.x = x;
        relativePosition.y = y;

        // update matrices

        offset = {
            {1., 0., (float)x},
            {0., 1., (float)y},
            {0., 0., 1.      }
        };

        cachedTransform = offset * rotation;

        cachePosition();

    }

    void ContainerNode::cachePosition() {

        Matrix<float, 3, 1> pivot;
        pivot = {
            {0.0},
            {0.0},
            {1.0}
        };

        Matrix<float, 3, 1> transformed = cachedParentTransform * cachedTransform * pivot;

        absolutePosition = Vector<float>(transformed(0, 0), transformed(1, 0));

    }

    Vector<float> ContainerNode::getAbsolutePosition() {

        Node* parent = findFirstParentByType(NODE_CONTAINER);

        Matrix<float, 3, 3> currentParentCachedTransform;

        if (parent != nullptr) {

            currentParentCachedTransform = ((ContainerNode*)parent)->getCachedTransform();

        }

        if (currentParentCachedTransform != cachedParentTransform) {
            cachedParentTransform = currentParentCachedTransform;
            cachePosition();
        }

        return absolutePosition;

    }

    Matrix<float, 3, 3> ContainerNode::getCachedTransform() const {
        return cachedTransform;
    }

}