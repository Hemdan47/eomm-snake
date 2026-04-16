#include <memory>
#include "../include/core/Application.h"

int main (int argc , const char* argv[]) {
    std::unique_ptr<Application> application = std::make_unique<Application>();
    application->run();
    return 0;
}