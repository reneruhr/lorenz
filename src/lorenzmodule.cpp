#include "lorenzmodule.h"

auto lorenz::CreateLorenzModule(int w, int h) -> std::unique_ptr<BasicModule>
{
    auto module = std::make_unique<BasicModule>(BasicModule{w, h, "Lorenz Module"});

    auto parameter_vector = std::vector<LorenzParameters>{};

    auto initial_left = Vec3d {10.,1.,1.};
    auto initial_right = Vec3d {9.9,1.2,0.8};
    auto interpolate = [l = initial_left, r = initial_right](double j, double total){
        auto c = [=](int i){
            return (l[i] * j + r[i] * (total-j)) / total;
        };
        return Vec3d{ c(0), c(1), c(2) };
    };

    auto copies {6};
    for(auto i = 0.; i < copies; i++) parameter_vector.push_back(
                LorenzParameters( 10., 28., 8./3.,interpolate(i,copies))
                        );
    UniformDistribution::Randomize();
    using UniformDistribution::Pick;
    auto scene = static_pointer_cast<BasicScene>(module->GetScene());

    scene->SetSpeed(3);

    //scene->AddCamera({5.f,0.f,-15.f} ,{0.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f});

    scene->AddCamera(RenderCamera({40.0f,-10.0f,-50.0f}));
    for(const auto& data : parameter_vector) {
        Lorenz lorenz{5000, 0.01, data};
        auto graph = CreateFloatData(*lorenz.Data());

        auto indices = std::vector<unsigned int>(std::size(*graph));
        std::iota(std::begin(indices), std::end(indices), 0);

        auto color = glm::vec3(Pick(0.0f,1.0f),Pick(0.0f,1.0f),Pick(0.0f,1.0f));

        auto lines = scene->Add(indices, *graph, GL_LINE_STRIP);
        lines->SetColor(glm::vec4(color, 0.1));
        auto points = scene->Add(indices, *graph, GL_POINTS);
        points->SetColor(color);
        static_cast<kipod::GLRenderLayout *>(points->Layout())->SetSubIndex(10, 0);
        auto steps = lorenz.GetSteps();
        auto Step = [steps](BasicObject *points)
        {
            static std::size_t current_step{0};
            const std::size_t points_buffer{1};
            static_cast<kipod::GLRenderLayout *>(points->Layout())->SetSubIndex(10, current_step);

            current_step++;
            current_step = current_step % steps;
        };

        points->SetUpdateCallback(Step);
    }
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