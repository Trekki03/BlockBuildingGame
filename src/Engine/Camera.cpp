#include "Camera.h"

/*
 * Initialize members and give CameraID and value corresponding to the address of the pointer.
 * This has the advantage, that the ID of the Camera is unique, because there can't be another object with the
 * same address, as long as this instance exists.
*/
engine::Camera::Camera(glm::vec3 position, float pitch, float yaw, float fov):
        m_pitch(pitch), m_yaw(yaw), m_fov(fov), m_xPos(position.x), m_yPos(position.y), m_zPos(position.z)
{
    m_cameraID = (unsigned long long int) this;
}

// Adding Functions
// ------------------------------------------------------------------------------//
void engine::Camera::AddFov(float fov)
{
    float newFov = m_fov + fov;
    // FOV has to be between 1.0 and 45.0
    if(newFov < 1.0f)
    {
        newFov = 1.0f;
    }
    else if (newFov > 45.0f)
    {
        newFov = 45.0f;
    }
    m_fov = newFov;
}

void engine::Camera::AddPitch(float pitch)
{
    float newPitch = m_pitch + pitch;
    // FOV has to be between -89.0 and 89.0
    if(newPitch > 89.0f)
    {
        newPitch = 89.0f;
    }
    else if (newPitch < -89.0f)
    {
        newPitch = -89.0f;
    }
    m_pitch = newPitch;
}

void engine::Camera::AddYaw(float yaw)
{
    m_yaw += yaw;
}

void engine::Camera::AddXPos(float xPos)
{
    m_xPos += xPos;
}

void engine::Camera::AddYPos(float yPos)
{
    m_yPos += yPos;
}

void engine::Camera::AddZPos(float zPos)
{
    m_zPos += zPos;
}

void engine::Camera::AddPositionVector(glm::vec3 position)
{
    m_xPos += position.x;
    m_yPos += position.y;
    m_zPos += position.z;
}

// Setter Functions
// ------------------------------------------------------------------------------//

void engine::Camera::SetFov(float fov)
{
    float newFov = fov;
    // FOV has to be between 1.0 and 45.0
    if(newFov < 1.0f)
    {
        newFov = 1.0f;
    }
    else if (newFov > 45.0f)
    {
        newFov = 45.0f;
    }
    m_fov = newFov;
}

void engine::Camera::SetPitch(float pitch)
{
    float newPitch = pitch;
    // FOV has to be between -89.0 and 89.0
    if(newPitch > 89.0f)
    {
        newPitch = 89.0f;
    }
    else if (newPitch < -89.0f)
    {
        newPitch = -89.0f;
    }
    m_pitch = newPitch;
}

void engine::Camera::SetYaw(float yaw)
{
    m_yaw = yaw;
}

void engine::Camera::SetXPos(float xPos)
{
    m_xPos = xPos;
}

void engine::Camera::SetYPos(float yPos)
{
    m_yPos = yPos;
}

void engine::Camera::SetZPos(float zPos)
{
    m_zPos = zPos;
}

void engine::Camera::SetPositionVector(glm::vec3 position)
{
    m_xPos = position.x;
    m_yPos = position.y;
    m_zPos = position.z;
}

// Getter Functions
// ------------------------------------------------------------------------------//

unsigned long long int engine::Camera::GetId() const
{
    return m_cameraID;
}

float engine::Camera::GetFov() const
{
    return m_fov;
}

float engine::Camera::GetYaw() const
{
    return m_yaw;
}

float engine::Camera::GetPitch() const
{
    return  m_pitch;
}

glm::vec3 engine::Camera::GetDirectionVector() const
{
    glm::vec3 direction;
    direction.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    direction.y = sinf(glm::radians(m_pitch));
    direction.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    return glm::normalize(direction);
}

glm::vec3 engine::Camera::GetPositionVector() const
{
    return {m_xPos, m_yPos, m_zPos};
}
