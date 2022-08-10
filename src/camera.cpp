#include <camera.h>
#include <cmath>

void Camera::updateVectors() {
    this->front = glm::normalize(this->front);
    this->right = glm::normalize(glm::cross(this->front, this->worldup));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
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
    glm::qua<float> Rx = glm::qua<float>(glm::cos(angle.z),
                                         this->getCameraRight().x*glm::sin(angle.x),
                                         this->getCameraRight().y*glm::sin(angle.x),
                                         this->getCameraRight().z*glm::sin(angle.x)),
                Ry = glm::qua<float>(glm::cos(angle.z),
                                     this->getCameraUp().x*glm::sin(angle.y),
                                    this->getCameraUp().y*glm::sin(angle.y),
                                    this->getCameraUp().z*glm::sin(angle.y)),
                Rz = glm::qua<float>(glm::cos(angle.z),
                                     this->getCameraFront().x*glm::sin(angle.z),
                                    this->getCameraFront().y*glm::sin(angle.z),
                                    this->getCameraFront().z*glm::sin(angle.z));
    this->rotateByQuaternions(Rx*Rz*Ry);
}


