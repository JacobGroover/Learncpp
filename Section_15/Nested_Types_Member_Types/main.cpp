#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
	using IDType = int;

	class Printer
	{
	public:
		void print(const Employee& e) const
		{
			// Printer can't access Employee's `this` pointer
			// so we can't print m_name and m_id directly
			// Instead, we have to pass in an Employee object to use
			// Because Printer is a member of Employee,
			// we can access private members e.m_name and e.m_id directly
			std::cout << e.m_name << " has id: " << e.m_id << '\n';
		}
	};

private:
	std::string m_name{};
	IDType m_id{};
	double m_wage{};

public:
	Employee(std::string_view name, IDType id, double wage)
		: m_name{ name }
	, m_id{ id }
	, m_wage{ wage }
	{
	}

	// removed the access functions in this example (since they aren't used)
};

// A nested type can be forward declared within the class that encloses it. The nested type can then be defined later,
// either within the enclosing class, or outside of it. For example:
class outer
{
public:
	class inner1;   // okay: forward declaration inside the enclosing class okay
	class inner1{}; // okay: definition of forward declared type inside the enclosing class
	class inner2;   // okay: forward declaration inside the enclosing class okay
};

class inner2 // okay: definition of forward declared type outside the enclosing class
{
};

// However, a nested type cannot be forward declared prior to the definition of the enclosing class.

int main()
{
	const Employee john{ "John", 1, 45000 };
	const Employee::Printer p{}; // instantiate an object of the inner class
	p.print(john);

	return 0;
}