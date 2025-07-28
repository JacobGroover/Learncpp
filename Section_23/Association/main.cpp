/*
Because associations are a broad type of relationship, they can be implemented in many different ways.
However, most often, associations are implemented using pointers, where the object points at the associated object.

In general, you should avoid bidirectional associations if a unidirectional one will do,
as they add complexity and tend to be harder to write without making errors.

In this example, we’ll implement a bi-directional Doctor/Patient relationship, since it makes sense for
the Doctors to know who their Patients are, and vice-versa.
 */

#include <functional> // reference_wrapper
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// Since Doctor and Patient have a circular dependency, we're going to forward declare Patient
class Patient;

class Doctor
{
private:
	std::string m_name{};
	std::vector<std::reference_wrapper<const Patient>> m_patient{};

public:
	Doctor(std::string_view name) :
		m_name{ name }
	{
	}

	void addPatient(Patient& patient);

	// We'll implement this function below Patient since we need Patient to be defined at that point
	friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);

	const std::string& getName() const { return m_name; }
};

class Patient
{
private:
	std::string m_name{};
	std::vector<std::reference_wrapper<const Doctor>> m_doctor{}; // so that we can use it here

	// We're going to make addDoctor private because we don't want the public to use it.
	// They should use Doctor::addPatient() instead, which is publicly exposed
	void addDoctor(const Doctor& doctor)
	{
		m_doctor.push_back(doctor);
	}

public:
	Patient(std::string_view name)
		: m_name{ name }
	{
	}

	// We'll implement this function below to parallel operator<<(std::ostream&, const Doctor&)
	friend std::ostream& operator<<(std::ostream& out, const Patient& patient);

	const std::string& getName() const { return m_name; }

	// We'll friend Doctor::addPatient() so it can access the private function Patient::addDoctor()
	friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
	// Our doctor will add this patient
	m_patient.push_back(patient);

	// and the patient will also add this doctor
	patient.addDoctor(*this);
}

std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
{
	if (doctor.m_patient.empty())
	{
		out << doctor.m_name << " has no patients right now";
		return out;
	}

	out << doctor.m_name << " is seeing patients: ";
	for (const auto& patient : doctor.m_patient)
		out << patient.get().getName() << ' ';

	return out;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient)
{
	if (patient.m_doctor.empty())
	{
		out << patient.getName() << " has no doctors right now";
		return out;
	}

	out << patient.m_name << " is seeing doctors: ";
	for (const auto& doctor : patient.m_doctor)
		out << doctor.get().getName() << ' ';

	return out;
}

int main()
{
	// Create a Patient outside the scope of the Doctor
	Patient dave{ "Dave" };
	Patient frank{ "Frank" };
	Patient betsy{ "Betsy" };

	Doctor james{ "James" };
	Doctor scott{ "Scott" };

	james.addPatient(dave);

	scott.addPatient(dave);
	scott.addPatient(betsy);

	std::cout << james << '\n';
	std::cout << scott << '\n';
	std::cout << dave << '\n';
	std::cout << frank << '\n';
	std::cout << betsy << '\n';

	return 0;
}

/*
Sometimes objects may have a relationship with other objects of the same type. This is called a reflexive association.
A good example of a reflexive association is the relationship between a university course and its prerequisites
(which are also university courses).

This can lead to a chain of associations (a course has a prerequisite, which has a prerequisite, etc…)

Consider the simplified case where a Course can only have one prerequisite. We can do something like this:
 */

#include <string>
#include <string_view>

// class Course
// {
// private:
// 	std::string m_name{};
// 	const Course* m_prerequisite{};
//
// public:
// 	Course(std::string_view name, const Course* prerequisite = nullptr):
// 		m_name{ name }, m_prerequisite{ prerequisite }
// 	{
// 	}
//
// };

/*
In all of the previous cases, we’ve used either pointers or references to directly link objects together.
However, in an association, this is not strictly required. Any kind of data that allows you to link two objects
together suffices. In the following example, we show how a Driver class can have a unidirectional association
with a Car without actually including a Car pointer or reference member:
 */

#include <iostream>
#include <string>
#include <string_view>

// class Car
// {
// private:
// 	std::string m_name{};
// 	int m_id{};
//
// public:
// 	Car(std::string_view name, int id)
// 		: m_name{ name }, m_id{ id }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	int getId() const { return m_id; }
// };
//
// // Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
// // Because it's static, we don't need to allocate an object of type CarLot to use it
// namespace CarLot
// {
// 	Car carLot[4] { { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };
//
// 	Car* getCar(int id)
// 	{
// 		for (auto& car : carLot)
// 		{
// 			if (car.getId() == id)
// 			{
// 				return &car;
// 			}
// 		}
//
// 		return nullptr;
// 	}
// };
//
// class Driver
// {
// private:
// 	std::string m_name{};
// 	int m_carId{}; // we're associated with the Car by ID rather than pointer
//
// public:
// 	Driver(std::string_view name, int carId)
// 		: m_name{ name }, m_carId{ carId }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// 	int getCarId() const { return m_carId; }
// };
//
// int main()
// {
// 	Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17
//
// 	Car* car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot
//
// 	if (car)
// 		std::cout << d.getName() << " is driving a " << car->getName() << '\n';
// 	else
// 		std::cout << d.getName() << " couldn't find his car\n";
//
// 	return 0;
// }

/*
In the above example, we have a CarLot holding our cars. The Driver, who needs a car, doesn’t have a pointer to his
Car -- instead, he has the ID of the car, which we can use to get the Car from the CarLot when we need it.

In this particular example, doing things this way is kind of silly, since getting the Car out of the CarLot requires
an inefficient lookup (a pointer connecting the two is much faster). However, there are advantages to referencing
things by a unique ID instead of a pointer. For example, you can reference things that are not currently in memory
(maybe they’re in a file, or in a database, and can be loaded on demand). Also, pointers can take 4 or 8
bytes -- if space is at a premium and the number of unique objects is fairly low, referencing them by an 8-bit or
16-bit integer can save lots of memory.
 */