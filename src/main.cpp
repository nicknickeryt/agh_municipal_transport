#include "utils.h"
#include "app.h"

using namespace std;

int main() {
  App& app = App::getInstance();
  
  app.loadData(); 
  app.run();
}
