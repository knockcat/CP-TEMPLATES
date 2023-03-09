#include <bits/stdc++.h>
using namespace std;

// 1 based Indexing

template <typename T>
class BIT
{
public:
    T N;
    vector<T> fen;

    BIT() {}
    BIT(int n)
    {
        N = n;
        fen.assign(n + 1, 0); // intialised with 0 at first
    }

    void update(int idx, int val)
    {
        while (idx <= N)
        {
            fen[idx] += val;
            idx += (idx & (-idx));
        }
    }

    int prefSum(int idx)
    {
        int sum = 0;
        while (idx > 0)
        {
            sum += fen[idx];
            idx -= (idx & (-idx));
        }
        return sum;
    }

    int rangeSum(int l, int r)
    {
        return prefSum(r) - prefSum(l - 1);
    }

    void updateMax(int idx, int val)
    {
        while (idx <= N)
        {
            fen[idx] = max(fen[idx], val);
            idx += (idx & (-idx));
        }
    }

    int prefMax(int idx)
    {
        int ans = -2e9;
        while (idx > 0)
        {
            ans = max(ans, fen[idx]);
            idx -= (idx & (-idx));
        }
        return ans;
    }

    // lower_bound of prefix Sum
    int find(int k)
    {
        int curr = 0, ans = 0, prevSum = 0;
        for (int i = log2(N); i >= 0; --i)
        {
            if (fen[curr + (1 << i)] + prevSum < k)
            {
                curr += (1 << i);
                prevSum += fen[curr];
            }
        }
        return (curr + 1);
    }

    int find1(int k)
    {
        int curr = 0, ans = 0, prevsum = 0;
        for (int i = 19; i >= 0; i--)
        {
            if ((curr + (1 << i)) < N && fen[curr + (1 << i)] + prevsum < k)
            {
                ans = curr + (1 << i);
                curr = ans;
                prevsum += fen[curr];
            }
        }

        return (ans + 1);
    }
};
// BIT<int> bit(n);

// bit.update(idx, val);    // update
// bit.prefSum(idx);        // pref sum till idx
// bit.rangeSum(l, r);      // range sum of [l,r]
// bit.updateMax(idx, val); // update all the values containing sum of range idx with max(val,fen[idx]);
// bit.prefMax(idx);        // max in all the prefixes containing idx [l idx r] also inclusive
// bit.find(k);             // idx of lower_bound of prefix sum
// bit.find1(k);             // another version with bound condition

int32_t main()
{
    int n;
    cin >> n;

    vector<int> v(n);

    BIT<int> bit(n);

    for (int i = 1; i <= n; ++i)
    {
        cin >> v[i];
        // update
        bit.update(i, v[i]);
    }

    int q;
    cin >> q;

    // range sum for queries
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << bit.rangeSum(l, r) << endl;
    }

    // max in all the prefixes containing 9 [l 9 r] also inclusive
    cout << bit.prefMax(9) << endl;

    // prefix sum at index 11
    cout << bit.prefSum(11) << endl;

    // lower_bound of prefix sum
    cout << bit.find(11) << endl;

    // update all the values containing sum of range idx with max(val,fen[idx]);
    bit.updateMax(1, 9);

    for (auto itr : bit.fen)
        cout << itr << " ";
    cout << endl;

    return 0;
}
