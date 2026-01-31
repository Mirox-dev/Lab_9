#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename Key, typename Elem, typename Sum>
struct GroupInfo {
    Key key;
    size_t count;
    Elem minElem;
    Elem maxElem;
    Sum sum;
    double avg;
};

template <typename T, typename Key, typename Val>

auto GroupStats(const T* arr, const size_t n, Key key, Val val) {
    using keytype = decltype(key(declval<T>()));
    using valtype = decltype(val(declval<T>()));
    vector<GroupInfo<keytype, T, valtype>> groups;
    for (size_t i = 0; i < n; ++i) {
        const T& a = arr[i];
        size_t group_id = 0;
        for (; group_id < groups.size(); ++group_id) {
            if (groups[group_id].key == key(a)) {
                break;
            }
        }
        if (group_id == groups.size()) {
            GroupInfo<keytype, T, valtype> group{} ;
            group.key = key(a);
            group.count = 1;
            group.minElem = a;
            group.maxElem = a;
            group.sum = val(a);
            group.avg = static_cast<double>(val(a));
            groups.push_back(group);
        }
        else {
            groups[group_id].count += 1;
            if (groups[group_id].minElem > a) {
                groups[group_id].minElem = a;
            }
            if (a > groups[group_id].maxElem) {
                groups[group_id].maxElem = a;
            }
            groups[group_id].sum += val(a);
            groups[group_id].avg = static_cast<double>(groups[group_id].sum) / static_cast<double>(groups[group_id].count);
        }
    }
    return groups;
}

class Mine {
    double x;
    double y;
public:
    Mine() : x(0), y(0) {}
    Mine(double x, double y) : x(x), y(y) {}

    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }
    [[nodiscard]] double length() const {
        return sqrt(x * x + y * y);
    }
    Mine operator+(const Mine& sec) const {
        return {x + sec.x, y + sec.y};
    }
    bool operator>(const Mine& sec) const {
        return this->length() > sec.length();
    }
};
ostream& operator<<(ostream& out, const Mine& sec) {
    out << "(" << sec.getX() << ", " << sec.getY() << ")" << endl;
    return out;
}

template<typename Key, typename Elem, typename Sum>
void print(const GroupInfo<Key, Elem, Sum>& g) {
    cout << "Key: " << g.key << "  "
         << "Count: " << g.count << "  "
         << "MinElement: " << g.minElem << "  "
         << "MaxElement: " << g.maxElem << "  "
         << "Sum: " << g.sum << "  "
         << "Average: " << g.avg << endl << endl;
}

int main() {
    cout << "====== VECTOR ======" << endl;
    const Mine MineArr[] = {Mine(4, 2), Mine(1, 5), Mine(6, 3), Mine(3, 3), Mine(4, 5)};
    const auto MineGroup = GroupStats(MineArr, size(MineArr),
        [](const Mine& mine) {return mine.getX() + mine.getY();},
        [](const Mine& mine) {return mine.length();});
    for (const auto & i : MineGroup) {
        print(i);
    }
    return 0;
}