#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct PhysicalConstants {
    const long double g = 9.8067;
    const long double pi = 3.14159265359;
};

struct ObjectProperties {
    long double angularVelocity;
    long double radius;
    long double distance;
    long double mass;
    long double initialRadius;
};

struct Forces {
    PhysicalConstants constants; // create an instance to access members

    long double centripetalForce(ObjectProperties& objProps, const PhysicalConstants &constants) {
        return 4 * objProps.mass * objProps.angularVelocity * objProps.angularVelocity * constants.pi * constants.pi *
               (objProps.radius + objProps.distance);
    }

    long double gravitationalForce(const ObjectProperties& objProps) {
        return objProps.mass * constants.g; // use constants.g
    }

    long double netForce(const ObjectProperties& objProps) {
        long double fc = centripetalForce(objProps);
        long double fg = gravitationalForce(objProps);
        return sqrt(fc * fc + fg * fg);
    }
};

struct PhysicsCalculator {
    Forces forces;

    long double calculateRadius(const ObjectProperties& objProps) {
        return (forces.centripetalForce(objProps) * objProps.initialRadius) / forces.netForce(objProps);
    }
};

int main() {
    fstream out;
    out.open("fizica.out", ios::out);
    out << setprecision(100);

    ObjectProperties object{2, 0, 3, 1, 4};

    PhysicsCalculator calculator;
    long double r, Fc;
    for (int i = 1; i < 10; i++) {
        r = calculator.calculateRadius(object);
        Fc = calculator.forces.centripetalForce(object);

        out << ' ' << i << ".    Fc = " << Fc
            << "       r = " << r << '\n';
            object{2, r, 3, 1, 4};
    }

    for (int i = 10; i < 101; i++) {
        out << i << ".    Fc = " << calculator.forces.centripetalForce(object)
            << "       r = " << calculator.calculateRadius(object) << '\n';
    }

    return 0;
}
