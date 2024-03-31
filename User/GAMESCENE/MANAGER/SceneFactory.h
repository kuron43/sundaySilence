#pragma once
#include "ISceneFactory.h"
#include "SceneIntegrate.h"
class SceneFactory :
    public ISceneFactory
{
private:

	 Iscene* CleateScene(const std::string& sceneName) override;
};

