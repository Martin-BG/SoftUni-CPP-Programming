/* You are tasked with creating a console application which will store and
 display information about astronomical objects. Each object has a name of
 a home solar system, a position in the system, a mass in kg, a radius in
 meters, and a type (star, rocky planet, gas giant, unknown) and a nickname.
 Only some astronomical objects have a nickname. The name of the home solar
 system of an object can change (the solar system could be renamed), and the
 type can ONLY change from unknown to star, rocky planet, or gas giant.
 Objects of type star always have their position in the system set to 1.
 The designation of an astronomical object has the format:
    home solar system - position in the system (nickname)
 Where (nickname) is omitted if the object has no nickname. E.g. the sun of
 the Cancri system will have a designation Cancri-1, while the 8th planet
 named "Steel World" will have a designation of Cancri-9 (Steel World).
 Write a program, which allows the user to create info about astronomical
 objects as well as search for all planets of a star system (by typing the
 name of the system) or of a specific object of a system (by typing the name
 and position of the object). When displaying info about objects the user
 searched for, use the following format:
    designation { mass: mass in kg, radius: radius in meters }
 For example, if Steel World had a mass of 5.972e+24 kg and a radius of
 6137000 meters, displaying it to the user would look like:
    Cancri-9 (Steel World) {mass: 5.972e+24, radius: 6137000}
 (note: don't worry about the exact format of the numbers, just show the
 numbers however count decides to print them).
 Creating objects is up to you - just make sure a user can add the info
 of any type of astronomical object.
 The program should store the info in a text file (each time an object is
 created) and should load the info each time it starts (so that users can
 look-up objects they created previously).
 Make sure you create the proper classes, constructors, access modifiers and
 const methods for the above task. You should submit your program in a single
 .cpp file, but also add a file which contains input which can be copy-pasted
 into the console to demonstrate creating astronomical objects and searching
 for astronomical objects. */

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

class AstronomicalObject
{
private:
    enum ObjectType
    {
        STAR,
        ROCKY_PLANET,
        GAS_GIANT,
        UNKNOWN
    };

    const string object_type_name[4] {
        "Star", "Rocky planet",
        "Gas giant", "Unknown" };

    string solar_system_name;
    int possition_index;
    long double mass_in_kg;
    long long unsigned radius_in_m;
    ObjectType object_type;
    string nickname;

public:
    // Constructor
    AstronomicalObject(const string & solar_system_name,
                       const int & possition_index,
                       const long double mass_in_kg,
                       const long long unsigned radius_in_m,
                       ObjectType object_type,
                       const string & nickname = "") :
        solar_system_name(solar_system_name),
        possition_index(possition_index),
        mass_in_kg(mass_in_kg),
        radius_in_m(radius_in_m),
        object_type(object_type),
        nickname(nickname)
        {
            if(object_type == STAR && possition_index != 1)
            {
                this->possition_index = 1;
            }
        }

    // Destructor
    ~AstronomicalObject() {};

    // Copy constructor
    AstronomicalObject(const AstronomicalObject& other) :
        solar_system_name(other.solar_system_name),
        possition_index(other.possition_index),
        mass_in_kg(other.mass_in_kg),
        radius_in_m(other.radius_in_m),
        object_type(other.object_type),
        nickname(other.nickname) {}

    // Copy-assignment operator
    AstronomicalObject& operator= (const AstronomicalObject& other)
    {
        if (this != &other)
        {
            this->solar_system_name = other.solar_system_name;
            this->possition_index = other.possition_index;
            this->mass_in_kg = other.mass_in_kg;
            this->radius_in_m = other.radius_in_m;
            this->object_type = other.object_type;
            this->nickname = other.nickname;
        }
    }

    void setSolarSystemName(const string & new_name)
    {
        this->solar_system_name = new_name;
    }

    void setNickName(const string & new_nickname)
    {
        this->nickname = new_nickname;
    }

    void setType(ObjectType new_object_type)
    {
        if (this->object_type == ObjectType::UNKNOWN && new_object_type != ObjectType::UNKNOWN)
        {
            this->object_type = new_object_type;
        }
    }

    int getPossition() const
    {
        return this->possition_index;
    }

    unsigned long long getRadius() const
    {
        return this->radius_in_m;
    }

    long double getMass() const
    {
        return this->mass_in_kg;
    }

    string getNickname() const
    {
        return this->nickname;
    }

    string getSolarSystemName() const
    {
        return this->solar_system_name;
    }

    string getDesignation() const
    {
        stringstream ss;

        ss << this->solar_system_name << "-" << this->possition_index;

        if(this->nickname.size() > 0)
        {
            ss << "(" << this->nickname << ")";
        }

        return ss.str();
    }

    string getFullInfo() const
    {
        stringstream ss;

        ss << getDesignation() << "{mass: " << this->mass_in_kg
            << ", radius: " << this->radius_in_m << "}";

        return ss.str();
    }
};

int main()
{

    return 0;
}
