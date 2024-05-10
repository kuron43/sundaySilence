#pragma once

#include <string>
#include <map>
#include <list>

#include "Model.h"

// 現状仕組み考え中

namespace _Modelmanager {
	class ModelManager
	{
	public:
		static ModelManager& get_instance() {
			static ModelManager instance;
			return instance;
		}
		void AddModel(std::wstring str, Model* model) {
			models.emplace(std::make_pair(str, model));
		}

	private:

		static std::map<std::wstring, Model*> models;
	};
}
