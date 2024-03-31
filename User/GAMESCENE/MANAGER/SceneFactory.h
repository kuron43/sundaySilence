#pragma once
#include "ISceneFactory.h"
#include "SceneIntegrate.h"
class SceneFactory :
    public ISceneFactory
{
public:
	 Iscene* CleateScene(const std::string& sceneName) override;
private:

};

