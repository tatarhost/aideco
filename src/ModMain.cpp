#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "ui/AIDecorateLayer.hpp"
#include "presets/AIPresetManager.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    // Initialize preset manager
    auto presetManager = AutoDecoratorAI::AIPresetManager::get();
    presetManager->initialize();
    
    log::info("Auto Decorator AI mod loaded successfully!");
}

class $modify(EditorUI) {
    AIDecorateLayer* m_aiDecorateLayer = nullptr;
    
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) {
            return false;
        }
        
        // Create AI Decorate layer
        m_aiDecorateLayer = AutoDecoratorAI::AIDecorateLayer::create(this);
        if (m_aiDecorateLayer) {
            this->addChild(m_aiDecorateLayer, 1000);
        }
        
        return true;
    }
    
    void destructor() {
        if (m_aiDecorateLayer) {
            m_aiDecorateLayer->removeFromParent();
            m_aiDecorateLayer = nullptr;
        }
        EditorUI::destructor();
    }
};
