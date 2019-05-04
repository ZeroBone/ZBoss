#include <zboss/scene.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    using namespace std;

    Scene::Scene() : root(Engine::get().entities().addEntity("r"s)) {}

}