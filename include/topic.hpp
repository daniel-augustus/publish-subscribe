#ifndef TOPIC_H
#define TOPIC_H

#include "subscriber.hpp"
#include <memory>
#include <string>
#include <vector>

class Topic {
    private:
        std::string name;
        std::vector<std::shared_ptr<ISubscriber>> subscribers;
 
    public:
        explicit Topic(const std::string &topicName);
        std::string getName() const;
        void clear();
        bool anySubscriber();
        void addSubscriber(const std::shared_ptr<ISubscriber>& subscriber);
        void delSubscriber(const std::shared_ptr<ISubscriber>& subscriber);
        void notifySubscribers(const std::string &message) const;      
};

#endif 
