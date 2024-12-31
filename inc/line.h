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

    void addRoute(const Route& route);
    std::vector<Route>& getRoutes();
    int getLineNumber() const;

};