#pragma once

#include "ModuleManager.h"

enum class NeulogError : uint32
{
	None,
	WriteFailed,
	ReadFailed,
	InvalidPrefix,
	InvalidResponse,
	OpenFailed,
	ThreadStartFailed,
};

class INeulogSensor
{
public:
	virtual ~INeulogSensor() {}

	virtual NeulogError Start() = 0;
	virtual float GetValue() = 0;
};

using INeulogSensorPtr = TUniquePtr<INeulogSensor>;

class INeulogGSRModule : public IModuleInterface
{
public:
	virtual INeulogSensorPtr OpenSensorOnPort(const FString& PortName) = 0;
	virtual INeulogSensorPtr FindSensor() = 0;

	static INeulogGSRModule& Get()
	{
		return FModuleManager::LoadModuleChecked<INeulogGSRModule>("NeulogGSR");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("NeulogGSR");
	}
};