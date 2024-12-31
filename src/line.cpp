#include "line.h"

using std::vector;

Line::Line(int number, const vector<Route>& routes)
    : lineNumber(number), lineRoutes(routes) {}

void Line::addRoute(const Route& route) {
    lineRoutes.push_back(route);
}

std::vector<Route>& Line::getRoutes() {
    return lineRoutes;
}

int Line::getLineNumber() const {
    return lineNumber;
}