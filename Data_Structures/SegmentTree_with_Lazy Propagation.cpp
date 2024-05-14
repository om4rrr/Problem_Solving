struct Node {
    int val, isLazy, lazy;

    Node() {
        val = 0;
        isLazy = 0;
        lazy = 0;
    }

    Node(int v) {
        val = v;
        isLazy = 0;
        lazy = 0;
    }

    void operation(int v, int lx, int rx) {
        val += v * (rx - lx);
        lazy += v;
        isLazy = 1;
    }
};


struct segTree {

    vector<Node> segData;
    int static treeSize;

    segTree(int n) {
        treeSize = 1;
        while (treeSize < n)
            treeSize *= 2;
        segData.assign(2 * treeSize, Node());
    }

    Node merge(Node &lf, Node &ri) {
        Node ans;
        ans.val = lf.val + ri.val;
        return ans;
    }

    void propagete(int ni, int lx, int rx) {
        if (!segData[ni].isLazy || rx - lx == 1)
            return;

        int mid = (rx + lx) / 2;
        segData[2 * ni + 1].operation(segData[ni].lazy, lx, mid);
        segData[2 * ni + 2].operation(segData[ni].lazy, mid, rx);
        segData[ni].isLazy = 0;
        segData[ni].lazy = 0;

    }

    void init(vector<int> &nums, int ni = 0, int lx = 0, int rx = treeSize) {

        if (rx - lx == 1) {
            if (lx < (int) nums.size()) {
                segData[ni] = Node(nums[lx]);
            }
            return;
        }

        int mid = (rx + lx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);

        segData[ni] = merge(segData[2 * ni + 1], segData[2 * ni + 2]);
    }

    void update(int val, int l, int r, int ni = 0, int lx = 0, int rx = treeSize) {
        if (lx >= r || rx <= l)
            return;

        if (l <= lx && r >= rx) {
            segData[ni].operation(val, lx, rx);
            return;
        }

        propagete(ni, lx, rx);

        int mid = (rx + lx) / 2;
        update(val, l, r, 2 * ni + 1, lx, mid);
        update(val, l, r, 2 * ni + 2, mid, rx);

        segData[ni] = merge(segData[2 * ni + 1], segData[2 * ni + 2]);
    }


    Node query(int l, int r, int ni = 0, int lx = 0, int rx = treeSize) {
        if (lx >= r || rx <= l)
            return Node();

        if (l <= lx && r >= rx) {
            return segData[ni];
        }

        propagete(ni, lx, rx);

        int mid = (rx + lx) / 2;
        Node lf = query(l, r, 2 * ni + 1, lx, mid);
        Node ri = query(l, r, 2 * ni + 2, mid, rx);

        return merge(lf, ri);
    }

};