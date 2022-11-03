#pragma once

#include "Resource.hpp"
#include <cstring>
#include <iostream>

class ResourceManager
{
private:
    Resource* r;

public:
    ResourceManager() { r = new Resource; }
    ResourceManager(const ResourceManager& resource_men)
        : r{(Resource*)memcpy(new Resource, resource_men.r, sizeof(*resource_men.r))}
    {
        //  std::cout << "konstruktor kopiujajacy\n";
    }

    ~ResourceManager() { delete r; }

    ResourceManager& operator=(const ResourceManager& reMen)
    {
        // std::cout << "przypisanie\n";
        if (&reMen == this) {
            return *this;
        }
        delete r;
        r = (Resource*)memcpy(new Resource, reMen.r, sizeof(*reMen.r));

        return *this;
    }

    double get() { return r->get(); }
};
