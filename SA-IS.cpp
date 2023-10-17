// 注意点：扩容 1 格；length = n + 1；值域不能包含 0！

// 后缀类型
#define L_TYPE 0
#define S_TYPE 1

// 判断一个字符是否为LMS字符
bool is_lms_char(auto &type, int x) {
    return x > 0 && type[x] == S_TYPE && type[x - 1] == L_TYPE;
}

// 判断两个LMS子串是否相同
bool equal_substring(auto &S, int x, int y, auto &type) {
    do {
        if (S[x] != S[y]) {
            return false;
        }
        x++, y++;
    } while (!is_lms_char(type, x) && !is_lms_char(type, y));
    return S[x] == S[y];
}

void induced_sort(auto &S, auto &SA, auto &type, auto &bucket,
    auto &lbucket, auto &sbucket, int n, int SIGMA) {
    for (int i = 0; i <= n; i++) {
        if (SA[i] > 0 && type[SA[i] - 1] == L_TYPE) {
            SA[lbucket[S[SA[i] - 1]]++] = SA[i] - 1;
        }
    }
    for (int i = 1; i <= SIGMA; i++) {  // Reset S-type bucket
        sbucket[i] = bucket[i] - 1;
    }
    for (int i = n; i >= 0; i--) {
        if (SA[i] > 0 && type[SA[i] - 1] == S_TYPE) {
            SA[sbucket[S[SA[i] - 1]]--] = SA[i] - 1;
        }
    }
}

std::vector<int> SAIS(auto &S, int length, int SIGMA) {
    int n = length - 1;
    std::vector<int> type(n + 1);  // 后缀类型
    std::vector<int> position(n + 1);  // 记录LMS子串的起始位置
    std::vector<int> name(n + 1);  // 记录每个LMS子串的新名称
    std::vector<int> SA(n + 1);  // SA数组
    std::vector<int> bucket(SIGMA + 1);  // 每个字符的桶
    std::vector<int> lbucket(SIGMA + 1);  // 每个字符的L型桶的起始位置
    std::vector<int> sbucket(SIGMA + 1);  // 每个字符的S型桶的起始位置

    for (int i = 0; i <= n; i++) {
        bucket[S[i]]++;
    }
    for (int i = 1; i <= SIGMA; i++) {
        bucket[i] += bucket[i - 1];
        lbucket[i] = bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }

    // 确定后缀类型(利用引理2.1)
    type[n] = S_TYPE;
    for (int i = n - 1; i >= 0; i--) {
        if (S[i] < S[i + 1]) {
            type[i] = S_TYPE;
        } else if (S[i] > S[i + 1]) {
            type[i] = L_TYPE;
        } else {
            type[i] = type[i + 1];
        }
    }

    // 寻找每个LMS子串
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (type[i] == S_TYPE && type[i - 1] == L_TYPE) {
            position[cnt++] = i;
        }
    }

    // 对LMS子串进行排序
    std::fill(SA.begin(), SA.end(), -1);
    for (int i = 0; i < cnt; i++) {
        SA[sbucket[S[position[i]]]--] = position[i];
    }
    induced_sort(S, SA, type, bucket, lbucket, sbucket, n, SIGMA);

    // 为每个LMS子串命名
    std::fill(name.begin(), name.end(), -1);
    int lastx = -1, namecnt = 1;  // 上一次处理的LMS子串与名称的计数
    bool flag = false;  // 这里顺便记录是否有重复的字符
    for (int i = 1; i <= n; i++) {
        int x = SA[i];

        if (is_lms_char(type, x)) {
            if (lastx >= 0 && !equal_substring(S, x, lastx, type)) {
                namecnt++;
            }
            // 因为只有相同的LMS子串才会有同样的名称
            if (lastx >= 0 && namecnt == name[lastx]) {
                flag = true;
            }

            name[x] = namecnt;
            lastx = x;
        }
    }  // for
    name[n] = 0;

    // 生成S1
    std::vector<int> S1(cnt);
    int pos = 0;
    for (int i = 0; i <= n; i++) {
        if (name[i] >= 0) {
            S1[pos++] = name[i];
        }
    }

    std::vector<int> SA1;
    if (!flag) {
        // 直接计算SA1
        SA1.assign(cnt + 1, 0);

        for (int i = 0; i < cnt; i++) {
            SA1[S1[i]] = i;
        }
    } else {
        SA1 = SAIS(S1, cnt, namecnt);  // 递归计算SA1
    }

    // 从SA1诱导到SA
    lbucket[0] = sbucket[0] = 0;
    for (int i = 1; i <= SIGMA; i++) {
        lbucket[i] = bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }
    std::fill(SA.begin(), SA.end(), -1);
    for (int i = cnt - 1; i >= 0; i--) {  // 这里是逆序扫描SA1，因为SA中S型桶是倒序的
        SA[sbucket[S[position[SA1[i]]]]--] = position[SA1[i]];
    }
    induced_sort(S, SA, type, bucket, lbucket, sbucket, n, SIGMA);

    // 后缀数组计算完毕
    return SA;
}