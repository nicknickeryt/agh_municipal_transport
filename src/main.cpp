#include "utils.h"
#include "app.h"

int main() {
  App& app = App::getInstance();

  app.loadData(); 
  app.run();
}
