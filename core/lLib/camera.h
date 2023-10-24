#include <lLib/transformations.h>
namespace lLib {
	struct Camera {
		ew::Vec3 position; //Camera body position
		ew::Vec3 target; //Position to look at
		float fov; //Vertical field of view in degrees
		float aspectRatio; //Screen width / Screen height
		float nearPlane; //Near plane distance (+Z)
		float farPlane; //Far plane distance (+Z)
		bool orthographic; //Perspective or orthographic?
		float orthoSize; //Height of orthographic frustum
		ew::Mat4 ViewMatrix() {
			return LookAt(position, target, ew::Vec3(0, 1, 0));
		}; //World->View
		ew::Mat4 ProjectionMatrix() {
			if (orthographic) {
				return Orthographic(orthoSize, aspectRatio, nearPlane, farPlane);
			}
			else {
				return Perspective(ew::Radians(fov), aspectRatio, nearPlane, farPlane);
			}
		};
	}; //View->Clip
	struct CameraControls {
		double prevMouseX, prevMouseY; //Mouse position from previous frame
		float yaw = -90, pitch = 0; //Degrees
		float mouseSensitivity = 0.1f; //How fast to turn with mouse
		bool firstMouse = true; //Flag to store initial mouse position
		float moveSpeed = 5.0f; //How fast to move with arrow keys (M/S)
	};

}

