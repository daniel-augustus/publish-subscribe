#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <string>

class ISubscriber {
    public:
        virtual ~ISubscriber() = default;
        virtual void update(const std::string& message) = 0;
};

#endif 
