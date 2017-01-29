#pragma once

#include "stdafx.h"
#include <exception>

template <typename Resource, typename Identifier>
class ResourceManager {
public:
	ResourceManager();
	void setDirectory(const std::string& path);
	void load(const Identifier& identifier, const std::string& filename);
	Resource& get(const Identifier& identifier);
private:
	std::string directory;
	std::map<Identifier, std::unique_ptr<Resource>> resources_;
};

#include "ResourceManager.inl"