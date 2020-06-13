//
// Created by janos on 08.11.19.
//

#pragma once


#include "arc_ball_camera.hpp"
#include "pbr_shader.hpp"
#include "cube_map_shader.hpp"
#include "background_shader.hpp"
#include "types.hpp"
#include "drawables.hpp"

#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/StaticArray.h>

#include <Magnum/GL/Texture.h>
#include <Magnum/GL/CubeMapTexture.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Shaders/Phong.h>

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/ImGuiIntegration/Context.h>
#include <Corrade/Containers/Array.h>

namespace Cr = Corrade;
namespace Mg = Magnum;

struct Viewer: public Platform::Application{
    explicit Viewer(int argc, char** argv);

    void drawEvent() override;
    void viewportEvent(ViewportEvent& event) override;
    void keyPressEvent(KeyEvent& event) override;
    void mousePressEvent(MouseEvent& event) override;
    void mouseReleaseEvent(MouseEvent& event) override;
    void mouseMoveEvent(MouseMoveEvent& event) override;
    void mouseScrollEvent(MouseScrollEvent& event) override;
    void keyReleaseEvent(KeyEvent& event) override;
    void textInputEvent(TextInputEvent& event) override;

    void drawOptions();

    Cr::Containers::Optional<ArcBallCamera> camera;
    DrawableGroup drawables;
    Scene scene;

    Mg::GL::Texture2D texture{Mg::NoCreate};
    Mg::GL::Mesh mesh{Mg::NoCreate};
    PbrShader pbrShader{Mg::NoCreate};
    Mg::Shaders::Phong phongShader{Mg::NoCreate};
    bool trackingMouse = false;

    Mg::GL::Texture2D colorMapTexture{Mg::NoCreate};

    Mg::GL::Mesh cube{Mg::NoCreate};
    GL::CubeMapTexture hdrIrradianceMap{Mg::NoCreate};
    GL::CubeMapTexture hdrCubeMap{Mg::NoCreate};
    GL::Texture2D hdrEquirectangular{Mg::NoCreate};
    BackgroundShader backgroundShader{Mg::NoCreate};

    Mg::ImGuiIntegration::Context imgui{Mg::NoCreate};
};