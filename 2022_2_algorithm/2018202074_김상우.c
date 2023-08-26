#include <stdio.h>
//header to use c language
int knapSack01(int i, int* val, int* wt, int w) {
	//main function to solve 0-1 knapsack problem
	if (i == 0 || w == 0) {
	//No more item or can't carry item anymore
		return 0;
		//return 0 dollar
	}
	else if (i > 0 && w > 0 && wt[i-1] > w) {
	//can add item but can't carry them
		return knapSack01(i-1, val, wt, w);
		//return no add item case
	}
	else if (i > 0 && w > 0 && wt[i-1] <= w) {
	//can add item and can carry them
		if (val[i - 1] + knapSack01(i-1, val, wt, w - wt[i - 1]) > knapSack01(i - 1, val, wt, w)) {
		//if add this item case is better than no add this item
			return val[i - 1] + knapSack01(i - 1, val, wt, w - wt[i - 1]);
			//return add this item case
		}
		else {
		//if add this item case is worse than no add this item
			return knapSack01(i-1, val, wt, w);
			//return no add this item case
		}
	}
}
int main() {
	int w = 5;
	printf("weight:");
	scanf_s("%d", &w);
	//limit of carry items weight
	int i = 4;
	printf("item:");
	scanf_s("%d", &i);
	//max number of items
	int val[5];
	for (int j = 0; j < i; j++) {
		printf("%d item value :", j);
		scanf_s("%d", &val[j]);
	}
	//array of value of each itme
	int wt[5];
	for (int j = 0; j < i; j++) {
		printf("%d item weight :", j);
		scanf_s("%d", &wt[j]);
	}
	//array of weight of each itme
	printf("%d", knapSack01(i, val, wt, w));

	return 0;
}