#include<iostream>
using namespace std;

int main() {
    enum planets {earth = 3, mars, jupiter, saturn, uranus, neptune};

    // We can do math on this enum, because it is just const int underneath
    cout << "earth (" << earth << ") is "
        << uranus - earth << " planets away from "
        << "uranus (" << uranus << ")" << endl;

    enum class Planets {earth = 3, mars, jupiter, saturn, uranus, neptune};

    Planets planetEarth = Planets::earth;
    // the line below will cause a compilation error - just earth means the other enum's earth
    //Planets planetEarthInvalid = earth;

    // You can also specify the type the enum class uses
    // NOTE: we can't do math on these without explicitly converting them to a numeric type
    enum class PlanetsChar : char {earth = 'e', mars = 'm', jupiter = 'j', saturn = 's', uranus = 'u', neptune = 'n'};
    PlanetsChar planetEarthChar = PlanetsChar::earth;

    return 0;
}
