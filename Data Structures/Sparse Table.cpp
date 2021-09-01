/**
HOW TO USE Sparse Table

vector<int> a = {1, 9, 8, -1, 6, -8, 2, 6};
sparse_table st(a.begin(), a.end(), [](int x, int y) {
    return min(x, y); // OPERATION (min(), max(), __gcd(), lcm())
});
**/

template<typename it, typename bin_op>
struct sparse_table {

    using T = typename remove_reference<decltype(*declval<it>())>::type;
    vector<vector<T>> t; bin_op f;

    sparse_table(it first, it last, bin_op op) : t(1), f(op) {
        int n = distance(first, last);
        t.assign(32 - __builtin_clz(n), vector<T>(n));
        t[0].assign(first, last);
        for (int i = 1; i < t.size(); i++)
            for (int j = 0; j < n - (1 << i) + 1; j++)
                t[i][j] = f(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
    }

    // returns f(a[l..r]) in O(1) time
    T query(int l, int r) {
        int h = floor(log2(r - l + 1));
        return f(t[h][l], t[h][r - (1 << h) + 1]);
    }
};

int main() {
    vector<int> a = {1, 9, 8, -1, 6, -8, 2, 6};
    sparse_table st(a.begin(), a.end(), [](int x, int y) {
        return min(x, y);
    });

    cout << st.query(0, 7) << endl;
}