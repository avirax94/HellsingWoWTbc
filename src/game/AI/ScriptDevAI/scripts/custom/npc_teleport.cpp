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
		pPlayer->ADD_GOSSIP_ITEM(0, "Equitaciones", GOSSIP_SENDER_MAIN, 3);
		pPlayer->ADD_GOSSIP_ITEM(0, "teleports", GOSSIP_SENDER_MAIN, 4);
        pPlayer->ADD_GOSSIP_ITEM(0, "Quitar Morph", GOSSIP_SENDER_MAIN, 20);
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
    }
    else
        pCreature->MonsterWhisper("No eres vip. puedes contactar con un administrador", pPlayer);

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
        pCreature->MonsterWhisper("Puedes encontrar ayuda en nuestra web hellsingwow.com", pPlayer);
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
        pPlayer->ADD_GOSSIP_ITEM(0, "ventormenta", GOSSIP_SENDER_MAIN, 5);
        pPlayer->ADD_GOSSIP_ITEM(0, "Orgrimmar", GOSSIP_SENDER_MAIN, 6);
		pPlayer->ADD_GOSSIP_ITEM(0, "Sharatt", GOSSIP_SENDER_MAIN, 7);
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
    }
	if (uiAction == 5)
	{
		 pPlayer->TeleportTo(0, 1807.07f, 336.105f, 70.3975f, 0.0f);
	}
	if (uiAction == 6)
	{
		 pPlayer->TeleportTo(0, 1807.07f, 336.105f, 70.3975f, 0.0f);
	}
	if (uiAction == 7)
	{
		 pPlayer->TeleportTo(0, 1807.07f, 336.105f, 70.3975f, 0.0f);
	}
    if (uiAction == 20)
    {
        pPlayer->RestoreDisplayId();
        pPlayer->CLOSE_GOSSIP_MENU();
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