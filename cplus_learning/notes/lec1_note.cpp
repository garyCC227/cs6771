/*********
 * Lecture 1 notes...
*/ 

/**** references
 * def: point to a object, 
 * 1. Cant change what they refer to once set
 * 2. dont need ->
 * 3. cannot be null

 * - reference to a const.
*/
int i = 1;
const int& ref = i;
i++; // this is fine,
ref++; // not fine.  const int&  you know it!

const int j = 1;
const int& ref = j; // allow 
int& ref = j; // not allow