#pragma once

#include <Geode/Geode.hpp>
#include "../presets/AIPresetData.hpp"
#include <vector>

namespace AutoDecoratorAI {

class PatternDetector {
public:
    static PatternDetector* get();
    
    PatternDetectionResult detectPatterns(const std::vector<geode::Ref<GameObject>>& objects);
    
private:
    PatternDetector();
    ~PatternDetector();
    
    static PatternDetector* s_instance;
    
    SymmetryType detectSymmetry(const std::vector<geode::Ref<GameObject>>& objects);
    float calculateSymmetryStrength(const std::vector<geode::Ref<GameObject>>& objects, SymmetryType type);
    
    bool detectRepetition(const std::vector<geode::Ref<GameObject>>& objects, float& period);
    cocos2d::CCPoint detectFlowDirection(const std::vector<geode::Ref<GameObject>>& objects);
    
    float calculateDensityImbalance(const std::vector<geode::Ref<GameObject>>& objects);
    std::vector<cocos2d::CCRect> findEmptyZones(const std::vector<geode::Ref<GameObject>>& objects);
    std::vector<cocos2d::CCRect> findDenseZones(const std::vector<geode::Ref<GameObject>>& objects);
    
    bool isSymmetricPair(const geode::Ref<GameObject>& a, const geode::Ref<GameObject>& b, SymmetryType type, float axis);
    float calculateAxisPosition(const std::vector<geode::Ref<GameObject>>& objects, SymmetryType type);
};

}
