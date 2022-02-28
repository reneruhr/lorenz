#include "src/lorenzmodule.h"
#include "kipod.h"

using namespace kipod;
using namespace lorenz;

int main()
{
    kipod::Application kipod;
    kipod.Init();
    auto [w,h] = kipod.WindowSize();
    kipod.Add(CreateLorenzModule(w,h));


    kipod.Run();
    kipod.ShutDown();
    return 0;
}