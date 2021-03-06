//
// Created by janos on 27.02.20.
//

#include "drawables.h"

#include <Magnum/Shaders/Flat.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Shaders/MeshVisualizer.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Math/Vector3.h>

using namespace Magnum;

MeshDrawable::MeshDrawable(Object& obj, Mg::GL::Mesh& m, DrawableGroup* group, Mg::GL::Texture2D* t):
        Drawable(obj, group),
        mesh(m),
        texture(t)
{
}


FlatDrawable::FlatDrawable(Object& object, Mg::GL::Mesh& m, Mg::Shaders::Flat3D& s, DrawableGroup* group):
        MeshDrawable(object, m, group),
        shader(s)
{
}

void FlatDrawable::draw(const Magnum::Matrix4& transformationMatrix, Magnum::SceneGraph::Camera3D& camera) {
    if (texture) {
        shader.bindTexture(*texture);
    } else {
        shader.setColor(color);
    }
    shader.setTransformationProjectionMatrix(camera.projectionMatrix() * transformationMatrix)
            .draw(mesh);
}

VertexColorDrawable::VertexColorDrawable(Object& object, Mg::GL::Mesh& m, Mg::GL::AbstractShaderProgram& shader, DrawableGroup* group):
        MeshDrawable(object, m, group),
        shader(dynamic_cast<Mg::Shaders::VertexColor3D&>(shader))
{
}

void VertexColorDrawable::draw(const Magnum::Matrix4& transformationMatrix, Mg::SceneGraph::Camera3D& camera) {
    if(!(this->show)) return;
    shader.setTransformationProjectionMatrix(camera.projectionMatrix() * transformationMatrix)
          .draw(mesh);
}

PhongDiffuseDrawable::PhongDiffuseDrawable(Object& object, Mg::GL::Mesh& m, Mg::GL::AbstractShaderProgram& shader, DrawableGroup* group):
        MeshDrawable(object, m, group),
        shader(dynamic_cast<Magnum::Shaders::Phong&>(shader))
{
}

void PhongDiffuseDrawable::draw(const Mg::Matrix4& transformationMatrix, Mg::SceneGraph::Camera3D& camera) {
    if(texture) {
        shader.bindDiffuseTexture(*texture);
    } else {
        shader.setDiffuseColor(0x2f83cc_rgbf)
                .setShininess(200.0f)
                .setLightPosition({5.0f, 5.0f, 7.0f})
                .setTransformationMatrix(transformationMatrix)
                .setNormalMatrix(transformationMatrix.normalMatrix())
                .setProjectionMatrix(camera.projectionMatrix())
                .draw(mesh);
        return;
    }
    shader.setLightPosition({10.0f, 10.0f, 10.0f})
          .setTransformationMatrix(transformationMatrix)
          .setNormalMatrix(transformationMatrix.normalMatrix())
          .setProjectionMatrix(camera.projectionMatrix())
          .draw(mesh);
}

MeshVisualizerDrawable::MeshVisualizerDrawable(Object& object, Mg::GL::Mesh& m, Mg::GL::AbstractShaderProgram& s, DrawableGroup* group):
        MeshDrawable(object, m, group),
        shader(dynamic_cast<Mg::Shaders::MeshVisualizer3D&>(s))
{
}

void MeshVisualizerDrawable::draw(const Magnum::Matrix4& transformationMatrix, Magnum::SceneGraph::Camera3D& camera) {

    shader.setViewportSize(Mg::Vector2{Mg::GL::defaultFramebuffer.viewport().size()})
          .setTransformationMatrix(transformationMatrix)
          .setProjectionMatrix(camera.projectionMatrix())
          .setWireframeWidth(wireframeWidth)
          .setWireframeColor(wireframeColor)
          .setSmoothness(smoothness)
          .setColor(color)
          .draw(mesh);
}


FaceColorDrawable::FaceColorDrawable(Object& object, Mg::GL::Mesh& m, Mg::GL::AbstractShaderProgram& s, DrawableGroup* group):
        MeshDrawable(object, m, group),
        shader(dynamic_cast<Mg::Shaders::MeshVisualizer3D&>(s))
{
}

void FaceColorDrawable::draw(const Magnum::Matrix4& transformationMatrix, Magnum::SceneGraph::Camera3D& camera) {
    if(!texture) return;
    shader.setViewportSize(Mg::Vector2{Mg::GL::defaultFramebuffer.viewport().size()})
          .setTransformationMatrix(transformationMatrix)
          .setProjectionMatrix(camera.projectionMatrix())
          .setColorMapTransformation(offset, scale)
          .bindColorMapTexture(*texture)
          .draw(mesh);
}
