#include "SpellStealPlugin.h"

namespace SpellStealPluginNamespace {
	static void setCastingPerk(RE::StaticFunctionTag* base, RE::SpellItem* spell, RE::BGSPerk* perk)
	{
		spell->data.castingPerk = perk;
	}

	static void setCastingTime(RE::StaticFunctionTag* base, RE::SpellItem* spell, float time)
	{
		spell->data.castDuration = time;

	}

	static void setCost(RE::StaticFunctionTag* base, RE::SpellItem* spell, int32_t cost)
	{
		spell->data.costOverride = cost;
	}

	static void setFlags(RE::StaticFunctionTag* base, RE::SpellItem* spell, uint32_t flag)
	{
		spell->formFlags = flag;
	}

	static void copySpell(RE::StaticFunctionTag* base, RE::SpellItem* toCopy, RE::SpellItem* target) {
		target->equipSlot = toCopy->equipSlot;
		target->menuDispObject = toCopy->menuDispObject;
		target->descriptionText = toCopy->descriptionText;
		target->data = toCopy->data;
		target->effects = toCopy->effects;
		target->formFlags = toCopy->formFlags;
		target->fullName = toCopy->fullName;
		target->keywords = toCopy->keywords;
		target->hostileCount = toCopy->hostileCount;
		target->boundData = toCopy->boundData;
		target->boundData = toCopy->boundData;
		target->pad14 = toCopy->pad14;
		target->fileOffset = toCopy->fileOffset;
		target->formID = toCopy->formID;
		target->sourceFiles = toCopy->sourceFiles;
		target->preloadCount = toCopy->preloadCount;
		target->pad1B = toCopy->pad1B;
		target->pad1C = toCopy->pad1C;
		target->pad2C = toCopy->pad2C;
		target->pad74 = toCopy->pad74;
		target->pad84 = toCopy->pad84;
		target->formType = toCopy->formType;
		target->data.castingType = toCopy->data.castingType;
		target->data.costOverride = toCopy->data.costOverride;
		target->data.range = toCopy->data.range;
		target->data.chargeTime = toCopy->data.chargeTime;
		target->data.castingPerk = toCopy->data.castingPerk;
		target->data.flags = toCopy->data.flags;
		target->data.delivery = toCopy->data.delivery;
		target->data.spellType = toCopy->data.spellType;
		target->data.castDuration = toCopy->data.castDuration;
	}

	static void setType(RE::StaticFunctionTag* base, RE::SpellItem* spell, RE::MagicSystem::SpellType type)
	{
		spell->data.spellType = type;
	}

	UINT32 getFlags(RE::StaticFunctionTag* base, RE::SpellItem* spell) {
		return spell->GetFormFlags();
	}

	bool RegisterFuncs(RE::BSScript::IVirtualMachine* registry)
	{
		registry->RegisterFunction("getFlags", "SpellStealPluginScript", SpellStealPluginNamespace::getFlags, registry);
		registry->RegisterFunction("setCastingPerk", "SpellStealPluginScript", SpellStealPluginNamespace::setCastingPerk, registry);
		registry->RegisterFunction("setCastingTime", "SpellStealPluginScript", SpellStealPluginNamespace::setCastingTime, registry);
		registry->RegisterFunction("copySpell", "SpellStealPluginScript", SpellStealPluginNamespace::copySpell, registry);
		registry->RegisterFunction("setType", "SpellStealPluginScript", SpellStealPluginNamespace::setType, registry);
		registry->RegisterFunction("setCost", "SpellStealPluginScript", SpellStealPluginNamespace::setCost, registry);
		registry->RegisterFunction("setFlags", "SpellStealPluginScript", SpellStealPluginNamespace::setFlags, registry);

		return true;
	}
}
