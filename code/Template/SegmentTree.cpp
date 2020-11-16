#include <iostream>
#include <cstring>

using namespace std;

template <class Type>
class SegmentTree {

private:
    struct Node {
        Type sum, tag;
        int l, r;
        Node *lson, *rson;
    };

    Node* root;

    void pushup(Node* rt) {
        rt->sum = rt->lson->sum + rt->rson->sum;
    }
    void pushdown(Node* rt) {
        if (rt->tag) {
            rt->lson->sum += rt->tag * (rt->lson->r - rt->lson->l + 1);
            rt->lson->tag += rt->tag;
            rt->rson->sum += rt->tag * (rt->rson->r - rt->rson->l + 1);
            rt->rson->tag += rt->tag;
            rt->tag = 0;
        }
    }

    Node* _alloc() {
        Node* p = new Node;
        memset(p, 0, sizeof(Node));
        return p;
    }

    void _destroy(Node* p) {
        if (p) {
            _destroy(p->lson);
            _destroy(p->rson);
        }
        delete p;
    }

public:

    SegmentTree() {
        root = _alloc();
    }
    ~SegmentTree() {
        _destroy(root);
    }

    Node* getRoot() { return root; }

    void build(Node* rt, Type* a, int l, int r) {
        rt->l = l, rt->r = r;
        if (l == r) {
            rt->sum = a[l];
            return;
        }
        rt->lson = _alloc(), rt->rson = _alloc();
        int mid = (l + r) >> 1;
        build(rt->lson, a, l, mid);
        build(rt->rson, a, mid + 1, r);
        pushup(rt);
    }

    Type query(Node* rt, int l, int r) {
        if (rt->l >= l && rt->r <= r) {
            return rt->sum;
        }
        pushdown(rt);
        Type ans = 0;
        int mid = (rt->l + rt->r) >> 1;
        if (l <= mid) ans += query(rt->lson, l, r);
        if (r > mid) ans += query(rt->rson, l, r);
        return ans;
    }

    void add(Node* rt, int l, int r, Type k) {
        if (rt->l >= l && rt->r <= r) {
            rt->sum += k * (rt->r - rt->l + 1);
            rt->tag += k;
            return;
        }
        pushdown(rt);
        int mid = (rt->l + rt->r) >> 1;
        if (l <= mid) add(rt->lson, l, r, k);
        if (r > mid) add(rt->rson, l, r, k);
        pushup(rt);
    }
};

int n, m;
long long int a[100001];
SegmentTree<long long int> t;

int main(int argc, char const *argv[]) {
	// freopen("testdata.in", "r", stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    t.build(t.getRoot(), a, 1, n);
    while (m --> 0) {
        int opt, a, b, c;
        cin >> opt;
        if (opt == 1) {
            cin >> a >> b >> c;
            t.add(t.getRoot(), a, b, c);
        }
        else {
            cin >> a >> b;
            cout << t.query(t.getRoot(), a, b) << endl;
        }
    }
    return 0;
}
