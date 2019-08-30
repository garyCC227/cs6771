
/*
protected: child can access
private: child cannot access
*/


/**** special memeber of a class */
/*
    - Default constructor	C::C();
    - Destructor	C::~C();
    - Copy constructor	C::C (const C&);
    - Copy assignment	C& operator= (const C&);
    - Move constructor	C::C (C&&);
    - Move assignment	C& operator= (C&&);

    - if we specify a constructor , the defualt constructor willnot work, if we
    want a default constructor, we have the declare and init it in the class.
    - ~destrucor, need to clean all the memory allocate in this class
    - copy : init memeory, and copy the object into the new memory
    - copy assignement: have a assign to some object that already init
    - move constructor: move A to B, and A lost its content.
    - move assignment: ?
*/

/**** friendship and inheritance */
/*
     friend function.  can access the protect and private member of the class.
*/

class Rectangle {
    int width, height;
  public:
    Rectangle() {}
    Rectangle (int x, int y) : width(x), height(y) {}
    int area() {return width * height;}
    friend Rectangle duplicate (const Rectangle&);
};

Rectangle duplicate (const Rectangle& param)
{
  Rectangle res;
  res.width = param.width*2;
  res.height = param.height*2;
  return res;
}

int main () {
  Rectangle foo;
  Rectangle bar (2,3);
  foo = duplicate (bar);
  cout << foo.area() << '\n';
  return 0;
}
/*
friend class. similar to friend fucntion, but you have put definition to access
*/
class Square;

class Rectangle {
    int width, height;
  public:
    int area ()
      {return (width * height);}
    void convert (Square a); // puta function to access its friend
};

class Square {
  friend class Rectangle;
  private:
    int side;
  public:
    Square (int a) : side(a) {}
};

void Rectangle::convert (Square a) {
  width = a.side;
  height = a.side;
}

int main () {
  Rectangle rect;
  Square sqr (4);
  rect.convert(sqr);
  cout << rect.area();
  return 0;
}


/* inheritance */
/*
    - format class derived_class_name : public parent_class_name{...}
    - not only public, we can also use private, protect, but pupolar is public

    - inherits every member except the following:
        - constuctor, destructor, assignment operator member
        - its friends, its private member

        - but anyway, when we call the constructor of the child, it will still call the base class constructor
         by default, we will call the base default constructor first, then the child constructor.
         unless we specify the special base constructor like this:

*/
class Mother {
  public:
    Mother ()
      { cout << "Mother: no parameters\n"; }
    Mother (int a)
      { cout << "Mother: int parameter\n"; }
};

class Daughter : public Mother {
  public:
    Daughter (int a)
      { cout << "Daughter: int parameter\n\n"; } // call Mother() first, then this constructor
};

class Son : public Mother {
  public:
    Son (int a) : Mother (a) // call Mother(a) first, then this constructor
      { cout << "Son: int parameter\n\n"; }
};

int main () {
  Daughter kelly(0);
  Son bud(0);

  return 0;
}

/* mutiple inheritance */
class Rectangle: public Polygon, public Output{ //逗号
    ...
}




/******* Polymorphism **/

/* Pointer to class and its child*/
/*
    Pointer is compatitable with class type, if the pointer to a base class that point
    to its children. the pointer can only access the memeber that child inheritent from its parent.
*/

class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
};

class Rectangle: public Polygon {
  public:
    int area()
      { return width*height; }
};

class Triangle: public Polygon {
  public:
    int area()
      { return width*height/2; }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon * ppoly1 = &rect;  // so this pointer can only access set_values(), but not area(). since the child didnt
                            // inheritent from it
  Polygon * ppoly2 = &trgl;
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  cout << rect.area() << '\n';
  cout << trgl.area() << '\n';
  return 0;
}

/* virtual member */
/*
    the member in the base class, can be redefined by its children. with the function name are the same
*/
class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area ()
      { return 0; }
};

class Rectangle: public Polygon {
  public:
    int area ()
      { return width * height; }
};

class Triangle: public Polygon {
  public:
    int area ()
      { return (width * height / 2); }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon poly;
  Polygon * ppoly1 = &rect;
  Polygon * ppoly2 = &trgl;
  Polygon * ppoly3 = &poly;
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  ppoly3->set_values (4,5);
  cout << ppoly1->area() << '\n';
  cout << ppoly2->area() << '\n';
  cout << ppoly3->area() << '\n';
  return 0;
}

/* abstract class - 不是很想用*/
/*
 some function can without definition, but the class cannot be instance like,
 Polygon mypolygon; // not working
*/

class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area (void) =0;
};

class Rectangle: public Polygon {
  public:
    int area (void)
      { return (width * height); }
};

class Triangle: public Polygon {
  public:
    int area (void)
      { return (width * height / 2); }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon * ppoly1 = &rect;
  Polygon * ppoly2 = &trgl;
  ppoly1->set_values (4,5);
  ppoly2->set_values (4,5);
  cout << ppoly1->area() << '\n';
  cout << ppoly2->area() << '\n';
  return 0;
}



/*
* Class style note
*/
----- remeber to self check for copy and move assignment
// 1. move constructor and assignement with noexcept
// 2. class and struct different at
//     - default of struct is public
//     - default of class is private
//     - but use struct for just little method
// 3. 'friend' generally is bad idea. but useful for related class, and nonmember operator overload
// 4. static data and function are shared for all the instances that have same class type
//     -   sometime, with good reason we can use it
// 5. explict: good good good
// 6.lvalue and rvalue:
//     lvalue - we care. so compiler not allow to change it
//     rvalue - we not care anymore, so compiler allow to change it
//     --- use std::move() .. change lvalue to rvalue
//
// 7.
