#ifndef AUCTIONHOUSEMETHODS_H
#define AUCTIONHOUSEMETHODS_H

#include "AuctionHouseMgr.h"
#include "Player.h"
#include "WorldSession.h"

#define auctionMgr AuctionHouseMgr::instance()

namespace LuaAuctionHouse
{
    int GetAuctionCount(lua_State* L,  AuctionHouseMgr* ahman)
    {
        int auctionHouseId = Eluna::CHECKVAL<int>(L, 2);
        Eluna::Push(L, auctionHouseId);
        return 0;
    }

    int AddItem(lua_State* L, AuctionHouseMgr* ahman)
    {
        // int auctionHouseId, Item* item, Player* player

        int auctionHouseId = Eluna::CHECKVAL<int>(L, 2);
        Item* item = Eluna::CHECKOBJ<Item>(L, 3);
        Player* player = Eluna::CHECKOBJ<Player>(L, 4);


        auto trans = CharacterDatabase.BeginTransaction();

        AuctionEntry* auctionEntry = new AuctionEntry();
        auctionEntry->Id = sObjectMgr->GenerateAuctionID();
        auctionEntry->houseId = 6;
        auctionEntry->item_guid = item->GetGUID();
        auctionEntry->item_template = item->GetEntry();
        auctionEntry->itemCount = 1;
        auctionEntry->owner = player->GetGUID();
        auctionEntry->startbid = 9999;
        auctionEntry->buyout = 10000;
        auctionEntry->bid = 0;
        auctionEntry->deposit = 1000;
        auctionEntry->expire_time = (time_t) 86400 + time(NULL);

        item->SaveToDB(trans);
        item->RemoveFromUpdateQueueOf(player);
        auctionMgr->AddAItem(item);
        auctionEntry->SaveToDB(trans);
        CharacterDatabase.CommitTransaction(trans);

        Eluna::Push(L, auctionEntry);

        return 1;
    }
}

#endif