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
 for astronomical objects.


 TODO
* Display system information (data statistics about universe)
* Create random star systems
* Create random astronomical objects for existing star systems
* More unit and load tests could be added to auto testing suite
* Better save to file implementation
*/

#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<fstream>

using namespace std;

enum ObjectType
{
    OT_STAR,
    OT_ROCKY_PLANET,
    OT_GAS_GIANT,
    OT_UNKNOWN,
    OT_NUM_OF
};

const string ObjectTypeName[OT_NUM_OF]
{
    "Star",
    "Rocky planet",
    "Gas giant",
    "Unknown"
};

const string separator("---------------------------------------");

class StarSystem;

class AstronomicalObject
{
private:
    StarSystem * star_system;
    int index;
    long double mass;
    long long unsigned radius;
    ObjectType type;
    string nickname;

public:
    // Constructor
    AstronomicalObject(StarSystem * star_system,
                       const int & index,
                       const long double mass,
                       const long long unsigned radius,
                       ObjectType type,
                       const string & nickname = "") :
        star_system(star_system),
        index(index),
        mass(mass),
        radius(radius),
        type(type),
        nickname(nickname) {}

    // Destructor
    ~AstronomicalObject() {}

    // Copy constructor
    AstronomicalObject(const AstronomicalObject& other) :
        star_system(other.star_system),
        index(other.index),
        mass(other.mass),
        radius(other.radius),
        type(other.type),
        nickname(other.nickname) {}

    // Copy-assignment operator
    AstronomicalObject& operator= (const AstronomicalObject& other)
    {
        if (this != &other)
        {
            this->star_system = other.star_system;
            this->index = other.index;
            this->mass = other.mass;
            this->radius = other.radius;
            this->type = other.type;
            this->nickname = other.nickname;
        }

        return *this;
    }

    // Getters and setters
    void setStarSystem(StarSystem * star_system)
    {
        this->star_system = star_system;
    }

    StarSystem * getStarSystem() const
    {
        return this->star_system;
    }

    void setNickName(const string & nickname)
    {
        this->nickname = nickname;
    }

    string getNickname() const
    {
        return this->nickname;
    }

    void setType(const ObjectType & type)
    {
        if (this->type == OT_UNKNOWN && type != OT_UNKNOWN)
        {
            this->type = type;
        }
    }

    ObjectType getType() const
    {
        return this->type;
    }

    string getTypeName() const
    {
        return ObjectTypeName[this->type];
    }

    void setIndex(const int & index)
    {
        this->index = index;
    }

    int getIndex() const
    {
        return this->index;
    }

    unsigned long long getRadius() const
    {
        return this->radius;
    }

    void setRadius(const unsigned long long & radius)
    {
        this->radius = radius;
    }

    long double getMass() const
    {
        return this->mass;
    }

    void setMass(const long double & mass)
    {
        this->mass = mass;
    }
};

class StarSystem
{
private:
    string name;
    vector<AstronomicalObject*> * objects;
    int stars = 0;

    static bool objectCompareByIndex(const AstronomicalObject * obj_one, const AstronomicalObject * obj_two)
    {
        return (obj_one->getIndex() <= obj_two->getIndex()); // Sort by current index
    }

    void updateStarSystem()
    {
        sort(this->objects->begin(), this->objects->end(), objectCompareByIndex);
    //  Alternatively Lambda expression could be used for the sort:
    //  sort(objects->begin(), objects->end(), [](const AstronomicalObject * a, const AstronomicalObject * b) {return a->getIndex() <= b->getIndex();});

        this->stars = 0;

        for (int i = 0; i < this->objects->size(); i++)
        {
            if (this->objects->at(i)->getType() == OT_STAR)
            {
                this->stars++;
            }

            this->objects->at(i)->setIndex(i);
        }
    }
public:
    // Constructor
    StarSystem(const string & name) :
        name(name),
        objects(new vector<AstronomicalObject*>(0)),
        stars(0) {}

    // Destructor
    ~StarSystem()
    {
        while (!this->objects->empty())
        {
            AstronomicalObject * object = *(this->objects->end()-1);
            delete object;
            this->objects->erase(this->objects->end()-1);
        }

        delete objects;
    }

    // Copy constructor
    StarSystem(const StarSystem& other) :
        name(other.name),
        stars(other.stars)
    {
        for (int i = 0; i < other.objects->size(); i++)
        {
            this->objects->push_back(other.objects->at(i));
        }
    }

    // Copy-assignment operator
    StarSystem& operator= (const StarSystem& other)
    {
        if (this != &other)
        {
            this->name = other.name;
            this->stars = other.stars;

            for (int i = 0; i < other.objects->size(); i++)
            {
                this->objects->push_back(other.objects->at(i));
            }
        }

        return *this;
    }

    // Getters and setters
    string getName() const
    {
        return this->name;
    }

    void setName(const string & name)
    {
        this->name = name;
    }

    vector<AstronomicalObject*> * getObjects()
    {
        return this->objects;
    }

    AstronomicalObject & getObject(const int & index) const
    {
        if (index > 0 && index < this->getNumberOfObjects())
        {
            return *this->objects->at(index);
        }
        else
        {
            throw "Invalid index";
        }
    }

    int getNumberOfStars() const
    {
        return this->stars;
    }

    int getNumberOfObjects() const
    {
        return this->objects->size();
    }

    void addObject(const int & index,
                   const long double & mass,
                   const long long unsigned & radius,
                   ObjectType type,
                   const string & nickname = "")
    {
        this->objects->push_back(
            new AstronomicalObject(this, index, mass, radius, type, nickname));

        updateStarSystem();
    }

    void removeObject(AstronomicalObject * object)
    {
        this->objects->erase(this->objects->begin() + object->getIndex());

        delete object;

        updateStarSystem();
    }
};

struct  // Container for all star systems
{
private:
    vector<StarSystem*> * universe = new vector<StarSystem*>();

    struct FindSystem
    {   // Helper class for vector.find() method
        private:
        const string& name;

        public:
        FindSystem (const string& name) : name(name) {}

        bool operator()(const StarSystem * star_system) const
        {
            return star_system->getName() == this->name;
        }
    };

public:
    vector<StarSystem*> * getUniverse() const
    {
        return this->universe;
    }

    int getCountOfStarSystems() const
    {
        return this->universe->size();
    }

    void addStarSystem(StarSystem * star_system)
    {
        this->universe->push_back(star_system);
    }

    void addStarSystem(const string & name)
    {
        this->universe->push_back(new StarSystem(name));
    }

    void resetUniverse()
    {
        for (int i = 0; i < this->universe->size(); i++)
        {
            delete this->universe->back();
            this->universe->erase(this->universe->end()-1);
        }

        this->universe->clear();
    }

    StarSystem * getStarSystem(const string & name) const
    {
        auto it = find_if(this->universe->begin(), this->universe->end(), FindSystem(name));

        if (it != this->universe->end())
        {
          return this->universe->at(distance(this->universe->begin(), it));
        }

        return nullptr;
    }

    void removeStarSystem(const string & name)
    {
        auto it = find_if(this->universe->begin(), this->universe->end(), FindSystem(name));

        if (it != this->universe->end())
        {
            StarSystem * star_system = this->universe->at(distance(this->universe->begin(), it));
            this->universe->erase(it);
            delete star_system;
        }
    }

    StarSystem * findAstonomicalObjectByDesignation(const string & designation, int & index) const
    {
        size_t found = designation.find_last_of("-");
        string name = designation.substr(0, found);

        StarSystem * star_system = getStarSystem(name);

        if(star_system != nullptr)
        {
            if (star_system->getNumberOfStars() > 1)
            {
                if (designation[designation.size()-1] >= 'a')
                {
                    index = designation[designation.size()-1] - 'a';
                    index += stoi(designation.substr(found + 1, designation.size()-1));
                }
                else
                {
                    index = star_system->getNumberOfStars() - 1;
                    index += stoi(designation.substr(found + 1));
                }
            }
            else
            {
                index += stoi(designation.substr(found + 1));
            }

            index--; // Normalize index from user input (1, 2, 3 etc)

            if (index >= star_system->getObjects()->size() || index < 0)
            {
                star_system = nullptr;
            }
        }

        if (star_system == nullptr)
        {
            index = -1;
        }

        return star_system;
    }

    void saveDataToFile(const string & file_name) const
    {
        ofstream fs(file_name);

        int star_systems_count = universe->size();

        fs << star_systems_count << endl;

        for (int i = 0; i < star_systems_count; i++)
        {
            int star_system_size = universe->at(i)->getObjects()->size();

            fs << star_system_size << " " << universe->at(i)->getName() << endl;

            for (int j = 0; j < star_system_size; j++)
            {
                fs << j << " "                                              // int index
                    << universe->at(i)->getObjects()->at(j)->getMass() << " "       // long double mass
                    << universe->at(i)->getObjects()->at(j)->getRadius() << " "     // long long unsigned radius
                    << (int)universe->at(i)->getObjects()->at(j)->getType() << " "  // ObjectType type
                    << universe->at(i)->getObjects()->at(j)->getNickname() << endl; // string nickname
            }
        }

        fs.close();
    }

    void restoreDataFromFile(const string & file_name)
    {
        resetUniverse(); // Clear current data

        ifstream fs(file_name);

        int star_systems_count, star_system_size, index, temp;
        string star_system_name, object_nickname, line;
        long double mass;
        long long unsigned radius;
        ObjectType type;

        getline(fs, line);
        stringstream ss(line);
        ss >> star_systems_count;

        for (int i = 0; i < star_systems_count; i++)
        {
            getline(fs, line);

            stringstream ss(line);
            ss >> star_system_size;
            getline(ss >> ws, star_system_name);

            addStarSystem(star_system_name);

            StarSystem * star_system = getStarSystem(star_system_name);

            if (star_system != nullptr)
            {
                for (int j = 0; j < star_system_size; j++)
                {
                    object_nickname = "";
                    getline(fs, line);
                    stringstream ss(line);
                    ss >> ws >> index;
                    ss >> ws >> mass;
                    ss >> ws >> radius;
                    ss >> ws >> temp;
                    type = (ObjectType)temp;
                    getline(ss >> ws, object_nickname);

                    star_system->addObject(index, mass, radius, type, object_nickname);
                }
            }
        }

        fs.close();
    }
}KnownUniverse;

struct  // Data validate
{
public:
    bool canAddObjectAtIndex(const StarSystem * star_system, const int & index, const ObjectType type) const
    {
        if (index > star_system->getNumberOfObjects() // Leaves gap between elements
            || (type == OT_STAR && index > star_system->getNumberOfStars()) // Leaves non-star object(s) between old and new star
            || (type != OT_STAR && index < star_system->getNumberOfStars()))// Inserts non-star object before star
        {
            return false;
        }

        return true;
    }

    bool canCreateStarSystem(const string & name) const
    {
        if (KnownUniverse.getStarSystem(name) != nullptr)
        {   // Star system with this name already exists
            return false;
        }

        return true;
    }

    bool canDeleteObject(const AstronomicalObject * object, StarSystem * star_system) const
    {
        if (object->getType() == OT_STAR && star_system->getNumberOfStars() < 2)
        {   // Forbids deletion of the only sun. Also prevents deletion of all objects
            return false;
        }

        return true;
    }
}DataValidator;

struct  // Info builder
{
    string getObjectIndexString(AstronomicalObject * object) const
    {
        stringstream ss;

        if (object->getStarSystem()->getNumberOfStars() > 1)
        {   // Assuming that all stars in a system are at the center
            if (object->getType() == OT_STAR)
            {   // Stars are always with index 1 + letter
                ss << 1 << char('a' + object->getIndex());
            }
            else
            {   // Re-indexing objects to start from 2 in multi-star systems (1 is reserved for stars)
                ss << 2 + object->getIndex() - object->getStarSystem()->getNumberOfStars();
            }
        }
        else
        {   // Indexes start at 1
            ss << 1 + object->getIndex();
        }

        return ss.str();
    }

    string getObjectDesignation(AstronomicalObject * object) const
    {
        stringstream ss;

        ss << object->getStarSystem()->getName()
            << "-" << getObjectIndexString(object);

        if (object->getNickname().size() > 0)
        {
            ss << " (" << object->getNickname() << ")";
        }

        return ss.str();
    }

    string getFullObjectInfo(AstronomicalObject * object) const
    {
        stringstream ss;

        ss << getObjectDesignation(object)
            << " {type: " << object->getTypeName()
            << ", mass: " << object->getMass()
            << ", radius: " << object->getRadius() << "}";

        return ss.str();
    }

    string getStarSystemInfo(StarSystem * star_system) const
    {
        stringstream ss;

        for (int i = 0; i < star_system->getObjects()->size(); i++)
        {
            ss << getObjectDesignation(star_system->getObjects()->at(i)) << endl;
        }

        return ss.str();
    }

    string getStarSystemDetailedInfo(StarSystem * star_system) const
    {
        stringstream ss;

        ss << star_system->getName() << ", "
            << star_system->getNumberOfObjects()
            << " known astronomical objects:" << endl << endl;

        for (int i = 0; i < star_system->getObjects()->size(); i++)
        {
            ss << setw(2) << i+1 << " "
                << getFullObjectInfo(star_system->getObjects()->at(i)) << endl;
        }

        return ss.str();
    }

    string getUniverseInfo() const
    {
        stringstream ss;

        ss << "Star systems : " << KnownUniverse.getUniverse()->size() << endl;
        for (int i = 0; i < KnownUniverse.getUniverse()->size(); i++)
        {
            ss << KnownUniverse.getUniverse()->at(i)->getName() << endl;
        }

        return ss.str();
    }

    string getAstronomicalObjectsInfo() const
    {
        stringstream ss;

        StarSystem * star_system;
        for (int i = 0; i < KnownUniverse.getUniverse()->size(); i++)
        {
            star_system = KnownUniverse.getUniverse()->at(i);
            for (int j = 0; j < star_system->getNumberOfObjects(); j++)
            {
                ss << getObjectDesignation(star_system->getObjects()->at(j)) << endl;
            }
        }

        return ss.str();
    }
}InfoBuilder;

struct  // Unit and load tests
{
private:
    void createStarSystems(const int & number)
    {

        static const string system_names[] {
            // http://www.fantasynamegenerators.com/star-names.php#.WOAQJc996Hs
            "Fluaps", "Usla", "Boog", "Ozleil", "Doos",
            "Qigdauh", "Ugecteut", "Rojaif", "Odicceob", "Kioyeft",
            "Itrih", "Fluaf", "Kror", "Voosh", "Clauts",
            "Feadsa", "Choohelt", "Omiogdo", "Flonucs", "Ipriarsof" };
        static const int system_names_lenght = sizeof(system_names) / sizeof(string) - 1;
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const int alphanum_length = sizeof(alphanum) - 1;

        string name;
        for (int i = 0; i < number; i++)
        {
            if (i <= system_names_lenght)
            {
               name = system_names[i];
            }

            while (!DataValidator.canCreateStarSystem(name))
            {
                name = "";
                int name_length = 3 + rand() % 5;
                for (int j = 0; j < name_length; j++)
                {
                    name += alphanum[rand() % alphanum_length];
                }
            }

            KnownUniverse.addStarSystem(name);
        }
    }

    void createAstronomicalObjects(const int & number)
    {
        int universe_size = KnownUniverse.getUniverse()->size();

        if (universe_size == 0)
        {
            return;
        }

        for (int i = 0; i < number; i++)
        {
            StarSystem * star_system = KnownUniverse.getUniverse()->at(rand() % universe_size);
            long double mass = rand() % 100000 + i / 0.333;
            long long unsigned radius = rand() % 1000000;
            ObjectType type;

            if (star_system->getNumberOfStars() == 0)
            {
                type = OT_STAR;
            }
            else
            {
                type = ObjectType(rand() % OT_NUM_OF);

                if (type == OT_STAR && rand() % 10 > 0) // 10% chance for 2 or more stars
                {
                    type = ObjectType(1 + rand() % (OT_NUM_OF - 1));
                }
            }

            int index, start_index, end_index;

            if (type == OT_STAR)
            {
                start_index = 1;
                end_index = star_system->getNumberOfStars() + 1;
            }
            else
            {
                start_index = star_system->getNumberOfStars() + 1;
                end_index = star_system->getNumberOfObjects() + 1;
            }

            if (start_index < end_index)
            {
                index = start_index + rand() % (end_index - start_index);
            }
            else
            {
                index = start_index;
            }

            index--; // Normalize index to simulate console input (1, 2, 3 etc.)

            if (DataValidator.canAddObjectAtIndex(star_system, index, type))
            {
                static const string nicknames[] {
                    "Steel World", "Endor",
                    "Pandora", "Dagobah", "Jakku"};
                static const int nicknames_length = sizeof(nicknames) / sizeof(string) - 1;

                string name("");

                int nickname_index = rand() % 100;
                if (nickname_index <= nicknames_length)
                {
                    name = nicknames[nickname_index];
                }

                star_system->addObject(index, mass, radius, type, name);
            }
        }
    }
public:
    bool populateUniverse()
    {
        const int TEST_STAR_SYSTEMS = 20;
        const int TEST_ASTRO_OBJECTS = 200;
        createStarSystems(TEST_STAR_SYSTEMS);
        createAstronomicalObjects(TEST_ASTRO_OBJECTS);

        return true;
    }

}TestUniverse;

struct  // File master
{
private:
    const string file_name = "universe.txt";
public:
    void saveUniverseToFile() const
    {
        cout << "Saving universe data to [" << file_name << "]...";

        KnownUniverse.saveDataToFile(file_name);

        cout << " done" << endl;
    }

    void loadUniverseFromFile() const
    {
        cout << "Restoring universe data from [" << file_name << "]...";

        KnownUniverse.restoreDataFromFile(file_name);

        cout << " done" << endl;
    }
}FileWorker;

struct // User interaction
{
private:
    string getString() const
    {
        string name, input;
        cin.get();
        getline(cin, input);
        if (!input.empty())
        {
            istringstream istr(input);
            getline(istr >> ws, name);
        }

        return name;
    }

    StarSystem * selectStarSystemByName() const
    {
        string name;
        cout << "Enter star system name: ";
        cin >> name;
        cout << endl;

        StarSystem * star_system = KnownUniverse.getStarSystem(name);

        if(star_system == nullptr)
        {
            cout << "Invalid star system name" << endl;
        }

        return star_system;
    }

    int selectAstronomicalObjectByIndex(const int & max_index) const
    {
        int index;

        do
        {
            cout << "Enter astronomical object index (1-"
                << max_index << ", 0 to cancel): ";
            cin >> index;
        }
        while (index < 0 || index > max_index);

        return index;
    }

    void getAllObjectsInStarSystem() const
    {
        StarSystem * star_system = selectStarSystemByName();

        if(star_system != nullptr)
        {
            cout << InfoBuilder.getStarSystemDetailedInfo(star_system) << endl;
        }
    }

    void newAstronomicalObject(StarSystem * star_system) const
    {
        int temp;

        cout << "Specify new object type" << endl;
        for (int i = 0; i < OT_NUM_OF; i++)
        {
            cout << i + 1 << " " << ObjectTypeName[i] << endl;
        }

        do
        {
            cout << "Enter your selection (1-" << (int)OT_NUM_OF << "): ";
            cin >> temp;
            temp--; // Normalize input
        }
        while (temp < 0 || temp > (int)OT_NUM_OF);

        ObjectType type = (ObjectType)temp;

        int index, start_index, end_index;

        if (type == OT_STAR)
        {
            start_index = 1;
            end_index = star_system->getNumberOfStars() + 1;
        }
        else
        {
            start_index = star_system->getNumberOfStars() + 1;
            end_index = star_system->getNumberOfObjects() + 1;
        }

        do
        {
            cout << "Enter index for the new object (" << start_index << "-" << end_index << "): ";
            cin >> index;
            index--; // Normalize index
        }
        while (!DataValidator.canAddObjectAtIndex(star_system, index, type));

        unsigned long long radius;
        cout << "Enter radius for the new object (positive int): ";
        cin >> radius;

        long double mass;
        cout << "Enter mass for the new object (real number): ";
        cin >> mass;

        cout << "Enter nickname for the new object (could be blank too): ";
        string name = getString();

        star_system->addObject(index, mass, radius, type, name);

        cout << endl << "Created " << InfoBuilder.getFullObjectInfo(star_system->getObjects()->at(index)) << endl;
    }

    void editAstronomicalObject(StarSystem * star_system, const int & index) const
    {
        AstronomicalObject * object = star_system->getObjects()->at(index);

        while (true)
        {
            cout << endl << separator << endl
                << "Edit astronomical object" << endl << endl
                << InfoBuilder.getFullObjectInfo(object) << endl << endl
                << " 0 - Exit object edit" << endl
                << " 1 - Change mass (" << object->getMass() << ")" << endl
                << " 2 - Change radius (" << object->getRadius() << ")" << endl
                << " 3 - Change nickname (" << object->getNickname() << ")" << endl;

            if (object->getType() == OT_UNKNOWN)
            {
                cout << " 4 - Change type to " << ObjectTypeName[OT_GAS_GIANT] << endl
                    << " 5 - Change type to " << ObjectTypeName[OT_ROCKY_PLANET] << endl;
            }

            cout << endl << "Enter your selection: ";

            int selection;
            cin >> selection;
            cout << endl;
            switch (selection)
            {
                case 0:
                {
                    cout << "Cancel selected" << endl;
                    return;
                } break;
                case 1: // Mass
                {
                    long double mass;
                    cout << "Enter new mass (real number): ";
                    cin >> mass;
                    object->setMass(mass);
                 } break;
                case 2: // Radius
                {
                    unsigned long long radius;
                    cout << "Enter new radius (positive int): ";
                    cin >> radius;
                    object->setRadius(radius);
                } break;
                case 3: // Nickname
                {
                    cout << "Enter new nickname (could be empty): ";
                    string name = getString();
                    object->setNickName(name);
                } break;
                case 4: // Change type to Gas giant
                {
                    if (object->getType() == OT_UNKNOWN)
                    {
                        cout << "Changing object type to " << ObjectTypeName[OT_GAS_GIANT] << "...";
                        object->setType(OT_GAS_GIANT);
                        cout << " done" << endl;
                    }
                    else
                    {
                        cout << "Invalid selection!" << endl;
                    }
                } break;
                case 5: // Change type to Rocky planet
                {
                    if (object->getType() == OT_UNKNOWN)
                    {
                        cout << "Changing object type to " << ObjectTypeName[OT_ROCKY_PLANET] << "...";
                        object->setType(OT_ROCKY_PLANET);
                        cout << " done" << endl;
                    }
                    else
                    {
                        cout << "Invalid selection!" << endl;
                    }
                } break;
                default :
                {
                    cout << "Invalid selection!" << endl;
                } break;
            }
        }
    }

    // Star System menu
    void editStarSystemMain() const
    {
        StarSystem * star_system = selectStarSystemByName();

        if(star_system != nullptr)
        {
            cout << InfoBuilder.getStarSystemDetailedInfo(star_system) << endl;

            int selection;
            bool quit_program = false;
            while (!quit_program)
            {
                cout << separator << endl;
                cout << editStarSystemOptionsMenu(star_system);
                cin >> selection;
                cout << separator << endl;

                quit_program = actOnUserInputStarSystem(selection, star_system);
            }
        }
    }

    string editStarSystemOptionsMenu(StarSystem * star_system) const
    {
        stringstream ss;

        cout << "Selected star system: " << star_system->getName() << endl << endl
            << " 0 - Exit edit star system menu" << endl
            << " 1 - Star system details" << endl
            << " 2 - Remove astronomical object..." << endl
            << " 3 - Add astronomical object..." << endl
            << " 4 - Edit astronomical object..." << endl
            << " 5 - Rename star system..." << endl
            << endl
            << "Enter your selection: ";

        return ss.str();
    }

    bool actOnUserInputStarSystem(const int & selection, StarSystem * star_system) const
    {
        switch (selection)
        {
            case 0: // Exit edit star system menu
            {
                cout << "Exit program selected" << endl;
                return true;
            } break;
            case 1: // Star system details
            {
                cout << "Star system details selected" << endl;
                cout << InfoBuilder.getStarSystemDetailedInfo(star_system) << endl;
            } break;
            case 2: // Remove astronomical object
            {
                cout << "Remove astronomical object selected" << endl;
                int index = selectAstronomicalObjectByIndex(star_system->getNumberOfObjects());
                if (index > 0)
                {
                    index--; // Normalize index

                    if (DataValidator.canDeleteObject(star_system->getObjects()->at(index), star_system))
                    {
                        cout << "Deleting "
                            << InfoBuilder.getObjectDesignation(star_system->getObjects()->at(index))
                            << "...";

                        star_system->removeObject(star_system->getObjects()->at(index));

                        cout << " done" << endl;
                    }
                    else
                    {
                        cout << InfoBuilder.getObjectDesignation(star_system->getObjects()->at(index))
                            << " cannot be deleted" << endl;
                    }
                }
                else
                {
                    cout << "Remove canceled" << endl;
                }
            } break;
            case 3: // Add astronomical object
            {
                cout << "Add astronomical object selected" << endl;
                newAstronomicalObject(star_system);
            } break;
            case 4: // Edit astronomical object
            {
                cout << "Edit astronomical object selected" << endl;
                int index = selectAstronomicalObjectByIndex(star_system->getNumberOfObjects());
                if (index > 0)
                {
                    index--; // Normalize index
                    editAstronomicalObject(star_system, index);
                }
                else
                {
                    cout << "Edit canceled" << endl;
                }
            } break;
            case 5: // Rename star system
            {
                cout << "Rename star system selected" << endl;

                cout << "Enter new name for " << star_system->getName() << ": ";
                string name;
                cin >> name;

                if (DataValidator.canCreateStarSystem(name))
                {
                    star_system->setName(name);

                    cout << "Star system name changed to "
                        << star_system->getName() << endl;
                }
                else
                {
                    cout << "This name is already used" << endl;
                }
            } break;
            default:
            {
                cout << "Invalid selection!" << endl;
            } break;
        }

        return false;
    }

    // Create new star system
    void createNewStarSystem() const
    {
        cout << "Enter name for the new star system: ";
        string name;
        cin >> name;

        if (!DataValidator.canCreateStarSystem(name))
        {
            cout << "This name is already used" << endl;
            return;
        }

        KnownUniverse.addStarSystem(name);

        StarSystem * star_system = KnownUniverse.getStarSystem(name);

        if (star_system == nullptr)
        {
            cout << "Star system creation failed" << endl;
            return;
        }

        cout << endl << star_system->getName() << " has been created."
            << endl << "Define at least one star for it" << endl << endl;
        while (star_system->getNumberOfStars() < 1)
        {
            newAstronomicalObject(star_system);
        }

        cout << endl << InfoBuilder.getStarSystemDetailedInfo(star_system) << endl;
    }

    // Edit astronomical object
    void editAstronomicalObjectMain() const
    {
        string designation;
        cout << "Enter astronomical object designation (StarSystem-Index): ";
        cin >> designation;
        cout << endl;

        int index;
        StarSystem * star_system = KnownUniverse.findAstonomicalObjectByDesignation(designation, index);

        if(star_system == nullptr || index == -1)
        {
            cout << "Invalid astronomical object name" << endl;
            return;
        }

        cout << designation << " found in " << star_system->getName() << endl;

        editAstronomicalObject(star_system, index);
    }

    // Edit astronomical object
    void findAstronomicalObjectMain() const
    {
        string designation;
        cout << "Enter astronomical object designation (StarSystem-Index): ";
        cin >> designation;
        cout << endl;

        int index;
        StarSystem * star_system = KnownUniverse.findAstonomicalObjectByDesignation(designation, index);

        if(star_system == nullptr || index == -1)
        {
            cout << "Invalid astronomical object name" << endl;
            return;
        }

        cout << designation << " found in " << star_system->getName() << endl;

        cout << endl << InfoBuilder.getFullObjectInfo(star_system->getObjects()->at(index)) << endl;
    }
public:
    string optionsMenu() const
    {
        stringstream ss;

        ss << " 0 - Exit" << endl
            <<" 1 - List all star systems" << endl
            <<" 2 - List all astronomical objects" << endl
            <<" 3 - List objects in a star system..." << endl
            <<" 4 - Define a new star system..." << endl
            <<" 5 - Edit star system..." << endl
            <<" 6 - Edit astronomical object..." << endl
            <<" 7 - Search for star system by name..." << endl
            <<" 8 - Search for astronomical object..." << endl
            <<" 9 - Backup universe data to file" << endl
            <<"10 - Restore data form backup file" << endl
         //   <<"11 - Display system information" << endl
            <<"12 - Delete all data from memory" << endl
            <<"13 - Run automated tests" << endl
         //   <<"14 - Create random star systems" << endl
         //   <<"15 - Create random astronomical objects" << endl
         //   <<"     for existing star systems..." << endl
            << endl
            <<"Enter your selection: ";

        return ss.str();
    }

    bool actOnUserInput(const int & selection)
    {
        switch (selection)
        {
            case 0: // Exit
            {
                cout << "Exit program selected" << endl;
                return true;
            } break;
            case 1: // List all star systems
            {
                cout << "List all star systems selected" << endl
                    << InfoBuilder.getUniverseInfo();
            } break;
            case 2: // List all astronomical objects
            {
                cout << "List all astronomical objects selected" << endl
                    << InfoBuilder.getAstronomicalObjectsInfo();
            } break;
            case 3: // List objects in a star system
            {
                cout << "List objects in a star system selected" << endl;
                getAllObjectsInStarSystem();
            } break;
            case 4: // Define a new star system
            {
                cout << "Define a new star system selected" << endl;
                createNewStarSystem();
            } break;
            case 5: // Edit star system
            {
                cout << "Edit star system selected" << endl;
                editStarSystemMain();
            } break;
            case 6: // Edit astronomical object
            {
                cout << "Edit astronomical object selected" << endl;
                editAstronomicalObjectMain();
            } break;
            case 7: // Search for star system by name
            {
                cout << "Search for star system by name selected" << endl;

                StarSystem * star_system = selectStarSystemByName();

                if (star_system != nullptr)
                {
                    cout << InfoBuilder.getStarSystemDetailedInfo(star_system);
                }
            } break;
            case 8: // Search for astronomical object
            {
                cout << "Search for astronomical object" << endl;

                findAstronomicalObjectMain();
            } break;
            case 9: // Backup universe data to file
            {
                cout << "Backup universe data to file" << endl;
                FileWorker.saveUniverseToFile();
            } break;
            case 10: // Restore data form backup file
            {
                cout << "Restore data form backup file" << endl;
                FileWorker.loadUniverseFromFile();
            } break;
            case 12: // Delete all data from memory
            {
                cout << "Delete all data from memory selected" << endl;
                KnownUniverse.resetUniverse();
            } break;
            case 13: // Run automated tests
            {
                cout << "Run automated tests selected" << endl;
                TestUniverse.populateUniverse();
            } break;
            default:
            {
                cout << "Invalid selection!" << endl;
            } break;
        }

        return false;
    }
}UserInteraction;

int main()
{
    FileWorker.loadUniverseFromFile();  // Load previously saved data

    int selection;
    bool quit_program = false;
    while (!quit_program)
    {
        cout << separator << endl;
        cout << UserInteraction.optionsMenu();
        cin >> selection;
        cout << separator << endl;

        quit_program = UserInteraction.actOnUserInput(selection);
    }

    FileWorker.saveUniverseToFile();// Save data to file
    KnownUniverse.resetUniverse();  // Remove all objects from memory
    return 0;
}
