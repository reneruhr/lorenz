#include <iostream>
#include "src/lorenz.h"
#include "src/runge_kutta.h"

using RK4 = RungeKutta4<StateType, double, double, ContainerAlgebra, DefaultOperations>;
int main()
{
    const int steps = 5000;
    const double dt = 0.01;

    auto stepper = RK4{};
    auto lorenz = Lorenz(10., 28., 8./3.);
    auto x = StateType(3,1.);
    x[0] = 10.;
    for(size_t n = 0; n< steps; ++n){
       stepper.DoStep(lorenz, x, n*dt, dt);
       std::cout << n* dt << ' ' << x[0] << ' ' << x[1] << ' ' << x[2] << "\n";
    }
    return 0;
}
