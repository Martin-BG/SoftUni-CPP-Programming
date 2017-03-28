#include<iostream>
#include<sstream>
using namespace std;

#define PI 3.14

#define SHOW(something) cout << something << endl;

#define UGLY(code) int main(){code; return 0;}

int main() {
    double radius;
    cin >> radius;

    SHOW(PI * radius * radius);
#undef SHOW
#define SHOW cout << "That's all, folks!" << endl;
    SHOW
#undef SHOW
    // The following line won't compile because SHOW is no longer defined
    // SHOW
    return 0;
}
