#include "Module.h"
#include "../BH.h"

Module::Module(string name) : name(name), active(false) {
	BH::moduleManager->Add(this);
}

Module::~Module() {
	//Unload();
	//BH::moduleManager->Remove(this);
}

void Module::Load() {
	if (IsActive())
		return;

	// Hook up all the events

	active = true;
	OnLoad();
}

void Module::Unload() {
	if (!IsActive())
		return;

	active = false;
	OnUnload();
}