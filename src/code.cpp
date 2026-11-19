// ============================================================
// CSCI 232 Assignment 07 – Shapes, Polymorphism and Insertion Sort
// Student Implementation
// ============================================================

#include "code.hpp"
#include <iostream>
#include <iterator>
#include <numbers>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Terren Foster";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Shape, Circle, Square, Rectangle
// ============================================================

/// True if THIS shape has a strictly smaller area() than other.
bool Shape::operator<(const Shape &other) const
{
    // TODO: compare area() of both shapes with <
    return area() < other.area();
}

/// Constructor with a member initializer list.
Circle::Circle(double newRadius)
    : radius(newRadius)
{
    // TODO: move the initialization of 'radius' into an initializer list
}

/// pi * radius * radius, use std::numbers::pi
double Circle::area() const
{
    // TODO: implement
    return std::numbers::pi * radius * radius;
}

/// Return exactly "Circle".
std::string Circle::name() const
{
    // TODO: implement
    return "Circles";
}

Square::Square(double newSide)
    : side(newSide)
{
    // TODO: initializer list
}

/// side * side
double Square::area() const
{
    // TODO: implement
    return side * side;
}

/// Return exactly "Square".
std::string Square::name() const
{
    // TODO: implement
    return "Square";
}

Rectangle::Rectangle(double newWidth, double newHeight)
    : width(newWidth), height(newHeight)
{
    // TODO: initializer list
}

/// width * height
double Rectangle::area() const
{
    // TODO: implement
    return width * height;
}

/// Return exactly "Rectangle".
std::string Rectangle::name() const
{
    // TODO: implement
    return "Rectangle";
}

// ============================================================
// PART 2: ShapeList
// ============================================================

/// RAII: delete EVERY shape, then clear the list.
ShapeList::~ShapeList()
{
    // TODO: implement
    for (Shape * shape : data)
    {
        delete shape;
    }
    data.clear();
}

/// Append at the end. Return -1 if newShapePtr is nullptr, 0 on success.
int ShapeList::addShape(Shape *newShapePtr)
{
    // TODO: implement
    if (newShapePtr == nullptr)
    {
        return -1;
    }
    data.push_back(newShapePtr);
    return 0;
}

/// Delete the first shape and remove it from the list.
/// Return false if the list is empty, true otherwise.
bool ShapeList::removeFirst()
{
    // TODO: implement
    if (data.empty())
    {
        return false;
    }
    delete data.front();
    data.pop_front();
    return true;
}

/// Number of shapes in the list.
int ShapeList::length() const
{
    // TODO: implement
    return data.size();
}

/// Sum of area() of all shapes (0.0 if empty).
double ShapeList::totalArea() const
{
    // TODO: implement
    double total = 0.0;
    for (Shape* shape : data)
    {
        total += shape->area();
    }
    return total;
}

/// One line per shape: name, one space, area. Return the number of shapes.
int ShapeList::printList() const
{
    // TODO: implement
    for (Shape* shape : data)
    {
        std::cout << shape->name() << " " << shape->area() << "\n";
    }
    return data.size();
}

/// area() of the shape at index, or std::nullopt if index is out of range.
/// Hint: std::next(data.begin(), index)
std::optional<double> ShapeList::areaAt(int index) const
{
    // TODO: implement
    if (index < 0 || index >= data.size())
    {
        return std::nullopt;
    }
    auto it = std::next(data.begin(), index);
    return (*it)->area();
}

/// name() of the shape at index, or std::nullopt if index is out of range.
std::optional<std::string> ShapeList::nameAt(int index) const
{
    // TODO: implement
    if (index < 0 || index >= data.size())
    {
        return std::nullopt;
    }
    auto it = std::next(data.begin(), index);
    return (*it)->name();
}

/// Your own STABLE insertion sort, smallest area first.
/// Compare shapes with operator< (dereference the pointers!).
/// Hint: for every element, walk left while the previous shape is bigger,
/// then move the element there with data.splice(...).
void ShapeList::insertionSort()
{
    // TODO: implement
    if (data.size() < 2)
    {
        return;
    }
    auto it = std::next(data.begin());
    while (it != data.end())
    {
        auto current = it++;
        auto pos = current;
        while (pos != data.begin())
        {
            auto prev = std::prev(pos);
            if (!(**current < ** prev))
            {
                break;
            }
            pos = prev;
        }
        data.splice(pos, data, current);
    }
}

/// True if no shape is smaller than the one before it.
bool ShapeList::isSorted() const
{
    if (data.size() <= 1)
    {
        return true;
    }
    auto prev = data.begin();
    auto current = std::next(data.begin());
    while (current != data.end())
    {
        if (**current < **prev)
        {
            return false;
        }
        ++prev;
        ++current;
    }
    return true;
   
}
