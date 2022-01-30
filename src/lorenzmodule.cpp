#include "lorenzmodule.h"

auto lorenz::CreateLorenzModule(int w, int h) -> std::unique_ptr<BasicModule>
{
    auto module = std::make_unique<BasicModule>(BasicModule{w, h, "Lorenz Module"});
    Lorenz lorenz{};
    auto graph = CreateFloatData(*lorenz.Data());
    auto scene = static_pointer_cast<BasicScene>(module->GetScene());


    auto indices = std::vector<unsigned int>(std::size(*graph));
    std::iota(std::begin(indices), std::end(indices), 0);

    scene->Add(indices, *graph, GL_LINE_STRIP);

    auto points =  static_pointer_cast<BasicObject>(scene->Add(indices, *graph, GL_POINTS));
    points->SetColor(glm::vec3(1.,1.,0));
    static_cast<kipod::GLRenderLayout*>(points->Layout())->SetSubIndex(10,0);
    glPointSize(5.);
    return std::move(module);
}

template<typename Vectors>
auto lorenz::CreateFloatData(const Vectors &vectors) -> std::unique_ptr<std::vector<glm::vec3>>
{
    auto float_vectors = std::make_unique<std::vector<glm::vec3>>(std::size(vectors));
    for(int i = 0; const auto& v : vectors) (*float_vectors)[i++]= {static_cast<float>(v[0]),static_cast<float>(v[1]),static_cast<float>(v[2])};
    return std::move(float_vectors);
}

template
std::unique_ptr<std::vector<glm::vec3>> lorenz::CreateFloatData<std::vector<std::vector<double>>>(const std::vector<std::vector<double>> &vectors);