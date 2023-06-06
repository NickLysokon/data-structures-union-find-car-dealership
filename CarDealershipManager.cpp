#include "CarDealershipManager.h"


//Makes a new set in the UnionFind. the current index is kept inside the UnionFind.
StatusType CarDealershipManager::AddAgency()
{
	try {
		dealerships.makeSet();  //O(1) amortized time & space

		return SUCCESS;
	}
	catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
}


//Finds the dealership's union set and updates the sales tree.
StatusType CarDealershipManager::SellCar(int agencyID, int typeID, int k)
{
	try {
		if (agencyID >= dealerships.getElementCount()) {
			return FAILURE;
		}

		UnionFindNode<Dealership>* agency = dealerships.getElement(agencyID); //O(log*(n)) time (uses find)
		agency->data.sellCarType(typeID, k);								  //O(log(m)) time

		return SUCCESS;
	}
	catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
}


StatusType CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2)
{
	try {
		if (agencyID1 >= dealerships.getElementCount() || 
			agencyID2 >= dealerships.getElementCount()) {
			return FAILURE;
		}

		dealerships.Union(agencyID1, agencyID2);  //O(log*(n) + m1 + m2)

		return SUCCESS;
	}
	catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
}


StatusType CarDealershipManager::GetIthSoldType(int agencyID, int i, int* res)
{
	try {
		if (agencyID >= dealerships.getElementCount()) {
			return FAILURE;
		}

		UnionFindNode<Dealership>* agency = dealerships.getElement(agencyID); //O(log*(n)) time

		if (i >= agency->data.getCarsAmount()) {
			return FAILURE;
		}

		*res = agency->data.getIthSoldCarType(i);	//O(log(m) time

		return SUCCESS;
	}
	catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
}
