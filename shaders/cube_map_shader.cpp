//
// Created by janos on 10.06.20.
//

#include "cube_map_shader.hpp"

#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Corrade/Utility/FormatStl.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>

using namespace Magnum;


CubeMapShader::CubeMapShader(Phase phase){

    MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GL450);

    const Utility::Resource rs{"tmo-data"};

    GL::Shader vert{GL::Version::GL450, GL::Shader::Type::Vertex};
    GL::Shader frag{GL::Version::GL450, GL::Shader::Type::Fragment};

    vert.addSource(rs.get("cube_map_shader.vert"));
    switch (phase) {
        case Phase::EquirectangularConversion :
            frag.addSource(rs.get("cube_map_shader_equirectangular.frag"));
            break;
        case Phase::IrradianceConvolution :
            frag.addSource(rs.get("cube_map_shader_irradiance.frag"));
            break;
        case Phase::Prefilter :
            frag.addSource(rs.get("cube_map_shader_prefilter.frag"));
            break;
    }

    CORRADE_INTERNAL_ASSERT_OUTPUT(Mg::GL::Shader::compile({vert, frag}));

    attachShaders({vert, frag});

    CORRADE_INTERNAL_ASSERT_OUTPUT(link());

    projectionMatrixUniform = uniformLocation("projectionMatrix");
    transformationMatrixUniform = uniformLocation("transformationMatrix");

}