#include <iostream>
#include <vector>

using std::cout;
using std::endl;
/* 第一列表示所有的man，第二列表示这个man看上了哪些women
     *          m1,  [n1, n3, n5]
     *          m2,  [n3, n6, n7, n9],  来者不拒啊
     *          m3,  [n1, n4]
     *          m4,  [], 高冷，一个没看上
     *
     */
int m = 10;
int n = 7;     // 总共有10个男生, 7个女生, 狼少肉多啊
std::vector<int> boys(m, -1);  // 记录分配给每个boy的妹子的id，刚开始的时候肯定一个都没分配
std::vector<int> girls(n, -1); // 记录每个妹子被分配给了哪个boy，刚开始的时候肯定还没分配出去
std::vector<int> visits(n, 0);// 标记访问过的顶点，只有未被访问过的妹子才能构成增广路径
std::vector<std::vector<bool> > vvMatches(m);  // 记录在每个boy与妹子之间是否有连线

// 输入是man的id，返回值是能否给这个man匹配到一个妹子
bool Find(int x) {
    for (int i = 0; i < n; ++i) {
//        cout << "x = " << x << ", i = " << i << endl;
//        cout << ", vvMatches[x][i] = " << vvMatches[x][i] << endl;
        if (!vvMatches[x][i]) { // 在boy_x和girl_i之间没有连线，别费劲了，下一个妹子
            continue;
        }

        // 这个妹子已经在给这个boy分配妹子的过程中，被访问过了，也就是已经有人预订了，
        // 这是一个强者为尊的世界，前面的就是强者，如果这个妹子girl_i已经被前面的人预定了，那这个boy_x也不用再痴心妄想了
        // 这个游戏就是这么玩的:
        // 排在后面的boy都比较强势,比如boy_D,他发现没有妹子剩给他的时候，他就去抢一个,假设D抢的妹子本来是C的，C被抢了之后他再去抢B的，
        // 这个时候D,C霸占着的妹子B是不敢抢的，但是除了这两个其它的所有妹子B都看不上，没有眼缘，这个时候B就不乐意了，反馈回去老子不干，
        // 我死也不会把妹子让出去的，D也觉得不过意，他抢了C的妹子后导致B没有妹子了。所以他就再去抢A的...，
        // 如果A被抢了后还能再找一个替补的，那么这次D抢人就成功了
        if (visits[i] == 1) {
            continue;
        }
        visits[i] = 1;

        if (girls[i] < 0 || Find(girls[i]))  {
            // 在boy_x和girl_i之间有连线，俩人看对眼了，并且girl_i还没被分配给其他的boy，那就正好把他俩连上
            // 如果girl_i已经被分配给了一个boy_y，那就让boy_y再去找一个，如果boy_y能够再找一个，那么当前的这个girl_i就能腾出来给boy_x
            girls[i] = x;
            boys[x] = i;
            return true;
        }
    }

    return false;
}

int main() {
    // 随机生成m个man, n个women之间的眼缘
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            vvMatches[i].push_back(rand() % 100 > 64);
        }
    }

    for (const auto& vMatches : vvMatches) {
        for (int id : vMatches) {
            cout << id << " ";
        }
        cout << endl;
    }

    // Step1: 对于每个boy，看看能不能给分配个妹子
    for (int i = 0; i < m; ++i) {
        visits = std::vector<int>(n, 0);
        Find(i);
    }

    for (int i = 0; i < m; ++i) {
        cout << "parterner: " << boys[i] << endl;
    }
}