#pragma once
#include <memory>
#include <array>
#include <vector>
namespace lorenz {
using Vec3d= std::vector<double>;
using Vectors = std::vector<Vec3d>;

struct LorenzParameters
{
    LorenzParameters(double sigma = 10., double R = 28., double b = 8./3., Vec3d initial = {10.,1.,1.})
    : sigma_(sigma), R_(R), b_(b), initial_(initial) {}
    double sigma_, R_,b_;
    Vec3d initial_;
};

class Lorenz
{
public:
    Lorenz(int steps = 5000, double dt = 0.01, LorenzParameters paras = LorenzParameters());

    std::shared_ptr<Vectors> Data() const { return data_; }

    auto GetSteps()  { return steps_; }
private:
    std::size_t steps_;
    std::shared_ptr<Vectors> data_;
};
}