/*
A good rule of thumb is that each class should be built to accomplish a single task. That task should either be the
storage and manipulation of some kind of data (e.g. Point2D, std::string), OR the coordination of its members
(e.g. Creature). Ideally not both.

In this case of our example, it makes sense that Creature shouldn’t have to worry about how Points are implemented,
or how the name is being stored. Creature’s job isn’t to know those intimate details. Creature’s job is to worry
about how to coordinate the data flow and ensure that each of the class members knows what it is supposed to do.
It’s up to the individual classes to worry about how they will do it.
 */

#include <string>
#include <iostream>
#include "Creature.h"
#include "Point2D.h"

int main()
{
	std::cout << "Enter a name for your creature: ";
	std::string name;
	std::cin >> name;
	Creature creature{ name, { 4, 7 } };

	while (true)
	{
		// print the creature's name and location
		std::cout << creature << '\n';

		std::cout << "Enter new X location for creature (-1 to quit): ";
		int x{ 0 };
		std::cin >> x;
		if (x == -1)
			break;

		std::cout << "Enter new Y location for creature (-1 to quit): ";
		int y{ 0 };
		std::cin >> y;
		if (y == -1)
			break;

		creature.moveTo(x, y);
	}

	return 0;
}

/*
Variants on the composition theme

Although most compositions directly create their parts when the composition is created and directly destroy their
parts when the composition is destroyed, there are some variations of composition that bend these rules a bit.

For example:

A composition may defer creation of some parts until they are needed. For example, a string class may not create
a dynamic array of characters until the user assigns the string some data to hold.
A composition may opt to use a part that has been given to it as input rather than create the part itself.
A composition may delegate destruction of its parts to some other object (e.g. to a garbage collection routine).
The key point here is that the composition should manage its parts without the user of the composition needing to
manage anything.
 */

/*
Composition and class members

One question that new programmers often ask when it comes to object composition is, “When should I use a class member
instead of direct implementation of a feature?”. For example, instead of using the Point2D class to implement the
Creature’s location, we could have instead just added 2 integers to the Creature class and written code in the Creature
class to handle the positioning. However, making Point2D its own class (and a member of Creature) has a number of benefits:

1. Each individual class can be kept relatively simple and straightforward, focused on performing one task well.
This makes those classes easier to write and much easier to understand, as they are more focused. For example,
Point2D only worries about point-related stuff, which helps keep it simple.

2. Each class can be self-contained, which makes them reusable. For example, we could reuse our Point2D class in
a completely different application. Or if our creature ever needed another point (for example, a destination it
was trying to get to), we can simply add another Point2D member variable.

3. The outer class can have the class members do most of the hard work, and instead focus on coordinating the
data flow between the members . This helps lower the overall complexity of the outer class, because it can delegate
tasks to its members, who already know how to do those tasks. For example, when we move our Creature, it delegates
that task to the Point class, which already understands how to set a point. Thus, the Creature class does not have
to worry about how such things would be implemented.
 */