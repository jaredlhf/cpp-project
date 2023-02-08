#include<stdio.h>
#include <iostream>

using namespace std;

#include "FollowsStore.h"

FollowsStore::FollowsStore() {}

void FollowsStore::addFollows(int leftLineNum, int rightLineNum) {
	followeeStore[rightLineNum] = leftLineNum;
	followerStore[leftLineNum] = rightLineNum;
	
}

int FollowsStore::getFollowee(int rightLineNum) {
	if (hasFollower(rightLineNum)) {
		return followeeStore[rightLineNum];
	}
	else {
		return -1;
	}
}

int FollowsStore::getFollower(int leftLineNum) {
	if (hasFollowee(leftLineNum)) {
		return followerStore[leftLineNum];
	}
	else {
		return -1;
	}
}

bool FollowsStore::hasFollowee(int lineNum) {
	if (followerStore.find(lineNum) != followerStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool FollowsStore::hasFollower(int lineNum) {
	if (followeeStore.find(lineNum) != followeeStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool FollowsStore::hasFollows(int leftLineNum, int rightLineNum) {
	return hasFollowee(leftLineNum) && hasFollower(rightLineNum);
}

unordered_set<int> FollowsStore::getAllFollowers() {
	unordered_set<int> followerList;
	for (const auto& [key, value] : followerStore) {
		followerList.insert(value);
	}
	return followerList;
}

unordered_set<int> FollowsStore::getAllFollowees() {
	unordered_set<int> followeeList;
	for (const auto& [key, value] : followeeStore) {
		followeeList.insert(value);
	}
	return followeeList;
}

void FollowsStore::clear() {
	followerStore.clear();
	followeeStore.clear();
}