/* Write classes which can save an array of Person objects and an array of car registrations
 (from task 3) into a file, as well as read them back from a file. Hint: make sure you first
 read/write the Person objects – notice that you can't store pointers to Person objects in a
 file for your car registration (you can, but they won't be valid, since the memory addresses
 will change), but you should instead store the id of the person and then find that person in
 the array to re-create the car registration. Make sure you create the proper classes,
 constructors, access modifiers and const methods for the above task. You need to write two
 programs for this task, 4A and 4B, and submit the .cpp files for 4A and 4B.
Task 4A
 Write a program which writes several Person objects and car registrations to a file.
 You should submit your program in a single .cpp file. */

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>

using namespace std;

class Person
{
private:
    string name;
    int age;
    int id;

    static int getID()
    {
        static int nextID = 0;

        return nextID++;
    }

public:
    // Constructor
    Person(const string& name, const int& age) :
        name(name),
        age(age)
    {
        id = getID();
    }

    // Destructor
    ~Person() {}

    // Copy constructor
    Person(const Person& other) :
        name(other.name),
        age(other.age),
        id(other.id) {}

    // Copy-assignment operator
    Person& operator= (const Person& other)
    {
        if (this != &other) {
            this->name = other.name;
            this->age = other.age;
            this->id = other.id;
        }

        return *this;
    }

    int getId() const
    {
        return this->id;
    }

    string getName() const
    {
        return this->name;
    }

    void changeName(const string & name)
    {
        this->name = name;
    }

    int getAge() const
    {
        return this->age;
    }

    void changeAge(const int & age)
    {
        this->age = age;
    }

    string getInfo() const
    {
        ostringstream str;
        str << "Name: " << this->name << endl
            << "Age: " << this->age << endl
            << "ID: " << this->id << endl;
        return str.str();
    }

    string getPackedData() const
    {
        ostringstream str;
        str << this->id << " " << this->age
            << " " << this->name << endl;
        return str.str();
    }
};

class Car
{
private:
    string manufacturer;
    string model;
    Person * owner;
    int horsepower;
    string registration_number;

public:
    // Constructor
    Car(const string & manufacturer, const string & model, int horsepower,
            Person * owner, const string & registration_number) :
        manufacturer(manufacturer),
        model(model),
        horsepower(horsepower),
        owner(owner),
        registration_number(registration_number) {}

    // Destructor
    ~Car(){}

    // Copy constructor
    Car(const Car& other) :
        manufacturer(other.manufacturer),
        model(other.model),
        horsepower(other.horsepower),
        owner(other.owner),
        registration_number(other.registration_number) {}

    // Copy-assignment operator
    Car& operator= (const Car& other) {
        if (this != &other) {
            this->manufacturer = other.manufacturer;
            this->model = other.model;
            this->horsepower = other.horsepower;
            this->owner = other.owner;
            this->registration_number = other.registration_number;
        }

        return *this;
    }

    void changeOwner(Person * owner, const string & registration_number)
    {
        this->owner = owner;
        this->registration_number = registration_number;
    }

    string getRegistration() const
    {
        return this->registration_number;
    }

    Person * getOwner() const
    {
        return this->owner;
    }

    int getHorsepower() const
    {
        return this->horsepower;
    }

    string getManufacturer() const
    {
        return this->manufacturer;
    }

    string getModel() const
    {
        return this->model;
    }

    string getInfo() const
    {
        ostringstream str;
        str << "Registration Number: " << this->registration_number << endl
            << "Manufacturer: " << this->manufacturer << endl
            << "Model: " << this->model << endl
            << "Horsepower: " << this->horsepower << endl << "....."<< endl
            << "Owner details:" << endl << this->owner->getInfo() << endl;
        return str.str();
    }

    string getPackedData() const
    {
        ostringstream str;
        str << this->registration_number << endl
            << this->manufacturer << endl
            << this->model << endl
            << this->horsepower << endl
            << this->owner->getId() << endl;
        return str.str();
    }
};

class CarsRegister
{
private:
    static vector<Car*> registeredCars;
    static vector<Person*> personsList;

    static void clearRegisteredCars()
    {
        while (!registeredCars.empty())
        {
            delete CarsRegister::registeredCars.back();
            CarsRegister::registeredCars.erase(registeredCars.end()-1);
        }

        CarsRegister::registeredCars.clear();
    }

    static void clearPersonsList()
    {
        while (!personsList.empty())
        {
            delete CarsRegister::personsList.back();
            CarsRegister::personsList.erase(personsList.end()-1);
        }

        CarsRegister::personsList.clear();
    }

public:
    static Person * addPerson(const string & name, const int & age)
    {
        Person * person = new Person(name, age);
        personsList.push_back(person);
        return person;
    }

    static void generatePersons(const int & persons)
    {
        static string names[5] {"Alex", "John", "Peter", "Ronald", "Ivan" };
        static string family_names[5] {" White", " Black", " Gray", " Green", " Pink"};
        for (int i = 0; i < persons; i++)
        {
            personsList.push_back(new Person(names[rand()%5] + family_names[rand()%5],
                                             16 + rand()%50));
        }
    }

    static Car * addCarRegistration(const string & manufacturer, const string & model,
                        int horsepower, Person * owner, const string & registration_number)
    {
        Car * car = new Car(manufacturer, model, horsepower, owner, registration_number);
        registeredCars.push_back(car);
        return car;
    }

    static void generateCarRegistrations(const int & cars)
    {
        static string manufacrurers[5] {"Honda", "BMW", "Lexus", "Ford", "Tesla" };
        static string models[5] {"Civic", "3 Series", "RX 350", "Mustang", "Model 3"};

        if (personsList.size() > 0)
        {
            for (int i = 0; i < cars; i++)
            {
                registeredCars.push_back(new Car(manufacrurers[i%5],
                                                 models[i%5],
                                                 20 + rand()%50,
                                                 personsList[rand() % personsList.size()],
                                                 "AU-" + to_string(rand()%99999)));
            }
        }
    }

    static void saveRegistrationsInfoToFile(const string & file_name)
    {
        ofstream fs(file_name);

        for (int i = 0; i < registeredCars.size(); i++)
        {
            fs << ".............................."
                << endl << registeredCars[i]->getInfo();
        }

        fs.close();
    }

    static void savePersonsInfoToFile(const string & file_name)
    {
        ofstream fs(file_name);

        for (int i = 0; i < personsList.size(); i++)
        {
            fs << ".............................."
                << endl << personsList[i]->getInfo();
        }

        fs.close();
    }

    static string getCarsInfo()
    {
        ostringstream str;
        for (int i = 0; i < registeredCars.size(); i++)
        {
            str << ".............................."
                << endl << registeredCars[i]->getInfo();
        }
        str << endl;

        return str.str();
    }

    static string getPersonsInfo()
    {
        ostringstream str;
        for (int i = 0; i < personsList.size(); i++)
        {
            str << ".............................."
                << endl << personsList[i]->getInfo();
        }
        str << endl;

        return str.str();
    }

    static string getSystemInfo()
    {
        ostringstream str;
        str << "Active persons: " << personsList.size() << endl
            << "Active registrations: " << registeredCars.size()
            << endl << endl;
        return str.str();
    }

    static int findPersonIndexByID(const int & id)
    {
        for (int i = 0; i < personsList.size(); i++)
        {
            if (personsList[i]->getId() == id)
            {
                return i;
            }
        }

        return -1;
    }

    static int findCarIndexByRegistration(const string & registration)
    {
        for (int i = 0; i < registeredCars.size(); i++)
        {
            if (registeredCars[i]->getRegistration() == registration)
            {
                return i;
            }
        }

        return -1;
    }

    static Person & getPersonByIndex(const int & index)
    {
        if (index < personsList.size())
        {
           return *personsList[index];
        }
        else
        {
            throw "invalid person index";
        }
    }

    static Car & getRegistrationByIndex(const int & index)
    {
        if (index < registeredCars.size())
        {
           return *registeredCars[index];
        }
        else
        {
            throw "invalid registration index";
        }
    }

    static void clearGlobalData()
    {
        clearPersonsList();
        clearRegisteredCars();
    }

    static void saveAllDataToFile(const string & file_name)
    {
        ofstream fs(file_name);

        fs << personsList.size() << endl;
        for (int i = 0; i < personsList.size(); i++)
        {
            fs << personsList[i]->getPackedData();
        }

        fs << registeredCars.size() << endl;
        for (int i = 0; i < registeredCars.size(); i++)
        {
            fs << registeredCars[i]->getPackedData();
        }

        fs.close();
    }
};

vector<Car*> CarsRegister::registeredCars;
vector<Person*> CarsRegister::personsList;

int main()
{
    while (true)
    {
        int selection;
        cout << "------------------------------" << endl
            << "0 - Exit" << endl
            << "1 - List all persons" << endl
            << "2 - List all registrations" << endl
            << "3 - Change person name..." << endl
            << "4 - Change person age..." << endl
            << "5 - Change car registration..." << endl
            << "6 - Generate random persons..." << endl
            << "7 - Generate random registrations..." << endl
            << "8 - Create a new person..." << endl
            << "9 - Create a new registration..." << endl
            << "10- System Information" << endl
            << "11- Export all persons to file..." << endl
            << "12- Export all registrations to file..." << endl
            << "13- Reset all data" << endl
            << "14- Save all data to file..." << endl << endl
            << "Enter your selection: ";
        cin >> selection;
        cout << "------------------------------" << endl;

        switch(selection)
        {
            case 0:
                {
                    CarsRegister::clearGlobalData();

                    return 0;
                } break;
            case 1: cout << endl << CarsRegister::getPersonsInfo(); break;
            case 2: cout << endl << CarsRegister::getCarsInfo(); break;
            case 3:
                {
                    cout << "Enter person ID: ";
                    cin >> selection;
                    int index = CarsRegister::findPersonIndexByID(selection);
                    if (index != -1)
                    {
                        Person & person = CarsRegister::getPersonByIndex(index);
                        cout << endl << person.getInfo()
                            << "Enter new name: ";
                        getchar();
                        string name;
                        getline(cin >> ws, name);;
                        person.changeName(name);
                        cout << endl << person.getInfo();
                    }
                    else
                    {
                        cout << "Invalid selection" << endl;
                    }
                }   break;
            case 4:
                {
                    cout << "Enter person ID: ";
                    cin >> selection;
                    int index = CarsRegister::findPersonIndexByID(selection);
                    if (index != -1)
                    {
                        Person & person = CarsRegister::getPersonByIndex(index);
                        cout << endl << person.getInfo()
                            << "Enter new age: ";
                        cin >> selection;
                        person.changeAge(selection);
                        cout << endl << person.getInfo();
                    }
                    else
                    {
                        cout << "Invalid selection" << endl;;
                    }
                }   break;
            case 5:
                {
                    cout << "Enter current car registration: ";
                    string registration;
                    getchar();
                    getline(cin >> ws, registration);
                    int index = CarsRegister::findCarIndexByRegistration(registration);
                    if (index != -1)
                    {
                        Car & car = CarsRegister::getRegistrationByIndex(index);
                        cout << endl << car.getInfo()
                            << "Enter new registration: ";
                        getline(cin >> ws, registration);

                        cout << "Enter new person ID: ";
                        cin >> selection;
                        int person_index = CarsRegister::findPersonIndexByID(selection);
                        if (person_index != -1)
                        {
                            Person & person = CarsRegister::getPersonByIndex(person_index);
                            car.changeOwner(&person, registration);
                            cout << endl << car.getInfo();
                        }
                        else
                        {
                            cout << "Invalid selection" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid selection" << endl;
                    }
                }   break;
            case 6:
                {
                    cout << "Enter number of random persons to generate: ";
                    cin >> selection;
                    CarsRegister::generatePersons(selection);
                    cout << endl << "Created " << selection << " new persons." << endl;
                }   break;
            case 7:
                {
                    cout << "Enter number of random registrations to generate: ";
                    cin >> selection;
                    CarsRegister::generateCarRegistrations(selection);
                    cout << endl << "Created " << selection << " new registrations." << endl;
                }   break;
            case 8:
                {
                    cout << "Enter a name: ";
                    string name;
                    getline(cin >> ws, name);
                    cout << "Enter age: ";
                    int age;
                    cin >> age;
                    Person * person = CarsRegister::addPerson(name, age);
                    cout << endl << person->getInfo();
                }   break;
            case 9:
                {
                    string manufacturer, model, registration_number;
                    int horsepower, person_id;
                    cout << "Enter car manufacturer: ";
                    getline(cin >> ws, manufacturer);

                    cout << "Enter car model: ";
                    getline(cin >> ws, model);

                    cout << "Enter car horsepower: ";
                    cin >> horsepower;

                    cout << "Enter car registration number: ";
                    getline(cin >> ws, registration_number);

                    cout << "Enter person ID: ";
                    cin >> person_id;

                    int person_index = CarsRegister::findPersonIndexByID(person_id);
                    if (person_index != -1)
                    {
                        Person & person = CarsRegister::getPersonByIndex(person_index);
                        Car * car = CarsRegister::addCarRegistration(manufacturer, model,
                                                horsepower, &person, registration_number);
                        cout << endl << car->getInfo();
                    }
                    else
                    {
                        cout << "Invalid selection" << endl;
                    }
                }   break;
            case 10:
                {
                    cout << endl << CarsRegister::getSystemInfo();
                }   break;
            case 11:
                {
                    string file_name;
                    cout << "Enter file name: ";
                    getline(cin >> ws, file_name);
                    CarsRegister::savePersonsInfoToFile(file_name);
                }   break;
            case 12:
                {
                    string file_name;
                    cout << "Enter file name: ";
                    getline(cin >> ws, file_name);
                    CarsRegister::saveRegistrationsInfoToFile(file_name);
                }   break;
            case 13:
                {
                    CarsRegister::clearGlobalData();
                    cout << "Cleared Persons and Registrations data." << endl;
                }   break;
            case 14:
                {
                    string file_name;
                    cout << "Enter file name: ";
                    getline(cin >> ws, file_name);
                    CarsRegister::saveAllDataToFile(file_name);
                }   break;
            default:    break;
        }
    }

    return 0;
}
