#include "Dealership.h"


bool SaleKey::operator<(const SaleKey& key)
{
	if (sales_amount == key.sales_amount) {
		return id < key.id;
	}
	else {
		return sales_amount < key.sales_amount;
	}
}

bool SaleKey::operator>(const SaleKey& key)
{
	if (sales_amount == key.sales_amount) {
		return id > key.id;
	}
	else {
		return sales_amount > key.sales_amount;
	}
}


void Dealership::sellCarType(int type_id, int amount)
{
	TreeNode<int, int>* node = car_types.findNode(type_id);
	if (node == nullptr) {
		car_types.insert(type_id, 0);
		node = car_types.findNode(type_id);
	}

	int sale_amount = node->data;
	node->data = sale_amount + amount;

	sales_tree.remove(SaleKey(sale_amount, type_id));
	sales_tree.insert(SaleKey(sale_amount + amount, type_id), type_id);
}


bool Dealership::findCarType(int type_id)
{
	TreeNode<int, int>* ptr = car_types.findNode(type_id);
	return (ptr == nullptr);
}


int Dealership::getIthSoldCarType(int i)
{
	return sales_tree.getIthNode(i)->data;
}


int Dealership::getCarsAmount()
{
	TreeNode<int,int>* ptr = car_types.getRoot();
	return (ptr == nullptr) ? 0 : ptr->size;
}


Dealership Dealership::operator+(const Dealership& d)
{
	Dealership res;
	res.car_types = uniteTrees(&car_types, &d.car_types);		//AvlTree copy c'tor
	res.sales_tree = uniteTrees(&sales_tree, &d.sales_tree);    //AvlTree copy c'tor

	return res;
}