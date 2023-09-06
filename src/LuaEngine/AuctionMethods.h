
#ifndef AUCTIONMETHODS_H
#define AUCTIONMETHODS_H

namespace LuaAuction
{
    int GetAuctionCount(lua_State* L, ElunaAuctionHouse* ah)
    {
        Eluna::Push(L, 100);
        return 1;
    }
}

#endif