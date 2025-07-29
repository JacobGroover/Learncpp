// Use public inheritance unless you have a specific reason to do otherwise.

/*
Access specifier in base class			Access specifier when inherited publicly			Access specifier when inherited privately			Access specifier when inherited protectedly
Public									Public												Private												Protected
Private									Inaccessible										Inaccessible										Inaccessible
Protected								Protected											Private												Protected
 */

// Here’s an example showing how things work for public inheritance:

// class Base
// {
// public:
// 	int m_public {};
// protected:
// 	int m_protected {};
// private:
// 	int m_private {};
// };
//
// class Pub: public Base // note: public inheritance
// {
// 	// Public inheritance means:
// 	// Public inherited members stay public (so m_public is treated as public)
// 	// Protected inherited members stay protected (so m_protected is treated as protected)
// 	// Private inherited members stay inaccessible (so m_private is inaccessible)
// public:
// 	Pub()
// 	{
// 		m_public = 1; // okay: m_public was inherited as public
// 		m_protected = 2; // okay: m_protected was inherited as protected
// 		m_private = 3; // not okay: m_private is inaccessible from derived class
// 	}
// };
//
// int main()
// {
// 	// Outside access uses the access specifiers of the class being accessed.
// 	Base base;
// 	base.m_public = 1; // okay: m_public is public in Base
// 	base.m_protected = 2; // not okay: m_protected is protected in Base
// 	base.m_private = 3; // not okay: m_private is private in Base
//
// 	Pub pub;
// 	pub.m_public = 1; // okay: m_public is public in Pub
// 	pub.m_protected = 2; // not okay: m_protected is protected in Pub
// 	pub.m_private = 3; // not okay: m_private is inaccessible in Pub
//
// 	return 0;
// }

/*
Protected inheritance is the least common method of inheritance. It is almost never used, except in very
particular cases. With protected inheritance, the public and protected members become protected, and private
members stay inaccessible.
 */

/*
With private inheritance, all members from the base class are inherited as private. This means private
members are inaccessible, and protected and public members become private.

Note that this does not affect the way that the derived class accesses members inherited from its parent!
It only affects the code trying to access those members through the derived class.
 */

class Base
{
public:
	int m_public {};
protected:
	int m_protected {};
private:
	int m_private {};
};

class Pri: private Base // note: private inheritance
{
	// Private inheritance means:
	// Public inherited members become private (so m_public is treated as private)
	// Protected inherited members become private (so m_protected is treated as private)
	// Private inherited members stay inaccessible (so m_private is inaccessible)
public:
	Pri()
	{
		m_public = 1; // okay: m_public is now private in Pri
		m_protected = 2; // okay: m_protected is now private in Pri
		m_private = 3; // not okay: derived classes can't access private members in the base class
	}
};

int main()
{
	// Outside access uses the access specifiers of the class being accessed.
	// In this case, the access specifiers of base.
	Base base;
	base.m_public = 1; // okay: m_public is public in Base
	base.m_protected = 2; // not okay: m_protected is protected in Base
	base.m_private = 3; // not okay: m_private is private in Base

	Pri pri;
	pri.m_public = 1; // not okay: m_public is now private in Pri
	pri.m_protected = 2; // not okay: m_protected is now private in Pri
	pri.m_private = 3; // not okay: m_private is inaccessible in Pri

	return 0;
}

/*
Private inheritance can be useful when the derived class has no obvious relationship to the base class,
but uses the base class for implementation internally. In such a case, we probably don’t want the public
interface of the base class to be exposed through objects of the derived class (as it would be if we
inherited publicly).

In practice, private inheritance is rarely used.
 */