#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main() {
    system("chcp 65001");
    int n, M, K;
    cout << "输入课程数n: ";
    cin >> n;
    
    vector<int> credit(n); // 每门课的学分
    cout << "输入每门课的学分（共" << n << "个）: ";
    for (int i = 0; i < n; i++) {
        cin >> credit[i];
    }
    
    cout << "输入每学期学分上限M: ";
    cin >> M;
    cout << "输入学期数上限K: ";
    cin >> K;
    
    vector<vector<int>> prereq(n); // 先修关系图
    int p;
    cout << "输入先修关系数量: ";
    cin >> p;
    cout << "输入先修关系（每行两个整数a b，表示a是b的先修课，课程编号从1开始）: " << endl;
    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--; // 转换为0-based
        prereq[b].push_back(a); // b的先修课是a
    }
    
    // 预处理：计算每个课程集合的总学分
    vector<int> sum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum[mask] += credit[i];
            }
        }
    }
    
    // 预处理：每个课程的先修课程集合（用掩码表示）
    vector<int> preMask(n, 0);
    for (int i = 0; i < n; i++) {
        for (int pre : prereq[i]) {
            preMask[i] |= (1 << pre);
        }
    }
    
    // DP数组：dp[mask][t] 表示已经安排了mask中的课程，用了t个学期的方案数
    vector<vector<long long>> dp(1 << n, vector<long long>(K + 1, 0));
    dp[0][0] = 1; // 初始状态：没有安排课程，用了0个学期
    
    // 遍历所有状态
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int t = 0; t < K; t++) {
            if (dp[mask][t] == 0) continue;
            
            // 计算当前可以选择的课程集合：未安排且先修条件已满足
            int available = 0;
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) { // 未安排
                    if ((mask & preMask[i]) == preMask[i]) { // 先修条件满足
                        available |= (1 << i);
                    }
                }
            }
            
            // 枚举available的所有非空子集
            for (int sub = available; sub; sub = (sub - 1) & available) {
                // 检查学分上限
                if (sum[sub] > M) continue;
                
                // 检查子集内部是否有先修冲突（即子集中不能有课程互为先修）
                bool conflict = false;
                for (int i = 0; i < n; i++) {
                    if (sub & (1 << i)) {
                        // 如果子集中包含当前课程i的先修课程，则冲突
                        if (sub & preMask[i]) {
                            conflict = true;
                            break;
                        }
                    }
                }
                if (conflict) continue;
                
                // 转移
                int newMask = mask | sub;
                dp[newMask][t + 1] += dp[mask][t];
            }
        }
    }
    
    // 统计所有安排完所有课程（mask为全1）且用了不超过K个学期的方案数
    long long ans = 0;
    for (int t = 1; t <= K; t++) {
        ans += dp[(1 << n) - 1][t];
    }
    
    cout << "排课方案数: " << ans << endl;
    
    return 0;
}