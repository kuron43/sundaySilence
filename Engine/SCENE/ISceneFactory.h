#pragma once
#pragma warning(push)
#pragma warning(disable: 4514)

#include<string>
#pragma warning(pop)

class Iscene;

/// <summary>
/// 仮想シーン工場
/// </summary>
class ISceneFactory
{
public:
	virtual ~ISceneFactory() = default;

	virtual Iscene* CleateScene(const std::string& sceneName) = 0;
};

