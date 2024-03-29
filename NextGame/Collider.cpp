#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"

void Collider::Initialize() {
	CollisionManager::Get().AddCollider(this);
}

void Collider::Destroy() {
	CollisionManager::Get().RemoveCollider(this);
}
