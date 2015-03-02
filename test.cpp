#include <iostream>
#include <cstdlib>
#include "Array.hpp"

using namespace std;
using namespace acc;

int main() {
    Array<int> v;
    for (int i = 0; i < 20; i++) {
        v.add(i);
    }
    v[1] = 9999;
    cout << v << endl;
    const Array<int> cv = static_cast<const Array<int> >(v);
    cout << cv[10] << endl;
    v.removeAt(9);
    cout << v << endl;

    Iterator<int> it = v.iter();
    while (it.isValid()) {
        cout << it.get() << endl;
        if (rand() % 4 < 1) {
            it.remove();
        }
        it.next();
    }

    return 0;
}