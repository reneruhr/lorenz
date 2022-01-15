#include <vector>
using StateType = std::vector<double>;

struct LorenzSystem
{
    const double sigma_, R_, b_;
    LorenzSystem(const double sigma, const double R, const double b)
    : sigma_(sigma), R_(R), b_(b) {}

    void operator() (const StateType& x, StateType& dxdt, double ) const
    {
        dxdt[0] = sigma_ *(x[1]-x[0]);
        dxdt[1] = R_ * x[0] - x[1] - x[0] * x[2];
        dxdt[2] = -b_ * x[2] + x[0] * x[1];
    }
};