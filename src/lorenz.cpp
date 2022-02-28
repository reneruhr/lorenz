#include "lorenz_system.h"
#include "runge_kutta.h"
#include "lorenz.h"

namespace lorenz
{
using RK4 = RungeKutta4<Vec3d, double, double, ContainerAlgebra, DefaultOperations>;

Lorenz::Lorenz(int steps, double dt, LorenzParameters paras) : steps_(steps), data_(std::make_shared<Vectors>(Vectors{paras.initial_}))
{
    auto stepper = RK4{};
    auto lorenz = LorenzSystem(paras.sigma_, paras.R_, paras.b_);
    auto x = paras.initial_;
    for (size_t n = 0; n < steps; ++n) {
        stepper.DoStep(lorenz, x, n * dt, dt);
        data_->push_back(x);
    }
}
}