#ifndef _DEALERSHIP_H
#define _DEALERSHIP_H

#include "AvlTree.h"

struct SaleKey {
	int sales_amount, id;
	
	SaleKey() : sales_amount(0), id(-1) {};
	SaleKey(int sales, int id): sales_amount(sales), id(id) {}
	bool operator<(const SaleKey& key);
	bool operator>(const SaleKey& key);
};

class Dealership {
	AvlTree<int, int> car_types;		//Key = id, Data = sale_amount.
	AvlTree<int, SaleKey> sales_tree;

public:
	Dealership() = default;
	~Dealership() = default;
	Dealership(const Dealership& d) = default;

	void sellCarType(int type_id, int amount);
	bool findCarType(int type_id);
	int getIthSoldCarType(int i);
	int getCarsAmount();

	Dealership operator+(const Dealership& d);
};




/*----------------------------------------------------------------

						Helper Functions

-----------------------------------------------------------------*/


//Merges the given keys and data arrays in O(len1 + len2) time and space.
template<class T, class S>
static void mergeArrays(T* data1, S* keys1, T* data2, S* keys2, int len1, int len2, T** new_data, S** new_keys)
{
	*new_data = new T[len1 + len2];
	*new_keys = new S[len1 + len2];
	int i = 0, j = 0, k = 0;
	while (i < len1 && j < len2) {
		if (keys1[i] > keys2[j]) {
			(*new_keys)[k] = keys2[j];
			(*new_data)[k++] = data2[j++];
		}
		else {
			(*new_keys)[k] = keys1[i];
			(*new_data)[k++] = data1[i++];
		}
	}

	for (; i < len1; i++) {
		(*new_keys)[k] = keys1[i];
		(*new_data)[k++] = data1[i];
	
	}
	for (; j < len2; j++) {
		(*new_keys)[k] = keys2[j];
		(*new_data)[k++] = data2[j];
	}
}


//converts an avl tree to a sorted array in O(n) time and space
template<class T, class S>
static void avlTreeToArrays(const AvlTree<T, S>* tr, T** data_arr, S** key_arr)
{
	const TreeNode<T, S>* iter = tr->getRoot();
	if (iter == nullptr) {
		*data_arr = nullptr;
		*key_arr = nullptr;
		return;
	}

	int index = 0;
	*data_arr = new T[iter->size];  //O(m) time + space
	*key_arr = new S[iter->size];   //O(m) time + space

	iter = tr->getMinNode();	   //O(log(m)
	while (iter != nullptr) {
		(*data_arr)[index] = iter->data;
		(*key_arr)[index++] = iter->key;
		iter = tr->getInOrderNext(iter);
	}
}


//Converts 2 avl trees to a merged sorted array in O(n+m) time and space
template<class T, class S>
static AvlTree<T, S> uniteTrees(const AvlTree<T, S>* tr1, const AvlTree<T, S>* tr2)
{
	T* data1 = nullptr, *data2 = nullptr, *new_data = nullptr;
	S* keys1 = nullptr, *keys2 = nullptr, *new_keys = nullptr;
	avlTreeToArrays(tr1, &data1, &keys1);
	avlTreeToArrays(tr2, &data2, &keys2);

	const TreeNode<T, S>* root1 = tr1->getRoot(), *root2 = tr2->getRoot();
	int len1 = (root1 == nullptr ? 0 : root1->size), len2 = (root2 == nullptr ? 0 : root2->size);
	mergeArrays(data1, keys1, data2, keys2, len1, len2, &new_data, &new_keys);

	delete[] data1;
	delete[] data2;
	delete[] keys1;
	delete[] keys2;

	AvlTree<T, S> temp;
	temp.arraysToAvlTree(new_data, new_keys, len1 + len2);

	delete[] new_data;
	delete[] new_keys;

	return temp;
}


#endif
