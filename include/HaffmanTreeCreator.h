#pragma once
#include <queue>
#include <list>
#include <string>
#include <vector>

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
		bool operator()(const std::pair<unsigned char, int>& p1, const std::pair<unsigned char, int>& p2) {
			return p1.second > p2.second;
		}
	};

	std::vector<std::vector<bool>> createCodes(const std::vector<int> frequency) {
		HeapComparator hp;

		std::priority_queue<std::pair<unsigned char, int>,
			std::vector<std::pair<std::string, int>>, HeapComparator> pq(hp);

		for (int i = 0; i < frequency.size(); i++) {
			pq.push(std::make_pair(std::to_string((unsigned char)i), frequency[i]));
		}

		std::pair<std::string, int> min1, min2;

		while (pq.size() >= 2) {
			min1 = pq.top();
			pq.pop();
			min2 = pq.top();
			pq.pop();
			pq.push(std::make_pair(min1.first + min2.first, min1.second + min2.second));
			addUnit(pq.top().first, min1.first, min2.first);
		}

		std::vector<std::vector<bool>> result(256);
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
		current_code.push_back(direction);
		if (!n->left) {
			codes.push_back(std::make_pair(current_code, n->name[0]));
		}
		fillCodes(codes, current_code, n->left, false);
		fillCodes(codes, current_code, n->right, true);
	}

	void addUnit(const std::string& merged, const std::string& lpart, const std::string& rpart) {
		HaffmanNode* newNode = new HaffmanNode;

		for (auto root = begin(roots); root != end(roots); ++root) {
			if (newNode->left && newNode->right) {
				break;
			}
			if (newNode->left && lpart == (*root)->name) {
				newNode->left = *root;
				root = roots.erase(root);
			}
			else if (newNode->right && rpart == (*root)->name) {
				newNode->right = *root;
				root = roots.erase(root);
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