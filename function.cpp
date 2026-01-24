#include <iostream>
#include <vector>
#include <string>
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

template <typename T, typename Val, typename Key>

auto GroupStats(const T* arr, const size_t n, Key (*keyFunc)(T), Val (*valueFunc)(T)) {
    vector<GroupInfo<Key, T, Val>> groups;
    for (size_t i = 0; i < n; ++i) {
        const T& a = arr[i];
        size_t group_id = 0;
        for (; group_id < groups.size(); ++group_id) {
            if (groups[group_id].key == keyFunc(a)) {
                break;
            }
        }
        if (group_id == groups.size()) {
            GroupInfo<Key, T, Val> group{} ;
            group.key = keyFunc(a);
            group.count = 1;
            group.minElem = a;
            group.maxElem = a;
            group.sum = valueFunc(a);
            group.avg = valueFunc(a);
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
            groups[group_id].sum += valueFunc(a);
            groups[group_id].avg = static_cast<double>(groups[group_id].sum) / static_cast<double>(groups[group_id].count);
        }
    }
    return groups;
}

// int
int KeyInt(const int x) {
    return x % 10;
}

int ValueInt(int const x) {return x;}

// double
int KeyDouble(double const x) {
    if (x < 0) return 0;
    if (x <= 10) return 1;
    return 2;
}

double ValueDouble(const double x) {return x;}

// str
char KeyStr(const string x) {return x[0];}

int ValueStr(const string x) {
    return static_cast<int>(x.size());
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
    cout << "====== INT ======" << endl;
    const int intArr[] = {1, 11, 21, 31, 1, 11};
    const auto IntGroup = GroupStats(intArr, size(intArr), KeyInt, ValueInt);
    for (const auto & i : IntGroup) {
        print(i);
    }
    cout << "====== DOUBLE ======" << endl;
    const double doubleArr[] = {-1, -4.3, 0, 0.2, 4.6234, 10.333};
    const auto doubleGroup = GroupStats(doubleArr, size(doubleArr), KeyDouble, ValueDouble);
    for (const auto & i: doubleGroup) {
        print(i);
    }
    cout << "====== STRING ======" << endl;
    string strArr[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const auto stringGroup = GroupStats(strArr, size(strArr), KeyStr, ValueStr);
    for (const auto & i : stringGroup) {
        print(i);
    }
    return 0;
}