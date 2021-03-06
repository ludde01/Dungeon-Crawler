#include "GameObject.h"
#include <GLM/gtx/transform.hpp>
#include <GLM/gtx/compatibility.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM//gtx/quaternion.hpp>
#include <System/Log.h>

GameObject::GameObject(Mesh * mesh, Type type, const glm::vec3 & position, float timeBeforeSpawn, float boundingBoxExpand)
{
	m_mesh = mesh;
	m_isCollidable = true;
	m_position = position;
	m_timeBeforeSpawn = timeBeforeSpawn;
	m_rotation = glm::vec3(0.f);
	m_velocity = glm::vec3(0.f);
	m_scale = glm::vec3(1.f);
	m_colorTint = glm::vec3(1.f);
	m_type = type;
	updateModelMatrix();
	

	if (!mesh->getMinMaxVector().empty())
	{
		for (size_t i = 0; i < mesh->getMinMaxVector().size() - 1; i += 2)
		{
			AABB* aabb = new AABB(mesh->getMinMaxVector()[i] - boundingBoxExpand, mesh->getMinMaxVector()[i + 1] + boundingBoxExpand);
			aabb->setParentPosition(position);

			m_boundingBoxes.emplace_back(aabb);
		}
	}
	
}

GameObject::~GameObject()
{
	for(size_t i = 0; i < m_boundingBoxes.size(); i++)
		delete m_boundingBoxes[i];
}

void GameObject::internalUpdate(float dt)
{
	if (m_colorTintFadeDuration > 0.0f) {
		m_colorTintFadeDuration -= dt;
		float colorAttr = 1.0f - (m_colorTintFadeDuration / 4.0f);
		m_colorTint.g = colorAttr;
		m_colorTint.b = colorAttr;
	}
	else {
		m_colorTint = glm::vec3(1.f);
		m_colorTintFadeDuration = 0.f;
	}

	if (m_timeBeforeSpawn > 0.0f){
		m_timeBeforeSpawn -= dt;
		
		if (m_timeBeforeSpawn <= 0.0f){
			m_timeBeforeSpawn = 0.0f;
		}
	}


}

void GameObject::updateModelMatrix()
{
	m_modelMatrix = glm::mat4(1.f);
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
}

void GameObject::setPosition(const glm::vec3 & position)
{
	m_position = position;
	for (size_t i = 0; i < m_boundingBoxes.size(); i++)
	{
		m_boundingBoxes[i]->setParentPosition(position);
	}
}

void GameObject::translate(const glm::vec3 & translationVector)
{
	m_position += translationVector;
	m_velocity = glm::vec3(translationVector);
	for (size_t i = 0; i < m_boundingBoxes.size(); i++)
	{
		m_boundingBoxes[i]->setParentPosition(m_position);
	}
}

void GameObject::setVelocity(const glm::vec3 & velocity)
{
	m_velocity = velocity;
}

void GameObject::setTranslateRotation(const glm::vec3 translateRotation)
{
	m_rotation += translateRotation;
}

void GameObject::setCollidable(bool condition)
{
	m_isCollidable = condition;
}

void GameObject::setScale(const glm::vec3 & scale)
{
	m_scale = scale;
}

void GameObject::setRotation(const glm::vec3 rotation)
{
	m_rotation = rotation;
}

void GameObject::setPlayerPosition(const glm::vec3 & position)
{
	m_playerPosition = position;
}

void GameObject::setMaxMinValues(const glm::vec4& maxMinValues) {
	this->m_mesh->setMaxMinValues(maxMinValues);
}

void GameObject::setHit()
{
	m_colorTintFadeDuration = 2.f;
}

void GameObject::lookAt(const glm::vec3& position)
{
	glm::vec3 direction = glm::vec3(
		position.x - this->getPosition().x,
		0,
		position.z - this->getPosition().z);
	float angle = glm::degrees(atan2f(direction.z, direction.x));

	setRotation(glm::vec3(0.f, -angle, 0.f));
		
}

float GameObject::lerp(float start, float end, float percent)
{
	return ((start)+percent * (end - start));;
}

const bool GameObject::isSpawned() const
{
	return (m_timeBeforeSpawn <= 0.0f);
}

void GameObject::hit(const HitDescription & desc)
{

}

bool GameObject::meleeRange(float dt)
{
	return false;
}

Type GameObject::getType()
{
	return m_type;
}

std::vector<AABB*> GameObject::getBoundingBoxes() const
{
	return m_boundingBoxes;
}

const glm::vec3 & GameObject::getPosition() const
{
	return m_position;
}

const glm::vec3 & GameObject::getScale() const
{
	return m_scale;
}

const glm::vec3 & GameObject::getRotation() const
{
	return m_rotation;
}

const glm::vec3 & GameObject::getVelocity() const
{
	return m_velocity;
}

const glm::mat4 & GameObject::getModelMatrix() const
{
	return m_modelMatrix;
}

const glm::vec3 & GameObject::getPlayerPosition() const
{
	return m_playerPosition;
}

const glm::vec3 & GameObject::getColorTint() const
{
	return m_colorTint;
}

const bool GameObject::isCollidable() const
{
	return m_isCollidable;
}

const glm::vec4& GameObject::getMaxMinValues() const {
	return this->m_mesh->getMaxMinValues();
}

Mesh * GameObject::getMesh() const
{
	return m_mesh;
}
