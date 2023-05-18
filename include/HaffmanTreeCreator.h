#pragma once
#include <queue>
#include <list>
#include <string>
#include <vector>
#include <iostream>

class HaffmanTreeCreator {
public:
	struct HaffmanNode {
		std::string name;
		HaffmanNode* left;
		HaffmanNode* right;

		HaffmanNode() {
			left = right = nullptr;
		}

		HaffmanNode(const std::string& name_, HaffmanNode* left_ = nullptr, HaffmanNode* right_ = nullptr) :
			name(name_),
			left(left_),
			right(right_)
		{
		}
	};



	class HeapComparator {
	public:
		bool operator()(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) {
			return p1.second > p2.second;
		}
	};

	std::vector<std::vector<bool>> createCodes(const std::vector<int> frequency) {
		HeapComparator hp;
		std::vector<std::vector<bool>> result(256);

		std::priority_queue<std::pair<std::string, int>,
			std::vector<std::pair<std::string, int>>, HeapComparator> pq(hp);
		
		for (int i = 0; i < frequency.size(); i++) {
			if (frequency[i]) {
				pq.push(std::make_pair(std::string(1,(char)i), frequency[i]));
			}
		}

		if (!pq.size()) {
			return result;
		}
		else if (pq.size() == 1) {
			result[pq.top().first[0]] = std::vector<bool>({ 0 });
			return result;
		}
		
		std::pair<std::string, int> min1, min2;
		
		while (pq.size() >= 2) {
			min1 = pq.top();
			pq.pop();
			min2 = pq.top();
			pq.pop();
			pq.push(std::make_pair(min1.first + min2.first, min1.second + min2.second));
			addUnit(min1.first, min2.first);
		}

		std::vector<std::pair<std::vector<bool>, unsigned char>> codes;

		fillCodes(codes, std::vector<bool>(), roots.front()->left, false);
		fillCodes(codes, std::vector<bool>(), roots.front()->right, true);

		for (auto code : codes) {
			result[code.second] = code.first;
		}

		return result;
	}

private:
	std::list<HaffmanNode*> roots;

	void fillCodes(std::vector<std::pair<std::vector<bool>, unsigned char>>& codes, std::vector<bool> current_code, HaffmanNode* n, bool direction){
		if (!n) return;
		current_code.push_back(direction);
		if (!n->left || !n->right) {
			codes.push_back(std::make_pair(current_code, n->name[0]));
			return;
		}
		fillCodes(codes, current_code, n->left, false);
		fillCodes(codes, current_code, n->right, true);
	}

	void addUnit(const std::string& lpart, const std::string& rpart) {
		HaffmanNode* newNode = new HaffmanNode(lpart + rpart);

		auto root = roots.begin();
		while (root != roots.end()){
			if (newNode->left && newNode->right) {
				break;
			}
			if (lpart == (*root)->name) {
				newNode->left = *root;
				root = roots.erase(root);
			}
			else if (rpart == (*root)->name) {
				newNode->right = *root;
				root = roots.erase(root);
			}
			else {
				++root;
			}
		}
		if (!newNode->left) {
			newNode->left = new HaffmanNode(lpart);
		}
		if (!newNode->right) {
			newNode->right = new HaffmanNode(rpart);
		}

		roots.push_back(newNode);
	}
};