#include "AI/ScriptDevAI/ScriptDevAIMgr.h"
#include "AI/ScriptDevAI/include/sc_common.h"

bool ItemUse_item_icerune(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{

    uint32 sSpell = 18282; //Icerune Visual Spell when used
    if (pPlayer->IsInCombat())
    {
        pPlayer->GetSession()->SendNotification("You are in combat.");
    }

    else if (pPlayer->IsMoving())
    {
        pPlayer->GetSession()->SendNotification("You can not do that while moving.");
    }
    if (pPlayer->IsFlying() || pPlayer->IsTaxiFlying() || pPlayer->IsMounted())
    {
        pPlayer->GetSession()->SendNotification("You are mounted and cannot switch spec at this time.");
        return false;
    }
    if (pPlayer->GetSpecsCount() < MAX_TALENT_SPECS)
    {
        pPlayer->GetSession()->SendNotification("You must unlock the dual talent specialization feature first.");
        return false;
    }
    if (pPlayer->IsDead())
    {
        pPlayer->GetSession()->SendNotification("You are dead and cannot switch spec at this time.");
        return false;
    }
    if (pPlayer->getLevel() < 10)
    {
        pPlayer->GetSession()->SendNotification("Current level is less than ten - you cannot switch spec at this time.");
        return false;
    }
    /* else if (pPlayer->GetClosestCreatureWithEntry(pPlayer, 100002, 40) || pPlayer->GetClosestCreatureWithEntry(pPlayer, 100000, 8))
    {
      pPlayer->GetSession()->SendNotification("Flaming Legion Vortex can not be summoned right now. Another Vortex is nearby.");
    }*/
    else
    {
        float x, y, z, o = pPlayer->GetOrientation();

        if (o >= 3.141592)
            o = o - 3.141592;
        else
            o = o + 3.141592;
        Creature* pCreature = pPlayer->SummonCreature(100002, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ() + 2, 0, TEMPSPAWN_TIMED_DESPAWN, 120000);
        pCreature->CastSpell(pCreature, 40162, TRIGGERED_OLD_TRIGGERED);
        return false;
    }
    return true;
}

void AddSC_summon()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "summon";
    pNewScript->pItemUse = &ItemUse_item_icerune;
    pNewScript->RegisterSelf(false);
}