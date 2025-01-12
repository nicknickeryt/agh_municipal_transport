#include "app.h"
#include "utils.h"

int main() {
  App &app = App::getInstance();

  app.loadData();
  app.run();
}
