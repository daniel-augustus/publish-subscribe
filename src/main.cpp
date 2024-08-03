#include "event_bus.hpp"
#include <iostream>
#include <typeinfo>

class SubscriberA : public ISubscriber {
    public:
        void update(const std::string& message) override {
            std::cout << "Subscriber <" << typeid(*this).name() << "> got the message: " << message << std::endl; 
        }
};

class SubscriberB : public ISubscriber {
    public:
        void update(const std::string& message) override {
            std::cout << "Subscriber <" << typeid(*this).name() << "> got the message: " << message << std::endl; 
        }
};

int main() {
    std::shared_ptr<ISubscriber> subscriberA = std::make_shared<SubscriberA>();
    std::shared_ptr<ISubscriber> subscriberB = std::make_shared<SubscriberB>();
    std::unique_ptr<EventBus> bus = std::make_unique<EventBus>();
    
    bus->subscribe("C++", subscriberA);
    bus->subscribe("C++", subscriberB);
    bus->subscribe("Python", subscriberA);

    bus->publish("C++", "\nint main() {\n\tstd::cout << \"Hello World!\" << std::endl;\n\treturn 0\n};");
    bus->publish("Python", "\nprint(\"Hello World!\")");

    bus->unsubscribe("C++", subscriberB);
    bus->publish("C++", "\nint main() {\n\tstd::cout << \"Now only SubscriberA got a message!\" << std::endl;\n\treturn 0\n};");

    return 0;
}
