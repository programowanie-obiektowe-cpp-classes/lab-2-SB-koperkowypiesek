#pragma once

#include "Resource.hpp"
#include <cstring>
#include <iostream>

class ResourceManager
{
private:
    // wskaznik na obiekt Resource:
    Resource* pointer_to_resource;
    // licznik resource menedzerow odnoszacych sie do tego samego obiektu Resource:
    int* pointer_to_counter;

public:
    ResourceManager()
    {
        // domyslny konstruktor tworzy obiekt Resource:
        pointer_to_resource = new Resource;
        // tworzy tez nowy licznik Resource menedzerow dla tego obiektu:
        pointer_to_counter = new int;
        // licznik inicjalizuje 1 (na razie istnieje tylko ten jeden Resource menedzer):
        *pointer_to_counter = 1;
    }
    ResourceManager(const ResourceManager& rm_in) : pointer_to_resource{rm_in.pointer_to_resource}
    {
        // Kostruktor kopiujacy ma dzialac na tym samym obiekcie Resource co zmienna wejsciowa
        // wiec pointer_to_resource zostal zainicjalizowany wartoscia pointer_to_resource obiektu
        // przyjmowanego (rm_in)

        // skoro nowy menedzer dziala na tym samym obiekcie Resource ma tez ten sam licznik
        // aktywnych menadzerow:
        pointer_to_counter = rm_in.pointer_to_counter;
        // nalezy zwiekszyc licznik menedzerow dzialajacych na tej samej pamieci (ten sam obiekt
        // Resource):
        *pointer_to_counter += 1;
    }

    ~ResourceManager()
    {
        // jesli jest aktywny tylko jeden menedzer dla danego obiektu Resource to mozna go usunac
        if (*pointer_to_counter == 1) {
            std::cout << "zabijam ResourseMen. Pozostale aktywne: " << *pointer_to_counter - 1
                      << "\n";
            delete pointer_to_resource;
            delete pointer_to_counter;
        }
        // Jesli nie jest to jedyny meneder dla tego Resource zmniejsz counter:
        else {

            std::cout << "zabijam ResourseMen. Pozostale aktywne: " << *pointer_to_counter - 1
                      << "\n";
            *pointer_to_counter -= 1;
        }
    }

    ResourceManager& operator=(const ResourceManager& rm_in)
    {
        //  jesli przypisyjemy menedzer dzialajacy na tym samym obiekcie Resource nic nie
        //  zmieniaj:
        if (pointer_to_resource == rm_in.pointer_to_resource) {
            return *this;
        }
        //  jesli menedzer jest jedynym dzialajacym na danym obiekcie zdealokuj pamiec:
        if (*pointer_to_counter == 1) {
            delete pointer_to_resource;
            delete pointer_to_counter;
        }
        // jesli menedzer nie jest jedyny zmniejsz counter:
        else {
            (*pointer_to_counter)--;
        }
        // przepisz wskazniki z wejsciowego obiektu:
        pointer_to_counter = rm_in.pointer_to_counter;
        ++(*pointer_to_counter);
        pointer_to_resource = rm_in.pointer_to_resource;
        return *this;
    }

    // dostep do metody obiektu Resource
    double get() { return pointer_to_resource->get(); }
};

// class ResourceManager
// {
// private:
//     Resource* pointer_to_resource;

// public:
//     ResourceManager() { pointer_to_resource = new Resource; }
//     ResourceManager(const ResourceManager& rm_in)
//         : pointer_to_resource{(Resource*)memcpy(new Resource, rm_in.pointer_to_resource,
//         sizeof(*rm_in.pointer_to_resource))}
//     {
//     }

//     ~ResourceManager() { delete pointer_to_resource; }

//     ResourceManager& operator=(const ResourceManager& rm_in)
//     {
//         if (&rm_in == this) {
//             return *this;
//         }
//         delete pointer_to_resource;
//         pointer_to_resource = (Resource*)memcpy(new Resource, rm_in.pointer_to_resource,
//         sizeof(*rm_in.pointer_to_resource));

//         return *this;
//     }

//     double get() { return pointer_to_resource->get(); }
// };
