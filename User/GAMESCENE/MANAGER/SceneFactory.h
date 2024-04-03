#pragma once
#include "ISceneFactory.h"
#include "SceneIntegrate.h"
class SceneFactory :
    public ISceneFactory
{
public:
	 IScene* CleateScene(const std::string& sceneName) override;
private:

};

