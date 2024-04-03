#pragma once
#pragma warning(push)
#pragma warning(disable: 4514)

#include<string>
#pragma warning(pop)

class IScene;

/// <summary>
/// 仮想シーン工場
/// </summary>
class ISceneFactory
{
public:
	virtual ~ISceneFactory() = default;

	virtual IScene* CleateScene(const std::string& sceneName) = 0;
};

