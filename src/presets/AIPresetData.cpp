#include "AIPresetData.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace AutoDecoratorAI {

matjson::Value AIPreset::toJson() const {
    matjson::Value json;
    
    json["id"] = id;
    json["name"] = name;
    json["description"] = description;
    json["styleBias"] = styleBiasToString(styleBias);
    
    json["densityCurve"]["baseDensity"] = densityCurve.baseDensity;
    json["densityCurve"]["edgeMultiplier"] = densityCurve.edgeMultiplier;
    json["densityCurve"]["cornerMultiplier"] = densityCurve.cornerMultiplier;
    json["densityCurve"]["centerMultiplier"] = densityCurve.centerMultiplier;
    json["densityCurve"]["flowMultiplier"] = densityCurve.flowMultiplier;
    
    json["symmetryPreference"] = symmetryPreference;
    json["chaosTolerance"] = chaosTolerance;
    json["clusteringThreshold"] = clusteringThreshold;
    json["microDetailLevel"] = microDetailLevel;
    
    json["edgeEmphasis"] = edgeEmphasis;
    json["flowFollowing"] = flowFollowing;
    json["symmetryMirroring"] = symmetryMirroring;
    json["antiClutterMode"] = antiClutterMode;
    
    matjson::Value decorationPoolJson;
    for (const auto& obj : decorationPool) {
        matjson::Value objJson;
        objJson["objectID"] = obj.objectID;
        objJson["weight"] = obj.weight;
        objJson["category"] = obj.category;
        objJson["requiresGlow"] = obj.requiresGlow;
        objJson["isDetail"] = obj.isDetail;
        decorationPoolJson.push_back(objJson);
    }
    json["decorationPool"] = decorationPoolJson;
    
    matjson::Value styleWeightsJson;
    for (const auto& pair : styleWeights) {
        styleWeightsJson[pair.first] = pair.second;
    }
    json["styleWeights"] = styleWeightsJson;
    
    return json;
}

AIPreset AIPreset::fromJson(const matjson::Value& json) {
    AIPreset preset;
    
    preset.id = json["id"].asString();
    preset.name = json["name"].asString();
    preset.description = json["description"].asString();
    preset.styleBias = styleBiasFromString(json["styleBias"].asString());
    
    if (json.contains("densityCurve")) {
        auto dc = json["densityCurve"];
        preset.densityCurve.baseDensity = dc["baseDensity"].asDouble();
        preset.densityCurve.edgeMultiplier = dc["edgeMultiplier"].asDouble();
        preset.densityCurve.cornerMultiplier = dc["cornerMultiplier"].asDouble();
        preset.densityCurve.centerMultiplier = dc["centerMultiplier"].asDouble();
        preset.densityCurve.flowMultiplier = dc["flowMultiplier"].asDouble();
    }
    
    preset.symmetryPreference = json["symmetryPreference"].asDouble();
    preset.chaosTolerance = json["chaosTolerance"].asDouble();
    preset.clusteringThreshold = json["clusteringThreshold"].asDouble();
    preset.microDetailLevel = json["microDetailLevel"].asDouble();
    
    preset.edgeEmphasis = json["edgeEmphasis"].asBool();
    preset.flowFollowing = json["flowFollowing"].asBool();
    preset.symmetryMirroring = json["symmetryMirroring"].asBool();
    preset.antiClutterMode = json["antiClutterMode"].asBool();
    
    if (json.contains("decorationPool")) {
        for (const auto& objJson : json["decorationPool"].asArray()) {
            DecorationObject obj;
            obj.objectID = objJson["objectID"].asInt();
            obj.weight = objJson["weight"].asDouble();
            obj.category = objJson["category"].asString();
            obj.requiresGlow = objJson["requiresGlow"].asBool();
            obj.isDetail = objJson["isDetail"].asBool();
            preset.decorationPool.push_back(obj);
        }
    }
    
    if (json.contains("styleWeights")) {
        for (const auto& pair : json["styleWeights"].asObject()) {
            preset.styleWeights[pair.first] = pair.second.asDouble();
        }
    }
    
    return preset;
}

std::string AIPreset::styleBiasToString(StyleBias bias) {
    switch (bias) {
        case StyleBias::CleanModern: return "CleanModern";
        case StyleBias::NeonGlow: return "NeonGlow";
        case StyleBias::DemonExtreme: return "DemonExtreme";
        case StyleBias::RetroPixel: return "RetroPixel";
        case StyleBias::Architectural: return "Architectural";
        default: return "CleanModern";
    }
}

StyleBias AIPreset::styleBiasFromString(const std::string& str) {
    if (str == "CleanModern") return StyleBias::CleanModern;
    if (str == "NeonGlow") return StyleBias::NeonGlow;
    if (str == "DemonExtreme") return StyleBias::DemonExtreme;
    if (str == "RetroPixel") return StyleBias::RetroPixel;
    if (str == "Architectural") return StyleBias::Architectural;
    return StyleBias::CleanModern;
}

}
