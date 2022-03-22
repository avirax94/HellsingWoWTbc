#include "AI/ScriptDevAI/include/sc_common.h"

struct npc_tranfi: public ScriptedAI
{
    npc_tranfi(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }
};


bool GossipHello_Npc_Tranfi(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetSession()->IsPremium() || pPlayer->IsGameMaster())
    {
		pPlayer->ADD_GOSSIP_ITEM(0, "Morph", GOSSIP_SENDER_MAIN, 1);
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
    }
    else
        pCreature->MonsterSay("No eres vip. puedes contactar con un administrador", pPlayer->GetObjectGuid());

    return true;
}

bool GossipSelect_Npc_Tranfi(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{

    return true;
}

 void AddSC_npc_tranfi()
 {
	 Script* pNewScript = new Script;
	 pNewScript->Name = "npc_tranfi";
	 pNewScript->pGossipHello = &GossipHello_Npc_Tranfi;
	 pNewScript->pGossipSelect = &GossipSelect_Npc_Tranfi;
	 pNewScript->RegisterSelf(false);
 } 