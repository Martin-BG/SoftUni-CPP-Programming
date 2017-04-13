#include<iostream>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include<ctime>
#include<sstream>

#define REFRESH_RATE (0.1)

namespace DynaBlaster {

using std::string;
using std::vector;
using std::cout;

class Vector2D {
public:
    int x;
    int y;

    Vector2D()
    : x(0)
    , y(0)
    { }

    Vector2D(double x, double y)
    : x(x)
    , y(y)
    { }

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(this->x + other.x, this->y + other.y);
    }

    Vector2D& operator+=(const Vector2D& other) {
        *this = (*this) + other;
        return *this;
    }

    Vector2D operator*(const double & factor) const {
        return Vector2D(this->x * factor, this->y * factor);
    }

    Vector2D& operator*=(const double & factor) {
        *this = (*this) * factor;
        return *this;
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(this->x - other.x, this->y - other.y);
    }

    Vector2D& operator-=(const Vector2D& other) {
        *this = (*this) - other;
        return *this;
    }

    Vector2D operator/(const double & factor) const {
        return Vector2D(this->x / factor, this->y / factor);
    }

    Vector2D& operator/=(const double & factor) {
        *this = (*this) / factor;
        return *this;
    }

    bool operator==(const Vector2D & other) const {
        return (this->x == other.x) && (this->y == other.y);
    }

    bool operator!=(const Vector2D & other) const {
        return !((*this) == other);
    }
};

class GameObject {
protected:
    GameObject * owner = nullptr;
    Vector2D position;

    GameObject(Vector2D position)
    : owner(nullptr)
    , position(position)
    { }

    GameObject(Vector2D position, GameObject * owner)
    : owner(owner)
    , position(position)
    { }

public:
    Vector2D getPosition() const {
        return this->position;
    }

    bool hasType(const string & type) const {
        return this->getType().find(type) != string::npos;
    }

    GameObject * getOwner() const {
        return this->owner;
    }

    virtual void handleOwnedObjectDestroyed(const GameObject * object) {
    }

    virtual string getType() const = 0;
    virtual vector<GameObject*> update(vector<const GameObject*> allObjects) = 0;
    virtual void interact(const GameObject * other) = 0;
    virtual bool isActive() const = 0;

    static vector<const GameObject*> getObjectsAtPosition(Vector2D position, const vector<const GameObject*> & objects) {
        vector<const GameObject*> objectsAtPosition;

        for (const GameObject * object : objects) {
            if (object->getPosition() == position) {
                objectsAtPosition.push_back(object);
            }
        }

        return objectsAtPosition;
    }

    virtual ~GameObject() {
    }
};

class MovingObject : public GameObject {
protected:
    Vector2D movement;

    MovingObject(Vector2D position)
    : GameObject(position)
    { }
private:
    void move() {
        this->position += movement;
    }

public:
    bool canMove(Vector2D newPosition, vector<const GameObject*> allObjects) const {
        for (const GameObject * object : allObjects) {
            if (object->getPosition() == newPosition && !this->canMoveToPositionOf(object)) {
                return false;
            }
        }

        return true;
    }

    virtual vector<GameObject*> update(vector<const GameObject*> allObjects) {
        Vector2D targetPosition = this->getPosition() + movement;
        if (targetPosition != this->getPosition() && this->canMove(targetPosition, allObjects)) {
            this->move();
        }

        return vector<GameObject*>();
    }

    virtual string getType() const {
        return "moving";
    }

    virtual bool canMoveToPositionOf(const GameObject* other) const = 0;
};

class LivingObject : public MovingObject {
protected:
    bool isAlive;

    LivingObject(Vector2D position)
    : MovingObject(position)
    , isAlive(true)
    { }
public:
    virtual bool isActive() const {
        return this->isAlive;
    }

    virtual void interact(const GameObject * other) {
        for (const string & type : this->getDeathCausingTypes()) {
            if (other->hasType(type)) {
                this->isAlive = false;
            }
        }
    }

    virtual string getType() const {
        return MovingObject::getType() + " living";
    }
protected:
    virtual vector<string> getDeathCausingTypes() const {
        vector<string> causes;
        causes.push_back("fire");
        return causes;
    }
};

class StaticObject : public GameObject {
protected:
    StaticObject(Vector2D position, GameObject * owner)
    : GameObject(position, owner)
    { }
public:
    virtual string getType() const {
        return "static";
    }

    virtual vector<GameObject*> update(vector<const GameObject*> allObjects) {
        return vector<GameObject*>();
    }

    virtual void interact(const GameObject& other) {
    }

    virtual bool isActive() const {
        return true;
    }
};

class DestroyableObject : public StaticObject {
protected:
    bool isDestroyed;

    DestroyableObject(Vector2D position, GameObject * owner)
    : StaticObject(position, owner)
    , isDestroyed(false)
    { }

    virtual void interact(const GameObject * other) {
        if (other->hasType("fire")) {
            this->isDestroyed = true;
        }
    }

    virtual string getType() const {
        return StaticObject::getType() + " destroyable";
    }

    virtual bool isActive() const {
        return !this->isDestroyed;
    }
};

class Fire : public DestroyableObject {
public:
    Fire(Vector2D position)
    : DestroyableObject(position, nullptr)
    { }

    // NOTE: Fire will self-destruct, due to the check in DestroyableObject

    virtual string getType() const {
        return StaticObject::getType() + " fire";
    }

    static vector<const GameObject*> getBarriers(const vector<const GameObject*> objects) {
        vector<const GameObject*> barriers;
        for (const GameObject * object : objects) {
            if (object->hasType("brick") || object->hasType("concrete") || object->hasType("bomb")) {
                barriers.push_back(object);
            }
        }

        return barriers;
    }

    static bool containsIndestructible(const vector<const GameObject*> objects) {
        for (const GameObject * object : objects) {
            if (object->hasType("concrete")) {
                return true;
            }
        }

        return false;
    }
};

class BrickWall : public DestroyableObject {
public:
    BrickWall(Vector2D position)
    : DestroyableObject(position, nullptr)
    { }

    virtual string getType() const {
        return StaticObject::getType() + " brick";
    }
};

class ConcreteWall : public StaticObject {
public:
    ConcreteWall(Vector2D position)
    : StaticObject(position, nullptr)
    { }

    virtual string getType() const {
        return StaticObject::getType() + " concrete";
    }

    virtual void interact(const GameObject * other) {
    }
};

class Bomb : public DestroyableObject {
protected:
    int range;
    int timeLeft;
public:
    Bomb(Vector2D position, int range, GameObject * owner)
    : DestroyableObject(position, owner)
    , range(range)
    , timeLeft(5 / REFRESH_RATE)
    { }

    virtual void interact(const GameObject * other) {
        DestroyableObject::interact(other);
        if (this->isDestroyed && timeLeft >= 1) {
            this->isDestroyed = false;
            this->timeLeft = 1;
        }
    }

    virtual vector<GameObject*> update(vector<const GameObject*> allObjects) {
        vector<GameObject*> produced = DestroyableObject::update(allObjects);

        timeLeft--;
        if (timeLeft <= 0) {
            this->isDestroyed = true;
            vector<GameObject*> explosion = this->explode(allObjects);
            produced.insert(produced.begin(), explosion.begin(), explosion.end());
        }

        return produced;
    }

    virtual string getType() const {
        return StaticObject::getType() + " bomb";
    }
private:
    vector<GameObject*> explode(vector<const GameObject*> allObjects) {
        vector<GameObject*> explosion;

        vector<GameObject*> upExplosion = produceExplosion(Vector2D(0, 1), this->range, allObjects);
        vector<GameObject*> rightExplosion = produceExplosion(Vector2D(1, 0), this->range, allObjects);
        vector<GameObject*> downExplosion = produceExplosion(Vector2D(0, -1), this->range, allObjects);
        vector<GameObject*> leftExplosion = produceExplosion(Vector2D(-1, 0), this->range, allObjects);

        explosion.insert(explosion.end(), upExplosion.begin(), upExplosion.end());
        explosion.insert(explosion.end(), rightExplosion.begin(), rightExplosion.end());
        explosion.insert(explosion.end(), downExplosion.begin(), downExplosion.end());
        explosion.insert(explosion.end(), leftExplosion.begin(), leftExplosion.end());
        explosion.push_back(new Fire(this->getPosition()));

        return explosion;
    }

    vector<GameObject*> produceExplosion(Vector2D directionStep, int range, vector<const GameObject*> allObjects) {
        vector<GameObject*> explosion;
        for(int i = 1; i <= range; i++) {
            Vector2D currentPosition = this->getPosition() + directionStep * i;

            vector<const GameObject*> objectsAtFirePosition = GameObject::getObjectsAtPosition(currentPosition, allObjects);
            vector<const GameObject*> barriers = Fire::getBarriers(objectsAtFirePosition);

            if (barriers.empty()) {
                explosion.push_back(new Fire(currentPosition));
            } else {
                if (!Fire::containsIndestructible(barriers)) {
                    explosion.push_back(new Fire(currentPosition));
                }
                break;
            }
        }

        return explosion;
    }
};

class Creep : public LivingObject {
    int turnsSinceDirectionChange;
protected:
    Creep(Vector2D position)
    : LivingObject(position)
    , turnsSinceDirectionChange(0)
    { }

public:
    virtual vector<GameObject*> update(vector<const GameObject*> allObjects) {
        vector<GameObject*> produced = LivingObject::update(allObjects);

        // give a higher probability of changing direction for each turn where a change didn't happen
        turnsSinceDirectionChange++;
        if(rand() % 10 < turnsSinceDirectionChange) {
            this->randomizeDirection();
            turnsSinceDirectionChange = 0;
        }

        return produced;
    }

    virtual string getType() const {
        return LivingObject::getType() + " creep";
    }
protected:
    virtual void randomizeDirection() {
        int x = 0;
        int y = 0;

        int & movementDimension(rand() % 2 ? x : y);
        movementDimension = rand() % 3 - 1;
        this->movement = Vector2D(x, y);
    }
};

class Ghost : public Creep {
protected:
    virtual bool canMoveToPositionOf(const GameObject* other) const {
        return !other->hasType("concrete") && !other->hasType("bomb");
    }
public:
    Ghost(Vector2D position)
    : Creep(position)
    { }

    virtual string getType() const {
        return Creep::getType() + " ghost";
    }
};

class Blob : public Creep {
protected:
    virtual bool canMoveToPositionOf(const GameObject* other) const {
        return other->hasType("living");
    }
public:
    Blob(Vector2D position)
    : Creep(position)
    { }

    virtual string getType() const {
        return Creep::getType() + " blob";
    }
};

class Player : public LivingObject {
private:
    int numBombsAvailable;
    int numBombsDropped;

    int bombRange;

    bool bombArmed;
public:
    const int playerNumber;

    Player(Vector2D position, int playerNumber)
    : LivingObject(position)
    , numBombsAvailable(8)
    , numBombsDropped(0)
    , bombRange(2)
    , bombArmed(false)
    , playerNumber(playerNumber)
    { }

    void goUp() {
        this->movement = Vector2D(0, 1);
    }

    void goDown() {
        this->movement = Vector2D(0, -1);
    }

    void goLeft() {
        this->movement = Vector2D(-1, 0);
    }

    void goRight() {
        this->movement = Vector2D(1, 0);
    }

    void dropBomb() {
        if (this->numBombsAvailable > this->numBombsDropped) {
            this->bombArmed = true;
        }
    }

    virtual vector<GameObject*> update(vector<const GameObject*> allObjects) {
        vector<GameObject*> produced = LivingObject::update(allObjects);
        this->movement = Vector2D();

        if (bombArmed) {
            bool hasObjectsAtSamePosition = GameObject::getObjectsAtPosition(this->getPosition(), allObjects).size() > 1;

            if (!hasObjectsAtSamePosition) {
                produced.push_back(new Bomb(getPosition(), this->bombRange, this));
                numBombsDropped++;
            }

            this->bombArmed = false;
        }

        return produced;
    }

    virtual string getType() const {
        return LivingObject::getType() + " player";
    }

    virtual vector<string> getDeathCausingTypes() const {
        vector<string> causes = LivingObject::getDeathCausingTypes();
        causes.push_back("creep");
        return causes;
    }

    virtual void handleOwnedObjectDestroyed(const GameObject * object) {
        if (object->hasType("bomb")) {
            this->numBombsDropped--;
        }
    }
protected:
    virtual bool canMoveToPositionOf(const GameObject * other) const {
        return false;
    }
};

class InputReader {
public:
    virtual bool inputPresent() = 0;
    virtual char readInputCode() = 0;
};

class WindowsConsoleInputHandler : public InputReader {
public:
    bool inputPresent() {
        return _kbhit();
    }

    char readInputCode() {
        return _getch();
    }
};

class InputHandler {
    InputReader & reader;
    Player & player1;
    Player & player2;
public:
    InputHandler(InputReader & reader, Player & player1, Player & player2)
    : reader(reader)
    , player1(player1)
    , player2(player2)
    { }

    void handleInput() {
        if (reader.inputPresent()) {
            switch(reader.readInputCode()) {
                case 'a': player1.goLeft(); break;
                case 'd': player1.goRight(); break;
                case 'w': player1.goUp(); break;
                case 's': player1.goDown(); break;
                case 'f': player1.dropBomb(); break;

                case 'j': player2.goLeft(); break;
                case 'l': player2.goRight(); break;
                case 'i': player2.goUp(); break;
                case 'k': player2.goDown(); break;
                case 'p': player2.dropBomb(); break;
            }
        }
    }
};

class GameState {
    vector<GameObject*> objects;
public:
    GameState(vector<GameObject*> objects)
    : objects(objects)
    { }

    void setObjects(vector<GameObject*> objects) {
        this->objects = objects;
    }

    const vector<GameObject*>& getObjects() const {
        return objects;
    }

    const Player * getWinner() const {
        const Player * lastLivingPlayer = nullptr;
        for (const GameObject * object : this->objects) {
            if (object->hasType("player")) {
                if (lastLivingPlayer != nullptr) {
                    // more than 1 living player, so no winner;
                    return nullptr;
                } else {
                    lastLivingPlayer = dynamic_cast<const Player*>(object);
                }
            }
        }

        return lastLivingPlayer;
    }
};

class Renderer {
public:
    virtual void render(const GameState & gameState) = 0;
};

class WindowsConsoleRenderer : public Renderer {
    const int rows;
    const int cols;
public:
    WindowsConsoleRenderer(int rows, int cols)
    : rows(rows)
    , cols(cols)
    { }

    void render(const GameState & gameState) {
        using std::endl;
        char renderMatrix[rows][cols];

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                renderMatrix[row][col] = ' ';
            }
        }

        for(GameObject * object : gameState.getObjects()) {
            Vector2D position = translateToScreenRowCol(object->getPosition());

            renderMatrix[position.x][position.y] = getRenderSymbol(object);
        }

        std::ostringstream output;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                output << renderMatrix[row][col];
            }
            output << endl;
        }

        system("cls");
        cout << output.str();
    }

private:
    Vector2D translateToScreenRowCol(Vector2D coords) {
        return Vector2D((rows - 1) - coords.y, coords.x);
    }

    char getRenderSymbol(const GameObject* object) {
        if (object->hasType("player")) {
            const Player * p = dynamic_cast<const Player*>(object);
            return '0' + p->playerNumber;
        } else if (object->hasType("ghost")) {
            return '&';
        } else if (object->hasType("blob")) {
            return 'O';
        } else if (object->hasType("bomb")) {
            return '@';
        } else if (object->hasType("fire")) {
            return '*';
        } else if (object->hasType("brick")) {
            return '.';
        } else if (object->hasType("concrete")) {
            return '#';
        } else {
            return '?';
        }
    }
};

}

int main() {
    using namespace DynaBlaster;

    const int GridSize = 31;

    std::vector<GameObject*> objects;
    Player * p1 = new Player(Vector2D(1, (GridSize - 1) - 1), 1);
    objects.push_back(p1);
    Player * p2 = new Player(Vector2D((GridSize - 1) - 1, 1), 2);
    objects.push_back(p2);
    objects.push_back(new Blob(Vector2D(2, 1)));

    for (int i = 1; i < GridSize - 1; i++) {
        objects.push_back(new ConcreteWall(Vector2D(0, i)));
        objects.push_back(new ConcreteWall(Vector2D(i, 0)));
        objects.push_back(new ConcreteWall(Vector2D(i, GridSize - 1)));
        objects.push_back(new ConcreteWall(Vector2D(GridSize - 1, i)));
    }

    for (int y = 1; y < GridSize - 1; y++) {
        bool onPlayerRow = (y < 2 || y > GridSize - 3);
        for (int x = onPlayerRow ? 3 : 1; x < GridSize - (onPlayerRow ? 3 : 1); x++) {
            if (x % 2 == 0 && y % 2 == 0) {
                continue;
            }

            int brickProbability = 50;
            int creepProbability = 1;

            int random = rand() % 100;
            if (random < brickProbability) {
                objects.push_back(new BrickWall(Vector2D(x, y)));
            } else if (random < brickProbability + creepProbability) {
                objects.push_back(rand() % 2 ? (GameObject*) new Blob(Vector2D(x, y)) : (GameObject*) new Ghost(Vector2D(x, y)));
            }
        }
    }

    for (int x = 2; x < GridSize - 1; x+=2) {
        for (int y = 2; y < GridSize - 1; y+=2) {
            objects.push_back(new ConcreteWall(Vector2D(x, y)));
        }
    }



    Renderer * renderer = new WindowsConsoleRenderer(GridSize, GridSize);
    InputReader * inputReader = new WindowsConsoleInputHandler();

    GameState gameState(objects);
    InputHandler inputHandler(*inputReader, *p1, *p2);

    while(gameState.getWinner() == nullptr) {
        clock_t ticksStart = clock();
        inputHandler.handleInput();

        std::vector<const GameObject*> constObjects(gameState.getObjects().begin(), gameState.getObjects().end());

        std::vector<GameObject*> objectsAfterIteration;
        std::vector<GameObject*> inactiveObjects;
        for (GameObject * object : gameState.getObjects()) {
            std::vector<GameObject*> currentProduced = object->update(constObjects);

            for (const GameObject * otherObject : GameObject::getObjectsAtPosition(object->getPosition(), constObjects)) {
                object->interact(otherObject);
            }

            if (object->isActive()) {
                objectsAfterIteration.push_back(object);
            } else {
                if (object->getOwner() != nullptr) {
                    object->getOwner()->handleOwnedObjectDestroyed(object);
                }

                inactiveObjects.push_back(object);
            }

            objectsAfterIteration.insert(objectsAfterIteration.end(), currentProduced.begin(), currentProduced.end());
        }

        gameState.setObjects(objectsAfterIteration);

        for (GameObject * object : inactiveObjects) {
            delete object;
        }

        renderer->render(gameState);

        while(clock() - ticksStart < REFRESH_RATE * CLOCKS_PER_SEC) {
        }
    }

    return 0;
}
