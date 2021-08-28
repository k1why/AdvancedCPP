
/*
Ослабление правил замещения для виртуальных функций.
Разрешены преобразования из A*->B*, так же A&->B& (когда B наследник A)
Запрещены: A->B, B->A, B*->A*, int*->void*, int->double и тд.
*/


struct A {
    virtual A* clone() { return new A; }
};

struct B : A {
    virtual B* clone() { return new B; }
};

int main()
{
    A a;
    B b;
    
    A* a_ptr = a.clone();
    B* error_ab_ptr = a.clone(); // error: invalid conversion from ‘A*’ to ‘B*’
    
    A* b_ptr = b.clone();
    B* ab_ptr = b.clone();

    return 0;
}