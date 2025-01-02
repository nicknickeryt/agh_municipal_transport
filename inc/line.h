#pragma once

#include <vector>
#include "route.h"

using std::vector;

class Line {
private:
    int lineNumber;
    std::vector<Route> lineRoutes;

public:
    Line(int number, const vector<Route>& routes);
    Line(int number);

    void addRoute(const Route& route);
    std::vector<Route> getRoutes() const;
    int getLineNumber() const;

};