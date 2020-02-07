//
// Created by janos on 31.01.20.
//


#pragma once

#include <OpenMesh/Core/Utils/vector_traits.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Utils/color_cast.hh>

#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Vector.h>


struct MagnumTraits : public OpenMesh::DefaultTraits{
    using Point = Magnum::Vector3;
    using Normal = Magnum::Vector3;
    using TexCoord2D = Magnum::Vector2;
    using Color = Magnum::Color4;
};



namespace OpenMesh{


    template<class T>
    struct vector_traits<Magnum::Math::Vector3<T>>{
        using vector_type = Magnum::Math::Vector3<T>;
        using value_type = T;
        static size_t size (){ return 3;}
        static const size_t size_ = 3;
    };


    template<class T>
    struct vector_traits<Magnum::Math::Color4<T>>{
        using vector_type = Magnum::Math::Color4<T>;
        using value_type = T;
        static size_t size (){ return 3;}
        static const size_t size_ = 3;
    };


    template<class T>
    struct vector_traits<Magnum::Math::Vector2<T>>{
        using vector_type = Magnum::Math::Vector2<T>;
        using value_type = T;
        static size_t size (){ return 2;}
        static const size_t size_ = 2;
    };

    template <>
    struct color_caster<Magnum::Color4, Vec3f>
    {
        using return_type = Magnum::Color4;

        inline static return_type cast(const Vec3f& src)
        {
            return return_type(src[0], src[1], src[2], 1.f);
        }
    };


}

namespace Magnum {
    namespace Math {


        template<std::size_t n, class T>
        auto norm(const Vector<n, T> &x) {
            return x.length();
        }

        template<std::size_t n, class T>
        auto sqrnorm(const Vector<n, T> &x) {
            return dot(x, x);
        }


        template<std::size_t n, class T>
        auto normalize(Vector<n, T> &x) {
            x = x.normalized();
            return x;
        }


        template<std::size_t n, class T>
        decltype(auto) vectorize(Vector<n, T> &x, typename Vector<n, T>::Type const &val) {
            x = Math::Vector<n, T>(val);
            return x;
        }


    }
}


using T = OpenMesh::vector_traits<Magnum::Vector3>::value_type;
using Mesh = OpenMesh::TriMesh_ArrayKernelT<MagnumTraits>;