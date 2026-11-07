
#include <iostream>
#include <cassert>
#include <algorithm>
#include <climits>
#include <numeric>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;
	RedBlackTree rbt;
	for (int value : {30, 15, 45, 10}) rbt.Insert(value);
	assert(rbt.ToPrefixString() == " B30  B15  R10  B45 ");
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}

void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

template <typename Function>
void ExpectInvalidArgument(Function operation);

void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;
	RedBlackTree rbt;
	ExpectInvalidArgument([&] { rbt.GetMin(); });
	ExpectInvalidArgument([&] { rbt.GetMax(); });
	rbt.Insert(30);
	assert(rbt.GetMin() == 30);
	assert(rbt.GetMax() == 30);
	rbt.Insert(10);
	rbt.Insert(50);
	assert(rbt.GetMin() == 10);
	assert(rbt.GetMax() == 50);

	cout << "PASSED!" << endl << endl;
}

struct Label { char color; int value; };

// Validate red-black invariants through the public traversal methods.
int CheckSubtree(const vector<Label>& nodes, size_t& index,
				 long long low, long long high, bool redParent) {
	if (index == nodes.size() || nodes[index].value <= low || nodes[index].value >= high)
		return 1;
	const Label node = nodes[index++];
	assert(node.color == 'B' || node.color == 'R');
	assert(!(redParent && node.color == 'R'));
	int left = CheckSubtree(nodes, index, low, node.value, node.color == 'R');
	int right = CheckSubtree(nodes, index, node.value, high, node.color == 'R');
	assert(left == right);
	return left + (node.color == 'B');
}

void CheckTree(const RedBlackTree& tree, const set<int>& expected) {
	assert(tree.Size() == expected.size());
	istringstream prefix(tree.ToPrefixString());
	vector<Label> nodes;
	Label label;
	while (prefix >> label.color >> label.value) nodes.push_back(label);
	assert(nodes.size() == expected.size());
	if (!nodes.empty()) assert(nodes.front().color == 'B');
	size_t index = 0;
	CheckSubtree(nodes, index, LLONG_MIN, LLONG_MAX, false);
	assert(index == nodes.size());
	istringstream infix(tree.ToInfixString());
	for (int value : expected) {
		assert(infix >> label.color >> label.value);
		assert(label.value == value);
		assert(tree.Contains(value));
	}
	assert(!(infix >> label.color));
	if (!expected.empty()) {
		assert(tree.GetMin() == *expected.begin());
		assert(tree.GetMax() == *expected.rbegin());
	}
}

template <typename Function>
void ExpectInvalidArgument(Function operation) {
	bool thrown = false;
	try { operation(); } catch (const invalid_argument&) { thrown = true; }
	assert(thrown);
}

void TestEmptyAndEdgeCases() {
	cout << "Testing Empty Trees and Edge Cases..." << endl;
	RedBlackTree tree;
	CheckTree(tree, {});
	assert(tree.ToPostfixString().empty());
	assert(!tree.Contains(0));
	ExpectInvalidArgument([&] { tree.GetMin(); });
	ExpectInvalidArgument([&] { tree.GetMax(); });
	set<int> values;
	for (int value : {0, INT_MIN, INT_MAX, -1, 1}) {
		tree.Insert(value);
		values.insert(value);
		CheckTree(tree, values);
	}
	assert(!tree.Contains(2));
	for (int value : values) {
		string before = tree.ToPrefixString();
		ExpectInvalidArgument([&] { tree.Insert(value); });
		assert(tree.ToPrefixString() == before);
	}
	cout << "PASSED!" << endl << endl;
}

void TestAllRotationCases() {
	cout << "Testing All Rotation Cases..." << endl;
	for (const auto& sequence : vector<vector<int>>{
			{30, 20, 10}, {30, 10, 20}, {10, 30, 20}, {10, 20, 30}}) {
		RedBlackTree tree;
		for (int value : sequence) tree.Insert(value);
		assert(tree.ToPrefixString() == " B20  R10  R30 ");
		CheckTree(tree, {10, 20, 30});
	}
	cout << "PASSED!" << endl << endl;
}

void TestLargeTree() {
	cout << "Testing Large Trees..." << endl;
	mt19937 generator(2026);
	for (int order = 0; order < 3; ++order) {
		vector<int> sequence(2000);
		iota(sequence.begin(), sequence.end(), -1000);
		if (order == 1) reverse(sequence.begin(), sequence.end());
		if (order == 2) shuffle(sequence.begin(), sequence.end(), generator);
		RedBlackTree tree;
		set<int> expected;
		for (size_t i = 0; i < sequence.size(); ++i) {
			tree.Insert(sequence[i]);
			expected.insert(sequence[i]);
			if (i % 100 == 0) CheckTree(tree, expected);
		}
		CheckTree(tree, expected);
		assert(!tree.Contains(-1001));
		assert(!tree.Contains(1000));
		RedBlackTree copy(tree);
		CheckTree(copy, expected);
	}
	cout << "PASSED!" << endl << endl;
}

int main(){
	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestEmptyAndEdgeCases();
	TestAllRotationCases();
	TestLargeTree();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
