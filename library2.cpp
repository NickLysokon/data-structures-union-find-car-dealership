#include "library2.h"
#include "CarDealershipManager.h"


void* Init()
{
	CarDealershipManager* DS = new CarDealershipManager();
	return ((void*)DS);
}

StatusType AddAgency(void* DS)
{
	if (DS == nullptr) {
		return INVALID_INPUT;
	}

	return ((CarDealershipManager*)DS)->AddAgency();
}

StatusType SellCar(void* DS, int agencyID, int typeID, int k)
{
	if (DS == nullptr || agencyID < 0 || k <= 0) {
		return INVALID_INPUT;
	}

	return ((CarDealershipManager*)DS)->SellCar(agencyID, typeID, k);
}

StatusType UniteAgencies(void* DS, int agencyID1, int agencyID2)
{
	if (DS == nullptr || agencyID1 < 0 || agencyID2 < 0) {
		return INVALID_INPUT;
	}

	return ((CarDealershipManager*)DS)->UniteAgencies(agencyID1, agencyID2);
}

StatusType GetIthSoldType(void* DS, int agencyID, int i, int* res)
{
	if (DS == nullptr || agencyID < 0 || i < 0 || res == nullptr) {
		return INVALID_INPUT;
	}

	return ((CarDealershipManager*)DS)->GetIthSoldType(agencyID, i, res);
}

void Quit(void** DS)
{
	if (DS == nullptr || *DS == nullptr) return;

	delete  ((CarDealershipManager*)*DS);
	*DS = nullptr;
}