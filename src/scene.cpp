#include <zboss/scene.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    using namespace std;

    Scene::Scene() :
        root(Engine::get().entities().addEntity("r"s)) {

        camera.x = camera.y = 0;

        camera.w = Engine::get().vWidth;
        camera.h = Engine::get().vHeight;

    }

    void Scene::onResize() {

        camera.w = Engine::get().vWidth;
        camera.h = Engine::get().vHeight;

    }

}