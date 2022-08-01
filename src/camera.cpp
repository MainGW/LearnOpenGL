#include <camera.h>
#include <cmath>

void Camera::updateVectors() {
    this->front = glm::normalize(this->front);
    this->right = glm::normalize(glm::cross(this->front, this->worldup));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(pos, pos + front, up);
}

void Camera::translation(glm::vec3 direction) {
    pos += direction;
    updateVectors();
}

void Camera::rotateByQuaternions(glm::qua<float> angle) {
    this->front = angle * this->front;
    updateVectors();
}

void Camera::rotateByEulerAngle(glm::vec3 angle) {
    this->front.x = cos(glm::radians(angle.z)) * cos(glm::radians(angle.x));
    this->front.y = sin(glm::radians(angle.z));
    this->front.z = cos(glm::radians(angle.z)) * sin(glm::radians(angle.x));
    updateVectors();
}


