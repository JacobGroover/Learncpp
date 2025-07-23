
/*
This function calculates the equivalent index in a 1D array for accessing an element at position (row, col) in a 2D layout.

If each row has numberOfColumnsInArray columns, then:

- Row 0 starts at index 0
- Row 1 starts at index numberOfColumnsInArray
- Row 2 starts at 2 * numberOfColumnsInArray, etc.
- So (row * columns) + col gives the correct linear index.
 */
int getSingleIndex(int row, int col, int numberOfColumnsInArray)
{
	return (row * numberOfColumnsInArray) + col;
}

int main() {

	// Pointers to pointers have a few uses. The most common use is to dynamically allocate an array of pointers:

	// int** array { new int*[10] }; // allocate an array of 10 int pointers

	// This works just like a standard dynamically allocated array, except the array elements are of
	// type “pointer to integer” instead of integer.

	// Unlike a two dimensional fixed array, which can easily be declared like this:
	// int array[10][5];

	// Dynamically allocating a two-dimensional array is a little more challenging. You may be tempted to try something like this:
	// int** array { new int[10][5] }; // won’t work!

	// First, we allocate an array of pointers (as per above). Then we iterate through the array of pointers
	// and allocate a dynamic array for each array element. Our dynamic two-dimensional array is a dynamic
	// one-dimensional array of dynamic one-dimensional arrays!

	int** array { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
	for (int count { 0 }; count < 10; ++count)
		array[count] = new int[5]; // these are our columns

	// We can then access our array like usual:
	array[9][4] = 3; // This is the same as (array[9])[4] = 3;


	/*
	 With this method, because each array column is dynamically allocated independently, it’s
	 possible to make dynamically allocated two dimensional arrays that are not rectangular.
	 For example, we can make a triangle-shaped array:
	 */

int** array2 { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
	for (int count { 0 }; count < 10; ++count)
		array2[count] = new int[count+1]; // these are our columns

	// In the above example, note that array[0] is an array of length 1, array[1] is an array of length 2, etc…


	// Deallocating a dynamically allocated two-dimensional array using this method requires a loop as well:

	for (int count { 0 }; count < 10; ++count)
		delete[] array[count];
	delete[] array; // this needs to be done last

	/*
	Note that we delete the array in the opposite order that we created it (elements first, then the array itself).
	If we delete array before the array columns, then we’d have to access deallocated memory to delete the array
	columns. And that would result in undefined behavior.
	 */

	/*
	Because allocating and deallocating two-dimensional arrays is complex and easy to mess up, it’s often easier
	to “flatten” a two-dimensional array (of size x by y) into a one-dimensional array of size x * y:
	 */
	// Instead of this:
	int** array3 { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
	for (int count { 0 }; count < 10; ++count)
		array3[count] = new int[5]; // these are our columns

	// Do this:
	int *array4 { new int[50] }; // a 10x5 array flattened into a single array

	// Simple math can then be used to convert a row and column index for a rectangular two-dimensional array into a single index for a one-dimensional array:

	// set array[9,4] to 3 using our flattened array
	array4[getSingleIndex(9, 4, 5)] = 3;
	/*
	Writing the value 3 to the element in row 9, column 4 of a conceptual 2D array with 5 columns.
	index = 9 * 5 + 4 = 45 + 4 = 49, so this line assigns a value of 3 to array4[49], the last index in
	the conceptual 2D array.
	 */

	/*
	It’s also possible to declare a pointer to a pointer to a pointer:
	int*** ptrx3;

	This can be used to dynamically allocate a three-dimensional array. However, doing so would
	require a loop inside a loop, and is extremely complicated to get correct.

	We recommend avoiding using pointers to pointers unless no other options are available, because they’re
	complicated to use and potentially dangerous. It’s easy enough to dereference a null or dangling pointer
	with normal pointers — it’s doubly easy with a pointer to a pointer since you have to do a double-dereference
	to get to the underlying value!
	 */


	return 0;
}
