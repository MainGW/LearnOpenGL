#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glad/glad.h>
#include <glm/glm.hpp>

using namespace glm;
class Camera {
private:
    vec3 pos;
    vec3 front;
    vec3 right;
    vec3 up;
public:
    Camera(vec3 pos = vec3(0.0, 0.0, 0.0) ) {};
};

#endif