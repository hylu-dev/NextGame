#include "stdafx.h"
#include "Particle.h"
#include "ParticleSystem.h"

void Particle::Initialize() {
	Renderable::Initialize();
	p1 = float3::Zero;
	p2 = float3(0, 1.0f, 0);
	
}

void Particle::PostInitialize() {
	Transform& transform = parentEntity->GetTransform();
	transform.scale = size;
	rotationDirection = float3(
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1),
		Utils::RandomFloat(-1, 1)
	).Normalized();
	if (rotate) {
		transform.rotation = float3(
			Utils::RandomFloat(-180, 180),
			Utils::RandomFloat(-180, 180),
			Utils::RandomFloat(-180, 180)
		);
	}

	if (this->parentEntity != nullptr) {
		matScale = float4x4::CreateScale(transform.scale);
		matRotate = float4x4::CreateRotation(transform.rotation);
		matTranslate = float4x4::CreateTranslation(transform.position);
	}
}

void Particle::Update() {
	if (fade) {
		color -= Time::Get().DeltaTime()/lifetime;
	}

	Transform& transform = parentEntity->GetTransform();
	transform.position += direction * (speed * Time::Get().DeltaTime());
	if (rotate) {
		transform.rotation += rotationDirection*(rotationSpeed*Time::Get().DeltaTime());
	}
	// Set transformation matrices
	if (this->parentEntity != nullptr) {
		matScale = float4x4::CreateScale(transform.scale);
		matRotate = float4x4::CreateRotation(transform.rotation);
		matTranslate = float4x4::CreateTranslation(transform.position);
	}
	timer += Time::Get().DeltaTime();

	if (timer > lifetime) {
		ParticleSystem::Get().RemoveParticle(parentEntity);
	}
}

void Particle::Destroy() {
	Renderable::Destroy();
}

void Particle::Render() {
	float4x4 transformationMatrix = 
		matScale *
		matRotate *
		matTranslate *
		Scene::Get().GetCamera()->GetView() * 
		Scene::Get().GetCamera()->GetProjection();
	float3 p1Transformed = transformationMatrix*p1;
	float3 p2Transformed = transformationMatrix*p2;

	p1Transformed /= p1Transformed.w;
	p2Transformed /= p2Transformed.w;

	p1Transformed = (p1Transformed + float3(1, 1, 0)) * 0.5f;
	p2Transformed = (p2Transformed + float3(1, 1, 0)) * 0.5f;

	p1Transformed.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
	p1Transformed.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);
	p2Transformed.x *= static_cast<float>(APP_VIRTUAL_WIDTH);
	p2Transformed.y *= static_cast<float>(APP_VIRTUAL_HEIGHT);

	bool inBounds = p1Transformed.x < APP_VIRTUAL_WIDTH && p1Transformed.x > 0 &&
		p1Transformed.y < APP_VIRTUAL_HEIGHT && p1Transformed.y > 0;

	inBounds = inBounds && p2Transformed.x < APP_VIRTUAL_WIDTH && p2Transformed.x > 0 &&
		p2Transformed.y < APP_VIRTUAL_HEIGHT && p2Transformed.y > 0;

	if (inBounds) {
		App::DrawLine(
			p1Transformed.x, p1Transformed.y,
			p2Transformed.x, p2Transformed.y,
			color.x, color.y, color.z
		);
	}
}