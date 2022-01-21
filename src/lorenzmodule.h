#pragma once
#include "lorenz.h"
#include "kipod.h"

namespace lorenz
{
using namespace kipod;

template<typename Vectors>
auto CreateFloatData(const Vectors &vectors) -> std::unique_ptr<std::vector<glm::vec3>>;

auto CreateLorenzModule(int w, int h) -> std::unique_ptr<BasicModule>;
}