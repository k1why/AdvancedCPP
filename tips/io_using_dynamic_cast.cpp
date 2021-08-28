#include <map>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <functional>

// Defined user/library classes (probably can't be changed)
struct triangle
{
    void print_triangle()
    {
        std::cout << "triangle" << std::endl;
    }
};
struct circle
{
    void print_circle()
    {
        std::cout << "circle" << std::endl;
    }
};



//Classes hierarchy for input circle/triangle from file, socket, etc.
struct io_object
{
    virtual io_object* clone() = 0;
};

template <typename T>
struct io : public T, io_object
{
    io(std::ifstream&);

    virtual io* clone() override
    {
        return new io(*this);
    }

    static io* create(std::ifstream& s)
    {
        return new io(s);
    }
};

using io_circle = io<circle>;
io_circle::io(std::ifstream& s)
{
    //create circle from file
}

using io_triangle = io<triangle>;
io_triangle::io(std::ifstream& s)
{
    //create triangle from file
}


//object factory
using old_creator_t = std::add_pointer<io_object* (std::ifstream&)>::type;
using creator_t = std::function<io_object* (std::ifstream&)>;

std::map<std::string, creator_t> io_map = {
    {"circle", &io_circle::create},
    {"triangle", &io_triangle::create}
};

io_object* get_object(std::ifstream& fs)
{
    std::string obj_name = [](auto& fs) {
        return "triangle";
    }(fs);

    if (auto it = io_map.find(obj_name); it != io_map.end())
    {
        return it->second(fs);
    }

    return nullptr;
}



// function used/created by user
void user_func()
{
    std::ifstream file;
    io_object* object = get_object(file);

    if (circle* c = dynamic_cast<circle*>(object))
    {
        c->print_circle();
    }
    else if (triangle* t = dynamic_cast<triangle*>(object))
    {
        t->print_triangle();
    }
    else
    {
        // handle error or other figure
    }

    if (object != nullptr)
    {
        delete object;
    }
}


int main()
{
    user_func();
    return 0;
}
