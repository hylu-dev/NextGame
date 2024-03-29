#include "stdafx.h"
#include "PlayerController.h"
#include "BoxCollider.h"
#include "MeshFilter.h"
#include "CubeMesh.h"
#include "TimingFunction.h"

void PlayerController::Initialize() {
	MeshFilter* meshFilter = parentEntity->AddComponent<MeshFilter>();
	meshFilter->LoadMesh(CubeMesh(4));
	meshFilter->SetColor(float3(0, 1, 0));
	BoxCollider* collider = parentEntity->AddComponent<BoxCollider>();
	collider->dimensions = parentEntity->GetTransform().scale;
	collider->SetCollisionHook([](Collider* c1, Collider* c2) {
		if (c2->parentEntity->Name() == "EnemyBox") {
			Scene::Get().RemoveEntity(c2->parentEntity);
		}
		else if (c2->parentEntity->Name() == "Wall") {
			float3& p1 = c1->parentEntity->GetTransform().position;
			float3& p2 = c2->parentEntity->GetTransform().position;
			float3 direction = (p1 - p2).Normalized();
			p1 += direction * 10.0f * Time::Get().DeltaTime();
		}
		});
	animator = parentEntity->AddComponent<Animator>();
	emitter = parentEntity->AddComponent<ParticleEmitter>();
	emitter->burstSize = 100;
	emitter->active = false;
	emitter->size = 3;
	emitter->color = float3(0.3, 1, 0.6);
	emitter->shape = EmissionShape::RADIAL;
	emitter->speed = 50.0f;
	emitter->coneWidth = 30.0f;
}

void PlayerController::Update() {
	float3& position = parentEntity->GetTransform().position;
	float3& rotation = parentEntity->GetTransform().rotation;
	float3& scale = parentEntity->GetTransform().scale;
	float speed = 50.0f * Time::Get().DeltaTime();

	if (App::IsKeyPressed(VK_LSHIFT)) {
		speed *= 2;
	}
	if (App::IsKeyPressed(VK_OEM_MINUS)) {
		if (!minusPressed) {
			animator->Animate(rotation, rotation + float3(0, 0, -90.0f), 1.0f, new EaseInOutBack());
			animator->Animate(scale, scale*0.75f, 1.0f, new EaseInOutBack());
			emitter->Emit();
		}
		minusPressed = true;
	}
	else {
		minusPressed = false;
	}
	if (App::IsKeyPressed(VK_OEM_PLUS)) {
		if (!plusPressed) {
			animator->Animate(rotation, rotation + float3(-180.0f, 180.0f, 0), 1.0f, new EaseInOutBack());
			animator->Animate(scale, scale * 1.5f, 1.0f, new EaseInOutBack());
			emitter->Emit();
		}
		plusPressed = true;
	}
	else {
		plusPressed = false;
	}


	if (App::IsKeyPressed('F')) {
		position.x -= speed;
		direction = float3(1.0f, 0, 0);
	}
	if (App::IsKeyPressed('H')) {
		position.x += speed;
		direction = float3(-1.0f, 0, 0);
	}
	if (App::IsKeyPressed('T')) {
		position.y += speed;
		direction = float3(0, -1.0, 0);
	}
	if (App::IsKeyPressed('G')) {
		position.y -= speed;
		direction = float3(0, 1.0f, 0);
	}
}

void PlayerController::Destroy() {
}
