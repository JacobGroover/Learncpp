// NOTE: A friend function should prefer to use the class interface over direct access whenever possible.

// NOTE: Prefer to implement a function as a non-friend when possible and reasonable.

/*
A friend function is a function (member or non-member) that can access the private and protected members of a
class as though it were a member of that class. In all other regards, the friend function is a normal function.

Let’s take a look at an example of a simple class making a non-member function a friend:
 */

// #include <iostream>
//
// class Accumulator
// {
// private:
// 	int m_value { 0 };
//
// public:
// 	void add(int value) { m_value += value; }
//
// 	// Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
// 	friend void print(const Accumulator& accumulator);
// };
//
// void print(const Accumulator& accumulator)
// {
// 	// Because print() is a friend of Accumulator
// 	// it can access the private members of Accumulator
// 	std::cout << accumulator.m_value;
// }
//
// int main()
// {
// 	Accumulator acc{};
// 	acc.add(5); // add 5 to the accumulator
//
// 	print(acc); // call the print() non-member function
//
// 	return 0;
// }

/*
Although you might assume that because print() is defined inside Accumulator, that makes print() a member of
Accumulator, this is not the case. Because print() is defined as a friend, it is instead treated as a non-member
function (as if it had been defined outside Accumulator).
 */

/*
In the introduction to this lesson, we mentioned that there were times we might prefer to use a non-member function
over a member function. Let’s show an example of that now:
 */

// #include <iostream>
//
// class Value
// {
// private:
//  int m_value{};
//
// public:
//  explicit Value(int v): m_value { v }  { }
//
//  bool isEqualToMember(const Value& v) const;
//  friend bool isEqualToNonmember(const Value& v1, const Value& v2);
// };
//
// bool Value::isEqualToMember(const Value& v) const
// {
//  return m_value == v.m_value;
// }
//
// bool isEqualToNonmember(const Value& v1, const Value& v2)
// {
//  return v1.m_value == v2.m_value;
// }
//
// int main()
// {
//  Value v1 { 5 };
//  Value v2 { 6 };
//
//  std::cout << v1.isEqualToMember(v2) << '\n';
//  std::cout << isEqualToNonmember(v1, v2) << '\n';
//
//  return 0;
// }

/*
In this example, we’ve defined two similar functions that check whether two Value objects are equal. isEqualToMember()
is a member function, and isEqualToNonmember() is a non-member function. Let’s focus on how these functions are defined.

In isEqualToMember(), we’re passing one object implicitly and the other explicitly. The implementation of the function
reflects this, and we have to mentally reconcile that m_value belongs to the implicit object whereas v.m_value belongs
to the explicit parameter.

In isEqualToNonmember(), both objects are passed explicitly. This leads to better parallelism in the implementation of
the function, as the m_value member is always explicitly prefixed with an explicit parameter.

You may still prefer the calling syntax v1.isEqualToMember(v2) over isEqualToNonmember(v1, v2). But when we cover
operator overloading, we’ll see this topic come up again.
 */


// A function can be a friend of more than one class at the same time. For example, consider the following example:

#include <iostream>

class Humidity; // forward declaration of Humidity

class Temperature
{
private:
 int m_temp { 0 };
public:
 explicit Temperature(int temp) : m_temp { temp } { }

 friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed for this line
};

class Humidity
{
private:
 int m_humidity { 0 };
public:
 explicit Humidity(int humidity) : m_humidity { humidity } {  }

 friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity)
{
 std::cout << "The temperature is " << temperature.m_temp <<
    " and the humidity is " << humidity.m_humidity << '\n';
}

int main()
{
 Humidity hum { 10 };
 Temperature temp { 12 };

 printWeather(temp, hum);

 return 0;
}

/*
There are three things worth noting about this example. First, because printWeather() uses both Humidity and Temperature
equally, it doesn’t really make sense to have it be a member of either. A non-member function works better. Second,
because printWeather() is a friend of both Humidity and Temperature, it can access the private data from objects of
both classes. Finally, note the following line at the top of the example:

class Humidity;

This is a forward declaration for class Humidity. Class forward declarations serve the same role as function forward
declarations -- they tell the compiler about an identifier that will be defined later. However, unlike functions,
classes have no return types or parameters, so class forward declarations are always simply class ClassName
(unless they are class templates).

Without this line, the compiler would tell us it doesn’t know what a Humidity is when parsing the friend
declaration inside Temperature.
 */