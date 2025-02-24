#include "RotationComponent.h"

void dae::RotationComponent::Update(float deltaTime)
{
	m_elapsedSec += deltaTime;

	float x = cos(m_radiansPerSec * m_elapsedSec);
	float y = sin(m_radiansPerSec * m_elapsedSec);

	glm::vec3 newLocalPos = { m_radius*x, m_radius*y, 0 };

	GetOwner()->SetLocalPosition(newLocalPos);
}
