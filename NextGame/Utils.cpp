#include "stdafx.h"
#include "Utils.h"

namespace Utils {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    float RandomFloatUniform() {
        return dis(gen);
    }

    float RandomFloat(float min, float max) {
        return min + (max - min) * dis(gen);
    }

    float3 RandomFloat3(float3 min, float3 max) {
        return float3(
            min.x + (max.x - min.x) * dis(gen),
            min.y + (max.y - min.y) * dis(gen),
            min.z + (max.z - min.z) * dis(gen)
        );
    }

    float Clamp(float value, float minVal, float maxVal) {
        return max(minVal, min(value, maxVal));
    }
    bool IsInRange(float value, float minVal, float maxVal) {
        return value >= minVal && value <= maxVal;
    }
    float Logistic(float value, float approachRate) {
        return 1.0 / (1.0 + std::exp(-approachRate * value));
    }
}