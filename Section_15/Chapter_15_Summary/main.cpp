#include <iostream>

#include "Random.h"

class Monster {
public:
	enum Type {
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,
		maxMonsterTypes,
	};

	Monster(const Type type, const std::string_view name, const std::string_view roar, const int hitPoints)
		: m_type{type}
		, m_name{name}
		, m_roar{roar}
		, m_hitPoints{hitPoints} {
	}

	constexpr std::string_view getTypeString() const;

	void print() const;

private:
	Type m_type{};
	std::string m_name{"???"};
	std::string m_roar{"???"};
	int m_hitPoints{};
};

constexpr std::string_view Monster::getTypeString() const {
	switch (m_type) {
		case dragon:	return "dragon";
		case goblin:	return "goblin";
		case ogre:		return "ogre";
		case orc:		return "orc";
		case skeleton:	return "skeleton";
		case troll:		return "troll";
		case vampire:	return "vampire";
		case zombie:	return "zombie";
		default:		return "???";
	}
}

void Monster::print() const {
	std::cout  << m_name << " the " << getTypeString();

	if (m_hitPoints <= 0) {
		std::cout << " is dead.\n";
	} else {
		std::cout << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
	}
}

namespace MonsterGenerator {
	constexpr std::string_view getName(const int num) {
		switch (num) {
			case 0:			return "Bob";
			case 1:			return "Sam";
			case 2:			return "Olga";
			case 3:			return "Terry";
			case 4:			return "Penelope";
			case 5:			return "Cantaloupe";
			default:		return "???";
		}
	}

	constexpr std::string_view getRoar(const int num) {
		switch (num) {
			case 0:			return "zibzibzib";
			case 1:			return "whaaaaaah";
			case 2:			return "beeboobeeboo";
			case 3:			return "wokkaflocka";
			case 4:			return "meow";
			case 5:			return "rawr";
			default:		return "???";
		}
	}

	Monster generate() {
		return Monster {
			static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes - 1)),
			getName(Random::get(0, 5)),
			getRoar(Random::get(0, 5)),
			Random::get(1, 100)
		};
	}
}

int main()
{
	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
	skeleton.print();

	Monster vampire{ Monster::vampire, "Nibblez", "*hiss*", 0 };
	vampire.print();

	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}