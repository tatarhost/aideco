#pragma once

#include <Geode/Geode.hpp>
#include "../presets/AIPresetData.hpp"
#include "GeometryAnalyzer.hpp"
#include "PatternDetector.hpp"
#include <vector>
#include <functional>
#include <random>

namespace AutoDecoratorAI {

class AIDecorationEngine {
public:
    static AIDecorationEngine* get();
    
    void initialize();
    
    std::vector<DecorationPlacement> generateDecorations(
        const std::vector<geode::Ref<GameObject>>& selectedObjects,
        const AIPreset& preset,
        float densityOverride = -1.0f,
        float chaosOverride = -1.0f,
        float symmetryOverride = -1.0f,
        float detailOverride = -1.0f
    );
    
    void applyDecorationsToLevel(const std::vector<DecorationPlacement>& placements, EditorUI* editorUI);
    
    void setProgressCallback(std::function<void(const std::string&, float)> callback);
    
private:
    AIDecorationEngine();
    ~AIDecorationEngine();
    
    static AIDecorationEngine* s_instance;
    
    GeometryAnalyzer* m_geometryAnalyzer;
    PatternDetector* m_patternDetector;
    std::mt19937 m_randomGenerator;
    
    std::function<void(const std::string&, float)> m_progressCallback;
    
    void reportProgress(const std::string& status, float progress);
    
    std::vector<DecorationPlacement> generateDecorationsForCluster(
        const GeometryCluster& cluster,
        const PatternDetectionResult& patterns,
        const AIPreset& preset,
        float densityScale,
        float chaosScale,
        float symmetryScale,
        float detailScale
    );
    
    std::vector<DecorationPlacement> generateEdgeDecorations(
        const GeometryCluster& cluster,
        const std::vector<DecorationZone>& zones,
        const AIPreset& preset,
        float chaosScale
    );
    
    std::vector<DecorationPlacement> generateFillDecorations(
        const GeometryCluster& cluster,
        const std::vector<DecorationZone>& zones,
        const AIPreset& preset,
        float chaosScale,
        float detailScale
    );
    
    std::vector<DecorationPlacement> generateAccentDecorations(
        const GeometryCluster& cluster,
        const PatternDetectionResult& patterns,
        const AIPreset& preset,
        float symmetryScale
    );
    
    std::vector<DecorationPlacement> generateMicroDetails(
        const GeometryCluster& cluster,
        const std::vector<DecorationZone>& zones,
        const AIPreset& preset,
        float detailScale,
        float chaosScale
    );
    
    DecorationPlacement selectDecorationObject(
        const AIPreset& preset,
        const std::string& category,
        float chaosScale
    );
    
    cocos2d::CCPoint generatePositionInZone(
        const DecorationZone& zone,
        const GeometryCluster& cluster,
        float chaosScale
    );
    
    void applySymmetryMirroring(
        std::vector<DecorationPlacement>& placements,
        const GeometryCluster& cluster,
        const PatternDetectionResult& patterns,
        float symmetryScale
    );
    
    void applyFlowFollowing(
        std::vector<DecorationPlacement>& placements,
        const PatternDetectionResult& patterns,
        const AIPreset& preset
    );
    
    void applyAntiClutter(
        std::vector<DecorationPlacement>& placements,
        const GeometryCluster& cluster
    );
    
    bool validatePlacement(
        const DecorationPlacement& placement,
        const GeometryCluster& cluster,
        const std::vector<DecorationPlacement>& existingPlacements
    );
    
    float calculateImperfection(float chaosScale);
    cocos2d::CCPoint applyImperfection(cocos2d::CCPoint position, float chaosScale);
    
    DecorationObject selectWeightedObject(const std::vector<DecorationObject>& pool, const std::string& category);
};

}
