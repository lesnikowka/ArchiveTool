#pragma once
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

	std::vector<std::vector<bool>> getCodes() {
		return std::vector<std::vector<bool>>();
	}

private:
	std::list<HaffmanNode*> roots;

	bool isSheet(HaffmanNode* n) {
		return n->right && n->left;
	}
};