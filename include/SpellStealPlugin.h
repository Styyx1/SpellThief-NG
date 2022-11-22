#pragma once



namespace SpellStealPluginNamespace {
	static void setCastingPerk(RE::StaticFunctionTag* base, RE::SpellItem* spell, RE::BGSPerk* perk);
	static void  setCastingTime(RE::StaticFunctionTag* base, RE::SpellItem* spell, float time);
	static void  copySpell(RE::StaticFunctionTag* base, RE::SpellItem* toCopy, RE::SpellItem* target);
	static void   setType(RE::StaticFunctionTag* base, RE::SpellItem* spell, RE::MagicSystem::SpellType type);
	static void   setFlags(RE::StaticFunctionTag* base, RE::SpellItem* spell, uint32_t flag);
	static void    setCost(RE::StaticFunctionTag* base, RE::SpellItem* spell, int32_t cost);
	UINT32 getFlags(RE::StaticFunctionTag* base, RE::SpellItem* spell);

	bool RegisterFuncs(RE::BSScript::IVirtualMachine* registry);
}
