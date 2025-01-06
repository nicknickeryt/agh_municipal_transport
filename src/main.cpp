#include "demo.h"
#include "utils.h"
#include "app.h"

using namespace std;

int main() {
  #ifdef DEMO
  Demo();
  #endif

  App& app = App::getInstance();

  app.setDemoData();
  app.run();

}
