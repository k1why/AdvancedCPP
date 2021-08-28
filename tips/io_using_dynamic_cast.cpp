#include <map>
#include <fstream>
#include <iostream>
#include <type_traits>

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

struct io_circle : circle, io_object
{
    io_circle(std::ifstream&)
    {
        //create from file    
    }

    virtual io_circle* clone() override
    {
        return new io_circle(*this);
    }

    static io_object* create_circle(std::ifstream& s)
    {
        return new io_circle(s);
    }
};

struct io_triangle : triangle, io_object
{
    io_triangle(std::ifstream&)
    {
        //create from file    
    }

    virtual io_triangle* clone() override
    {
        return new io_triangle(*this);
    }

    static io_object* create_triangle(std::ifstream& s)
    {
        return new io_triangle(s);
    }
};

//object creator
using creator_t = std::add_pointer<io_object* (std::ifstream&)>::type;
std::map<std::string, creator_t> io_map = {
    {"circle", &io_circle::create_circle},
    {"triangle", &io_triangle::create_triangle}
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
}


int main()
{
    user_func();
    return 0;
}
