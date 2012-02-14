#include "level.hpp"
#include "monsterType.hpp"
#include "spawn.hpp"
#include <sstream>

Level::Level(int id, Game* game) : id(id), game(game)
{
    stringstream    s;
    string          line;
    s << "levels/" << id << ".lvl.txt";

    IFile   *definition = new AbstractFile;
    cout << "Loading level " << s.str();
    try {
        definition->open(s.str());
    } catch (std::exception *e) {
        stringstream    s2;
        s2 << "../../levels/" << id << ".lvl.txt";
        definition->open(s2.str());
    }


    stringstream    sizeS;
    sizeS << definition->getLine();
    sizeS >> len;
    cout << " (" << len << " blocks)" << endl;

    while ((line = definition->getLine()) != "")
    {
        string  monster;
        int  number;
        stringstream    ss;

        ss << line;
        ss >> monster >> number;
        cout << "Loading monster " << monster << " x" << number << endl;
        try {
            monsterList.push_back(new MonsterType(monster, number));
            for (int i = 0; i < number; i++)
                spawnList.push_back(new Spawn(monsterList.back(), *this));
        } catch (std::exception *e) {
            cerr << e->what() << endl;
            delete e;
        }
    }
    definition->close();
    delete definition;
    spawnList.sort(spawnSort);
}

Level::~Level()
{
    while (monsterList.size() > 0)
    {
        delete monsterList.front();
        monsterList.pop_front();
    }
    while (spawnList.size() > 0)
    {
        delete spawnList.front();
        spawnList.pop_front();
    }
}

int         Level::getId() const
{
    return (id);
}

Spawn*		Level::getNextSpawn(float maxPos)
{
	Spawn*	t;

	if (spawnList.empty())
		return (NULL);

	t = spawnList.front();
	if (t && t->getPos() <= maxPos)
	{
		spawnList.pop_front();
		return (t);
	}
	return (NULL);
}

Level::SpawnList&  Level::getSpawnList()
{
    return spawnList;
}

int    Level::getLen() const
{
    return len;
}

bool		spawnSort(Spawn* a, Spawn* b)
{
	return (a->getPos() < b->getPos());
}
