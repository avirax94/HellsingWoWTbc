#include "AI/ScriptDevAI/include/sc_common.h"

struct npc_teleport : public ScriptedAI
{
    npc_teleport(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }
};


bool GossipHello_Npc_Teleport(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetSession()->IsPremium() || pPlayer->IsGameMaster())
    {
		pPlayer->ADD_GOSSIP_ITEM(0, "Morph", GOSSIP_SENDER_MAIN, 1);
		pPlayer->ADD_GOSSIP_ITEM(0, "Necesito ayuda", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(0, "equitaciones", GOSSIP_SENDER_MAIN, 3);
		pPlayer->ADD_GOSSIP_ITEM(0, "teleports", GOSSIP_SENDER_MAIN, 4);
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
    }
    else
        pCreature->MonsterSay("No eres vip. puedes contactar con un administrador", pPlayer->GetObjectGuid());

    return true;
}

bool GossipSelect_Npc_Teleport(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == 1)
    {
        pPlayer->SetDisplayId(20681);
        pPlayer->CLOSE_GOSSIP_MENU(); 
    }
    if (uiAction == 2)
    {
        pCreature->MonsterSay("Puedes encontrar ayuda en nuestra web hellsingwow.com", pPlayer->GetObjectGuid());
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == 3)
    {
        pPlayer->learnSpell(33388, false);
        pPlayer->learnSpell(33391, false);
        pPlayer->learnSpell(34090, false);
        pPlayer->learnSpell(34091, false);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == 4)
    {
        pPlayer->ADD_GOSSIP_ITEM(0, "Prof Trainer", GOSSIP_SENDER_MAIN, 20);
        pPlayer->ADD_GOSSIP_ITEM(0, "Prof ", GOSSIP_SENDER_MAIN, 21);
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
    }
    return true;
}

 void AddSC_npc_teleport()
 {
	 Script* pNewScript = new Script;
	 pNewScript->Name = "npc_teleport";
	 pNewScript->pGossipHello = &GossipHello_Npc_Teleport;
	 pNewScript->pGossipSelect = &GossipSelect_Npc_Teleport;
	 pNewScript->RegisterSelf(false);
 }