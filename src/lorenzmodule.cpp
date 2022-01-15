//
// Created by Rene Ruhr on 15/01/2022.
//

#include "lorenzmodule.h"

kipod::GLRenderLayout lorenz::MakeGraphLayout(const lorenz::Vectors *vectors)
{
    auto layout = GLRenderLayout{};
    std::vector<Vec3> vectors_f(vectors->size());
    for(size_t i = 0, e= vectors->size(); i<e; ++i ){
        for(size_t j =0; j<3; ++j) vectors_f[i][j] = (*vectors)[i][j];
    }


    layout.SetupLayout(vectors_f, GL_POINTS);
    LOG_ENGINE("Uploaded {} Points", vectors_f.size());

    return layout;
}
