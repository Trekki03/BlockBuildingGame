#ifndef BLOCKBUILDINGGAME_CAMERACONTROLLER_H
#define BLOCKBUILDINGGAME_CAMERACONTROLLER_H

#include <vector>
#include "Camera.h"

namespace engine {

    class CameraController
    {
    private:
        unsigned int m_activeCameraIndex = 0;
        std::vector<Camera*> m_cameras;

    public:
        CameraController() = default;
        ~CameraController();

        void SetActiveCamera(unsigned long long int cameraID);
        void SetActiveCameraIndex(unsigned int index);
        Camera* GetActiveCameraPointer();
        unsigned int GetActiveCameraIndex() const;

        unsigned long long int CreateCamera(glm::vec3 initialPosition, float initialPitch, float initialYaw, float initialFov);
        void DeregisterCamera(unsigned long long int cameraID);
    };
}

#endif //BLOCKBUILDINGGAME_CAMERACONTROLLER_H
