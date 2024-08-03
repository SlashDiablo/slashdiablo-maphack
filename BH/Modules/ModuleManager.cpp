#include "ModuleManager.h"
#include "Module.h"
#include "../D2Helpers.h"
#include "../BH.h"
#include <algorithm>
#include <iterator>

ModuleManager::ModuleManager() {

}

ModuleManager::~ModuleManager() {
	for (auto it = moduleList.begin(); it != moduleList.end(); ++it) {
		Module* module = (*it).second;
		delete module;
	}
	moduleList.clear();
}

void ModuleManager::FixName(std::string& name)
{
	std::transform(name.begin(), name.end(), name.begin(), tolower);
	std::replace(name.begin(), name.end(), ' ', '-');
}

void ModuleManager::Add(Module* module) {
	// Add to list of modules
	std::string name = module->GetName();
	FixName(name);
	moduleList[name] = module;
}

Module* ModuleManager::Get(string name) {
	// Get a pointer to a module
	if (moduleList.count(name) > 0) {
		return moduleList[name];
	}
	return NULL;
}

void ModuleManager::Remove(Module* module) {
	// Remove module from list
	std::string name = module->GetName();
	FixName(name);
	moduleList.erase(name);

	delete module;
}

void ModuleManager::LoadModules() {
	for (map<string, Module*>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
		(*it).second->Load();
	}
}

void ModuleManager::UnloadModules() {
	for (map<string, Module*>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
		(*it).second->Unload();
	}
}

void ModuleManager::ReloadConfig() {
	for (map<string, Module*>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
		(*it).second->LoadConfig();
	}
}

void ModuleManager::MpqLoaded() {
	for (map<string, Module*>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
		(*it).second->MpqLoaded();
	}
}

bool ModuleManager::OnUserInput(wchar_t* module, wchar_t* msg, bool fromGame) {
	bool block = false;
	std::string name;
	std::wstring modname(module);
	name.assign(modname.begin(), modname.end());
	transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name.compare("reload") == 0)
	{
		ReloadConfig();
		Print("ÿc4BH:ÿc0 Successfully reloaded configuration.");
		return true;
	}

	if (name.compare("save") == 0) {
		BH::config->Write();
		Print("ÿc4BH:ÿc0 Successfully saved configuration.");
	}

	for (map<string, Module*>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
		if (name.compare((*it).first) == 0) {
			it->second->OnUserInput(msg, fromGame, &block);
		}
	}
	return block;
}

void ModuleManager::OnLoop() {
	for (auto& module : moduleList) {
		module.second->OnLoop();
	}
}

void ModuleManager::OnGameJoin() {
	for (auto& module : moduleList) {
		module.second->OnGameJoin();
	}
}

void ModuleManager::OnGameExit() {
	for (auto& module : moduleList) {
		module.second->OnGameExit();
	}
}

void ModuleManager::OnDraw() {
	for (auto& module : moduleList) {
		module.second->OnDraw();
	}
}

void ModuleManager::OnAutomapDraw() {
	for (auto& module : moduleList) {
		module.second->OnAutomapDraw();
	}
}

void ModuleManager::OnOOGDraw() {
	for (auto& module : moduleList) {
		module.second->OnOOGDraw();
	}
}

void ModuleManager::OnLeftClick(bool up, unsigned int x, unsigned int y, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnLeftClick(up, x, y, block);
	}
}

void ModuleManager::OnRightClick(bool up, unsigned int x, unsigned int y, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnRightClick(up, x, y, block);
	}
}

void ModuleManager::OnKey(bool up, BYTE key, LPARAM lParam, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnKey(up, key, lParam, block);
	}
}

void ModuleManager::OnChatPacketRecv(BYTE* packet, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnChatPacketRecv(packet, block);
	}
}

void ModuleManager::OnRealmPacketRecv(BYTE* packet, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnRealmPacketRecv(packet, block);
	}
}

void ModuleManager::OnGamePacketRecv(BYTE* packet, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnGamePacketRecv(packet, block);
	}
}

void ModuleManager::OnChatMsg(const char* user, const char* msg, bool fromGame, bool* block) {
	for (auto& module : moduleList) {
		module.second->OnChatMsg(user, msg, fromGame, block);
	}
}
