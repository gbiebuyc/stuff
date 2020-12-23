#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define MILLION 1000000

typedef struct		s_node
{
	int				val;
	struct s_node	*next;

}					t_node;

t_node *solve(bool ispart2) {
	char *input = "538914762";
	int numMoves = ispart2 ? 10*MILLION : 100;
	int numCups = ispart2 ? 1*MILLION : 9;
	t_node *nodes = malloc(sizeof(t_node) * numCups);
	t_node *cur = &nodes[input[0]-'0'-1];
	for (int i=numCups; i>0; i--) {
		int val = i;
		if (i<=9)
			val = input[i-1]-'0';
		t_node *new = &nodes[val-1];
		new->val = val;
		new->next = cur;
		cur = new;
	}
	for (int move=0; move<numMoves; move++) {
		t_node *pick = cur->next;
		cur->next = cur->next->next->next->next;
		int destVal = cur->val;
		bool ok = false;
		while (!ok) {
			destVal--;
			if (destVal == 0)
				destVal = numCups;
			if (destVal != pick->val &&
				destVal != pick->next->val &&
				destVal != pick->next->next->val)
				ok = true;
		}
		t_node *dest = &nodes[destVal-1];
		pick->next->next->next = dest->next;
		dest->next = pick;
		cur = cur->next;
	}
	while (cur->val != 1)
		cur = cur->next;
	return cur->next;
}

int main() {
	// Part 1
	t_node *cups = solve(false);
	while (cups->val != 1) {
		printf("%d", cups->val);
		cups = cups->next;
	}
	printf("\n");

	// Part 2
	cups = solve(true);
	printf("%ld\n", (int64_t)cups->val * (int64_t)cups->next->val);
}
