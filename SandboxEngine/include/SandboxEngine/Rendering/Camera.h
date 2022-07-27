#pragma once
#include "Events.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace SE
{
    class Camera
    {
    public:
        inline Camera(const glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), const float speed = 1.0f)
            : position(position), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f),
            pitch(0.0f), yaw(-90.0f),
            FOV(45.0f),
            sensivity(0.1f),
            speed(speed)
        {
            
        }

        inline glm::mat4 getViewMatrix() { return glm::lookAt(position, position + front, up); }

        inline void processKeyboard(Events& events, float deltaTime)
        {
            float cameraSpeed = static_cast<float>(this->speed * deltaTime);
            if (events.isKey(SE::Key::W, SE::Action::PRESSED)) position += cameraSpeed * front;
            if (events.isKey(SE::Key::S, SE::Action::PRESSED)) position -= cameraSpeed * front;
            if (events.isKey(SE::Key::A, SE::Action::PRESSED)) position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
            if (events.isKey(SE::Key::D, SE::Action::PRESSED)) position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
            if (events.isKey(SE::Key::SPACE, SE::Action::PRESSED)) position += up * cameraSpeed;
            if (events.isKey(SE::Key::LEFT_CONTROL, SE::Action::PRESSED)) position -= up * cameraSpeed;
        }

        inline void processMouseMovement(float xoffset, float yoffset)
        {
            yaw += xoffset * sensivity;
            pitch += yoffset * sensivity;

            // To avoid flipping:
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            // TODO: try to not to use temp var
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            this->front = glm::normalize(front);
        }

        inline void processScroll(float offset)
        {
            FOV -= offset;
        }

        glm::vec3 position, front, up;
        float pitch, yaw;
        float FOV;
        float sensivity;
        float speed;
    };
}