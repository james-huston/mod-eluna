
#include "ElunaAuctionHouse.h"
#include "AuctionHouseMgr.h"

extern AuctionHouseMgr* sAuctionManager;

ElunaAuctionHouse::ElunaAuctionHouse() {
    manager = sAuctionManager;
}

