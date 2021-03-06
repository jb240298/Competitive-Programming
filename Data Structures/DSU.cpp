int par[N]; 	// TODO: set par[i] = i
int sz[N]; 		// TODO: set sz[i] = 1

int findParent(int x) {
	if (par[x] == x) return x;
	return par[x] = findParent(par[x]);
}

void unionOf(int x, int y) {
	int xp = findParent(x);
	int yp = findParent(y);

	if (xp == yp) return;

	sz[yp] += sz[xp];
	par[xp] = yp;
}