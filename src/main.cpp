#include <ShlObj.h>  // CSIDL_MYDOCUMENTS
#include <PCH.h>
#include "SpellStealPlugin.h"
#include <stddef.h>

using namespace RE::BSScript;
using namespace SpellStealPluginNamespace;
using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;

namespace
{
	void InitializeLog()
	{
#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
		auto path = logger::log_directory();
		if (!path) {
			util::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format(FMT_STRING("{}.log"), Plugin::NAME);
		auto       sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

#ifndef NDEBUG
		const auto level = spdlog::level::trace;
#else
		const auto level = spdlog::level::info;
#endif

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
	}

	void InitializePapyrus()
	{
		log::trace("Initializing Papyrus binding...");
		if (GetPapyrusInterface()->Register(SpellStealPluginNamespace::RegisterFuncs)) {
			log::debug("Papyrus functions bound.");
		} else {
			stl::report_and_fail("Failure to register Papyrus bindings.");
		}
	}

	void MessageHandler()
	{
		if (!GetMessagingInterface()->RegisterListener([](MessagingInterface::Message* message) {
				switch (message->type) {
				// Skyrim lifecycle events.
				case MessagingInterface::kPostLoad:  // Called after all plugins have finished running SKSEPlugin_Load.
					// It is now safe to do multithreaded operations, or operations against other plugins.
				case MessagingInterface::kPostPostLoad:  // Called after all kPostLoad message handlers have run.
				case MessagingInterface::kInputLoaded:   // Called when all game data has been found.
					break;
				case MessagingInterface::kDataLoaded:  // All ESM/ESL/ESP plugins have loaded, main menu is now active.
					// It is now safe to access form data.
					
					break;

				// Skyrim game events.
				case MessagingInterface::kNewGame:      // Player starts a new game from main menu.
				case MessagingInterface::kPreLoadGame:  // Player selected a game to load, but it hasn't loaded yet.
					// Data will be the name of the loaded save.
				case MessagingInterface::kPostLoadGame:  // Player's selected save game has finished loading.
					// Data will be a boolean indicating whether the load was successful.
				case MessagingInterface::kSaveGame:  // The player has saved a game.
					// Data will be the save name.
				case MessagingInterface::kDeleteGame:  // The player deleted a saved game from within the load menu.
					break;
				}
			})) {
			stl::report_and_fail("Unable to register message listener.");
		}
	}
}


SKSEPluginLoad(const LoadInterface* skse)
{
	InitializeLog();

	auto* plugin = PluginDeclaration::GetSingleton();
	auto  version = plugin->GetVersion();
	log::info("{} {} is loading...", plugin->GetName(), version);

	Init(skse);
	MessageHandler();
	InitializePapyrus();

	log::info("{} has finished loading.", plugin->GetName());
	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Plugin::NAME.data();
	a_info->version = Plugin::VERSION[0];

	if (a_skse->IsEditor()) {
		logger::critical(FMT_STRING("Loaded in editor, marking as incompatible"));
		return false;
	}

	return true;
}

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;

	v.PluginVersion(Plugin::VERSION);
	v.PluginName(Plugin::NAME);

	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST_AE, SKSE::RUNTIME_LATEST_VR });
	v.HasNoStructUse(true);

	return v;
}();


