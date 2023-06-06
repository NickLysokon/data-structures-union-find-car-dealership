#ifndef _CAR_DEALERSHIP_MANAGER_WET_2
#define _CAR_DEALERSHIP_MANAGER_WET_2

#include "library2.h"
#include "UnionFind.h"
#include "Dealership.h"


class CarDealershipManager {
	UnionFind<Dealership> dealerships;

public:
    CarDealershipManager() = default;
    StatusType AddAgency();
    StatusType SellCar(int agencyID, int typeID, int k);
    StatusType UniteAgencies(int agencyID1, int agencyID2);
    StatusType GetIthSoldType(int agencyID, int i, int* res);

};


#endif