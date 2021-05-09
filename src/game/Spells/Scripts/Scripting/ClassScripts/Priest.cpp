/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Spells/Scripts/SpellScript.h"
#include "Spells/SpellAuras.h"

struct SpiritOfRedemptionHeal : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx == EFFECT_INDEX_0)
            spell->SetDamage(spell->GetCaster()->GetMaxHealth());
    }
};

enum
{
    SPELL_PLAYER_CONSUME_MAGIC = 32676,
};

struct ConsumeMagic : public SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool strict) const override
    {
        if (strict)
        {
            auto holderMap = spell->GetCaster()->GetSpellAuraHolderMap();
            for (auto holderPair : holderMap)
            {
                if (holderPair.second->GetSpellProto())
                {
                    if (holderPair.second->GetSpellProto()->SpellFamilyName == SPELLFAMILY_PRIEST)
                    {
                        if (holderPair.second->IsPositive() && !holderPair.second->IsPassive())
                        {
                            spell->SetScriptValue(holderPair.second->GetId());
                            return SPELL_CAST_OK;
                        }
                    }
                }
            }

            return SPELL_FAILED_NOTHING_TO_DISPEL;
        }
        else
            return SPELL_CAST_OK;
    }

    void OnEffectExecute(Spell* spell, SpellEffectIndex /*effIdx*/) const override
    {
        spell->GetCaster()->RemoveAurasDueToSpell(spell->GetScriptValue());
    }
};

struct PowerInfusion : public SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool/* strict*/) const override
    {
        // Patch 1.10.2 (2006-05-02):
        // Power Infusion: This aura will no longer stack with Arcane Power. If you attempt to cast it on someone with Arcane Power, the spell will fail.
        if (Unit* target = spell->m_targets.getUnitTarget())
            if (target->GetAuraCount(12042))
                return SPELL_FAILED_AURA_BOUNCED;

        return SPELL_CAST_OK;
    }
};

struct ShadowWordDeath : public SpellScript
{
    void OnHit(Spell* spell, SpellMissInfo /*missInfo*/) const override
    {
        int32 swdDamage = spell->GetTotalTargetDamage();
        spell->GetCaster()->CastCustomSpell(nullptr, 32409, &swdDamage, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
    }
};

struct Blackout : public AuraScript
{
    bool OnCheckProc(Aura* /*aura*/, ProcExecutionData& data) const override
    {
        if (!data.damage || data.isHeal)
            return false;
        return true;
    }
};

enum
{
    MANA_LEECH_PASSIVE = 28305,
};

struct Shadowfiend : public SpellScript
{
    void OnSummon(Spell* spell, Creature* summon) const override
    {
        summon->CastSpell(summon, MANA_LEECH_PASSIVE, TRIGGERED_OLD_TRIGGERED);
        summon->AI()->AttackStart(spell->m_targets.getUnitTarget());
    }
};

void LoadPriestScripts()
{
    RegisterSpellScript<ConsumeMagic>("spell_consume_magic");
    RegisterSpellScript<PowerInfusion>("spell_power_infusion");
    RegisterSpellScript<ShadowWordDeath>("spell_shadow_word_death");
    RegisterSpellScript<SpiritOfRedemptionHeal>("spell_spirit_of_redemption_heal");
    RegisterAuraScript<Blackout>("spell_blackout");
    RegisterSpellScript<Shadowfiend>("spell_shadowfiend");
}
