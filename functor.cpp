#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <utility>

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
            if (groups[group_id].maxElem < a) {
                groups[group_id].maxElem = a;
            }
            groups[group_id].sum += val(a);
            groups[group_id].avg = static_cast<double>(groups[group_id].sum) / static_cast<double>(groups[group_id].count);
        }
    }
    return groups;
}

class Key {
public:
    int operator()(int y) const {return y % 10;}
    int operator()(double y) const {
        if (y < 0) return 0;
        if (y <= 10) return 1;
        return 2;
    }
    char operator()(string y) const {return y[0];}
};

class Value {
public:
    int operator()(int y) const {return y;}
    double operator()(double y) const {return y;}
    int operator()(string y) const {return static_cast<int>(y.length());}
};

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
    cout << "====== INT ======" << endl;
    const int intArr[] = {1, 11, 21, 31, 1, 11};
    const auto IntGroup = GroupStats(intArr, size(intArr), Key{}, Value{});
    for (const auto & i : IntGroup) {
        print(i);
    }
    cout << "====== DOUBLE ======" << endl;
    const double doubleArr[] = {-1, -4.3, 0, 0.2, 4.6234, 10.333};
    const auto doubleGroup = GroupStats(doubleArr, size(doubleArr), Key{}, Value{});
    for (const auto & i: doubleGroup) {
        print(i);
    }
    cout << "====== STRING ======" << endl;
    string strArr[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const auto stringGroup = GroupStats(strArr, size(strArr), Key{}, Value{});
    for (const auto & i : stringGroup) {
        print(i);
    }
    return 0;
}