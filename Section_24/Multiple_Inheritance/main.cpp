// To use multiple inheritance, simply specify each base class (just like in single inheritance), separated by a comma.

// #include <string>
// #include <string_view>
//
// class Person
// {
// private:
// 	std::string m_name{};
// 	int m_age{};
//
// public:
// 	Person(std::string_view name, int age)
// 		: m_name{ name }, m_age{ age }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	int getAge() const { return m_age; }
// };
//
// class Employee
// {
// private:
// 	std::string m_employer{};
// 	double m_wage{};
//
// public:
// 	Employee(std::string_view employer, double wage)
// 		: m_employer{ employer }, m_wage{ wage }
// 	{
// 	}
//
// 	const std::string& getEmployer() const { return m_employer; }
// 	double getWage() const { return m_wage; }
// };
//
// // Teacher publicly inherits Person and Employee
// class Teacher : public Person, public Employee
// {
// private:
// 	int m_teachesGrade{};
//
// public:
// 	Teacher(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade)
// 		: Person{ name, age }, Employee{ employer, wage }, m_teachesGrade{ teachesGrade }
// 	{
// 	}
// };
//
// int main()
// {
// 	Teacher t{ "Mary", 45, "Boo", 14.3, 8 };
//
// 	return 0;
// }

/*
A mixin (also spelled “mix-in”) is a small class that can be inherited from in order to add properties to a class.
The name mixin indicates that the class is intended to be mixed into other classes, not instantiated on its own.

In the following example, the Box, Label, and Tooltip classes are mixins that we inherit from in order to create
a new Button class.
 */

// h/t to reader Waldo for this example
#include <string>

struct Point2D
{
	int x{};
	int y{};
};

class Box // mixin Box class
{
public:
	void setTopLeft(Point2D point) { m_topLeft = point; }
	void setBottomRight(Point2D point) { m_bottomRight = point; }
private:
	Point2D m_topLeft{};
	Point2D m_bottomRight{};
};

class Label // mixin Label class
{
public:
	void setText(const std::string_view str) { m_text = str; }
	void setFontSize(int fontSize) { m_fontSize = fontSize; }
private:
	std::string m_text{};
	int m_fontSize{};
};

class Tooltip // mixin Tooltip class
{
public:
	void setText(const std::string_view str) { m_text = str; }
private:
	std::string m_text{};
};

class Button : public Box, public Label, public Tooltip {}; // Button using three mixins

int main()
{
	Button button{};
	button.Box::setTopLeft({ 1, 1 });
	button.Box::setBottomRight({ 10, 10 });
	button.Label::setText("Submit");
	button.Label::setFontSize(6);
	button.Tooltip::setText("Submit the form to the server");
}

/*
You may be wondering why we use explicit Box::, Label::, and Tooltip:: scope resolution prefixes when this
isn’t necessary in most cases.

1. Label::setText() and Tooltip::setText() have the same prototype. If we called button.setText(), the compiler
would produce an ambiguous function call compilation error. In such cases, we must use the prefix to disambiguate
which version we want.

2. In non-ambiguous cases, using the mixin name provides documentation as to which mixin the function call applies
to, which helps make our code easier to understand.

3. Non-ambiguous cases may become ambiguous in the future if we add additional mixins. Using explicit prefixes
helps prevent this from occurring.
 */

/*
Because mixins are designed to add functionality to the derived class, not to provide an interface, mixins
typically do not use virtual functions (covered in the next chapter). Instead, if a mixin class needs to be
customized to work in a particular way, templates are typically used. For this reason, mixin classes are
often templatized.

Perhaps surprisingly, a derived class can inherit from a mixin base class using the derived class as a template
type parameter. Such inheritance is called Curiously Recurring Template Pattern (CRTP for short), which looks like this:
 */

// The Curiously Recurring Template Pattern (CRTP)

template <class T>
class Mixin
{
	// Mixin<T> can use template type parameter T to access members of Derived
	// via (static_cast<T*>(this))
	// https://en.cppreference.com/w/cpp/language/crtp.html
};

class Derived : public Mixin<Derived>
{
};