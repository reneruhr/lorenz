#pragma once
#include "lorenz.h"
#include "kipod.h"

namespace lorenz
{
using namespace kipod;

//class GraphLayout : public GLRenderLayout
//{
//public:
//    GraphLayout(Vectors* vectors) : GLRenderLayout()
//    {
//        SetupLayout(*vectors, GL_LINES);
//    }
//};

GLRenderLayout MakeGraphLayout(const Vectors* vectors);

class Graph : public RenderObject
{
public:
    Graph()
    {
        Init();
    }
    void Init()
    {
        Lorenz Lor{};
        AddLayout("Lorenz System", MakeGraphLayout(Lor.Data().get()));
    }
};

inline auto BaseShader()
{
    return std::make_shared<Shader>("kipod/shaders/basic.vert.glsl", "kipod/shaders/basic.frag.glsl");
}

class LorenzScene : public RenderScene, public Listener
{
    using Objects = std::vector<std::shared_ptr<RenderObject>>;
    using Shaders = std::vector<std::shared_ptr<Shader>>;
    Objects objects_{};
    Shaders shaders_{};
public:
    LorenzScene(int w, int h) : RenderScene(w,h) {}
    void Add(std::shared_ptr<Graph> graph) { objects_.push_back(graph);}
    void Add(std::shared_ptr<Shader> shader) {shaders_.push_back(shader); }
    void Setup() override
    {
        Add(BaseShader());
        Add(std::make_shared<Graph>());
        AddCamera(RenderCamera({0.0f,0.0f,-10.0f}));
        SetActiveCamera(0);
        shaders_[0]->AttachUniform<glm::mat4>("mvp");
        shaders_[0]->AttachUniform<glm::vec4>("color");



        LOG_ENGINE("Finished LorenzScene Setup");
    }
    void Draw() override
    {
        framebuffer_->Bind();
        glEnable(GL_DEPTH_TEST);

        for(auto& m : objects_)
        {
            auto transform = m->Transform();
            auto mvp = cameras_[0]->projection_view_matrix_ * transform;
            shaders_[0]->SetUniform<glm::vec4>("color", {1.f,1.f,1.f,1.f});
            shaders_[0]->SetUniform<glm::mat4>("mvp", mvp);
            shaders_[0]->Use();
            m->Draw();
        }
        kipod::RenderManager::Bind(0);
    }


    void Signup() override
    {
        kipod::Events::Signup(this, kipod::EventCategoryKeyboard); LOG_CATEGORY_NAME(kipod::EventCategoryKeyboard);
    }

    void ProcessKeys(kipod::KeyPressedEvent &event)
    {}

    void Receive(std::shared_ptr<kipod::Event> event) override
    {
        Process<kipod::KeyPressedEvent>(event, BIND_EVENT_FN(ProcessKeys));
    }
};

class LorenzSidebar : public Sidebar
{
public:
    explicit LorenzSidebar(std::shared_ptr<RenderScene> scene) : kipod::Sidebar(std::move(scene)) {}
    void SideBarContent() override {}
};

class LorenzModuleMenu : public MenuModule
{
protected:
    void Draw() override {}
};

class LorenzModule : public Module{
public:
    LorenzModule(int width, int height): Module("Lorenz System")
    {
        scene_ = std::make_shared<LorenzScene>(LorenzScene(width, height));
        sidebar_ = std::make_unique<LorenzSidebar>(LorenzSidebar{scene_});
        console_ = nullptr;
        menu_ = std::make_unique<LorenzModuleMenu>();
    }
};

}



