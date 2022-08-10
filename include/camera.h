#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

/**
 * @brief OpenGL Camera class.
 */
class Camera {

private:
    glm::vec3 pos, front, up, right, worldup;
    void updateVectors();
public:
    /**
     * @breif Initialize a new camera object
     * @param pos Camera position vector.
     * @param target Camera target vector.
     * @param up World Up vector.
     */
    explicit Camera(glm::vec3 pos       = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 target    = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 up        = glm::vec3(0.0f, 1.0f, 0.0f)): pos(pos), front(target - pos), worldup(up)
                    { updateVectors(); }
    void translation(glm::vec3 direction);
    void rotateByQuaternions(glm::qua<float>);
    void rotateByEulerAngle(glm::vec3 angle);

    [[nodiscard]] glm::vec3 getCameraPos() const {
        return this->pos;
    }
    [[nodiscard]] inline glm::vec3 getCameraFront() const {
        return this->front;
    }
    [[nodiscard]] inline glm::vec3 getCameraRight() const {
        return this->right;
    }
    [[nodiscard]] inline glm::vec3 getCameraUp() const {
        return this->up;
    }
    [[nodiscard]] glm::mat4 getViewMatrix() const {
        return glm::lookAt(this->pos, this->front + this->pos, this->up);
    }
};

#endif