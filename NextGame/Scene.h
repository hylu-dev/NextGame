#pragma once

#include <list>
#include "Camera.h"

class Entity;

class Scene
{
private:
	unsigned int id_counter = 0;

	std::list<Entity*> entities;
	std::list<Entity*> entitiesToDestroy;

	Camera* camera = nullptr;
	static Scene* instance;

public:
	static Scene& Get() {
		if (instance == nullptr) {
			instance = new Scene();
		}
		return *instance;
	}

	void Initialize(float _fov, float _near, float _far);

	void Update();

	void Destroy();

	Camera* GetCamera() { return camera; }

	Entity* CreateEntity(std::string name);

	Entity* GetEntityByName(std::string name);

	Entity* GetEntityById(unsigned int _id);

	void RemoveEntity(Entity* entity);

	void RemoveEntityById(unsigned int _id);

private:
	Scene() = default;
	Scene Renderer(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
};

