#include "Projectile.h"

Projectile::Projectile(const glm::vec3& startPosition, const std::vector<Node>& path, float damage, float speed, float cellSize)
{
	m_position = startPosition;
	m_path = path;
	m_damage = damage;
	m_speed = speed;
	m_cellSize = cellSize;
	m_isAtDestination = false;

	m_aabb = new AABB(glm::vec3(-m_cellSize * 0.25f, 0.0f, -m_cellSize * 0.25f), glm::vec3(m_cellSize * 0.25f, 0.0f, m_cellSize * 0.25f));

	m_internalAnimIndex = 0;
	m_internalAnimTimer = 0.0f;
}

Projectile::~Projectile()
{
	delete m_aabb;
}

void Projectile::update(float dt)
{

	if (m_path.size() > 0)
	{
		int index = m_path.size() - 1;
		const Node& currentNode = m_path.at(index);
		const glm::vec3& myPos = getPosition();

		float xDir = currentNode.x - myPos.x;
		float zDir = currentNode.z - myPos.z;
		float length = sqrtf(xDir * xDir + zDir * zDir);

		glm::vec3 velocity = (glm::vec3(xDir, 0.0f, zDir) / length) * m_speed * dt;
		m_internalAnimTimer += dt;

		// Move towards the node
		m_position += velocity;

		m_aabb->setParentPosition(m_position);

		// If being close enough then pop it from the path vector
		if (length <= m_cellSize * 0.25f)
		{
			m_path.erase(m_path.begin() + index);
		}
	}
	else
	{
		m_isAtDestination = true;
	}

}

void Projectile::resetInternalAnimTimer()
{
	m_internalAnimTimer = 0.0f;
}

void Projectile::setInternalAnimIndex(int index)
{
	m_internalAnimIndex = index;
}

AABB* Projectile::getAABB() const
{
	return m_aabb;
}

const float Projectile::getDamage() const
{
	return m_damage;
}

const glm::vec3& Projectile::getPosition() const
{
	return m_position;
}

const bool Projectile::isAtDestination() const
{
	return m_isAtDestination;
}

const int& Projectile::getInternalAnimIndex() const
{
	return m_internalAnimIndex;
}

const float& Projectile::getInternalAnimTimer() const
{
	return m_internalAnimTimer;
}
