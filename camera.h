#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <QDebug>

class Camera {
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    void forward(float delta);
    void backward(float delta);
    void left(float delta);
    void right(float delta);
    void rise(float delta);
    void drop(float delta);
    void speedUp(int value);
    void rotate(float pitch, float yaw);
    float zoom(int angle);
    glm::vec3 const& position() const;
    glm::mat4 lookAt();
private:
    glm::vec3 pos_;
    glm::vec3 front_;
    glm::vec3 up_;
    float pitch_ = 0.0f;
    float yaw_ = 0.0f;
    float fav_ = 45.0f;
    float const speed_ = 10.0f;
};

inline void Camera::forward(float delta)
{
    auto dir = front_;
    dir.y = 0.0f;
    pos_ += delta * speed_ * glm::normalize(dir);
    qDebug("position(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);

}

inline void Camera::backward(float delta)
{
    auto dir = front_;
    dir.y = 0.0f;
    pos_ -= delta * speed_ * glm::normalize(dir);
    qDebug("position(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

inline void Camera::left(float delta)
{
    auto dir = glm::cross(front_, up_);
    dir.y = 0.0f;
    pos_ -= delta * speed_ * glm::normalize(dir);
    qDebug("position(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

inline void Camera::right(float delta)
{
    auto dir = glm::cross(front_, up_);
    dir.y = 0.0f;
    pos_ += delta * speed_ * glm::normalize(dir);
    qDebug("position(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

inline void Camera::rise(float delta)
{
    pos_ += delta * speed_ * glm::vec3(0.0f, 1.0f, 0.0f);
    qDebug("position(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

inline void Camera::drop(float delta)
{
    pos_ -= delta * speed_ * glm::vec3(0.0f, 1.0f, 0.0f);
    qDebug("position(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
}

inline glm::mat4 Camera::lookAt()
{
    return glm::lookAt(pos_, pos_ + front_, up_);
}

inline float Camera::zoom(int angle)
{
    fav_ -= angle * 0.05f;  //sensitivity
    fav_ = glm::clamp(fav_, 5.0f, 45.0f);
    return glm::radians(fav_);
}

inline glm::vec3 const& Camera::position() const
{
    return pos_;
}
#endif // CAMERA_H
