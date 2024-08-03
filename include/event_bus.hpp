#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "topic.hpp"
#include <memory>
#include <string>
#include <vector>

class EventBus {
    private:
        std::vector<std::shared_ptr<Topic>> topics; 

    public:
        EventBus();
        EventBus(std::vector<std::shared_ptr<Topic>>& topicsVector);
        void delTopic(const std::string & topicName); 
        void printTopics() const;
        void publish(const std::string &topicName, const std::string& message) const;
        void subscribe(const std::string &topicName, std::shared_ptr<ISubscriber>& subscriber);
        void unsubscribe(const std::string &topicName, std::shared_ptr<ISubscriber>& subscriber);
        void clearTopics();
        void clearSubscribers(const std::string &topicName);
        std::shared_ptr<Topic> create(const std::string& topicName);
        std::shared_ptr<Topic> getTopic(const std::string &topicName) const;         
};

#endif 
