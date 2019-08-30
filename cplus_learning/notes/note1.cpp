// -------c++ data type:
//  - short int (2 bytes)
//  - int (4)
//  - char (1)
//  - long int(similar to int)
//  - float (4)
//  - double(8)
//  - wchar_t(2 or 4 bytes)
//  - and unsigned int ...

/******************
 * "::" - scope resolution
 * 1. use to access global variables (useful when there is a local variable has the same name)
 * 2.define a function outside of class.  like
 *  class A{
 *
 * }
 * then you can defind like:
 * void A::fun(){
 * }
 * 3.!!!!access global variables. ACCESS!!
 */


 /************
  *  namespace - keyword
  *
  * A namespace is designed to overcome this difficulty and is used as additional
  * information to differentiate similar functions, classes, variables etc. with the same name available in different libraries.
  * Using namespace, you can define the context in which names are defined. In essence, a namespace defines a scope.
  *
    * // first name space
    namespace first_space {
    void func() {
        cout << "Inside first_space" << endl;
    }
    }

    // second name space
    namespace second_space {
    void func() {
        cout << "Inside second_space" << endl;
    }
    }

    int main () {
    // Calls function from first name space.
    first_space::func();

    // Calls function from second name space.
    second_space::func();

    return 0;
    }
  *
  */

 /*************************
  constexpr - constant as well, but will be evaulate in complier time.
 */

//********* range base for loop( have range)
// for(int a:{1,2,3,4,5}){
//   a = 0;
// }
