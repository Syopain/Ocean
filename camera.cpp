#include "camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) :
    pos_(pos),
    front_(front),
    up_(up)
{
    rotate(0, -90);
}

void Camera::rotate(float pitch, float yaw)
{
    pitch_ += pitch;
    yaw_ += yaw;
    pitch_ = std::max(std::min(pitch_, 89.0f), -89.0f);

    qDebug("pitch:%.2f, yaw:%.2f;", pitch_, yaw_);

    front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
    front_.y = sin(glm::radians(pitch_));
    front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
    front_ = glm::normalize(front_);
}
