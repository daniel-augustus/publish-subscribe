#include "event_bus.hpp"
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

EventBus::EventBus() = default;

EventBus::EventBus(std::vector<std::shared_ptr<Topic>>& topicsVector) : topics(topicsVector) {}

void EventBus::delTopic(const std::string &topicName) {
    if(std::shared_ptr<Topic> topic = getTopic(topicName);  topic != nullptr) {
        topics.erase(std::remove(topics.begin(), topics.end(), topic), topics.end());
    }
}

void EventBus::printTopics() const {
    for(const std::shared_ptr<Topic>& topic : topics) {
        std::cout << "Topic: " << topic->getName() << "." << std::endl;
    }
}

void EventBus::publish(const std::string &topicName, const std::string& message) const {
    if(std::shared_ptr<Topic> topic = getTopic(topicName); topic != nullptr) {
        for(const std::shared_ptr<ISubscriber>& subscriber : topic->subscribers_) {
            subscriber->update(message);
        }
    }
}

void EventBus::subscribe(const std::string &topicName, std::shared_ptr<ISubscriber>& subscriber) {
    std::shared_ptr<Topic> topic = getTopic(topicName);
    if(!topic) {
        topic = std::make_shared<Topic>(topicName);
        topics.push_back(topic);
    }
    topic->addSubscriber(subscriber);
}

void EventBus::unsubscribe(const std::string &topicName, std::shared_ptr<ISubscriber>& subscriber) {
    if(std::shared_ptr<Topic> topic = getTopic(topicName); topic != nullptr) {
        topic->delSubscriber(subscriber);
    } 
}

void EventBus::clearTopics() { topics.clear(); }

void EventBus::clearSubscribers(const std::string &topicName) {
    if(std::shared_ptr<Topic> topic = getTopic(topicName); topic != nullptr) {
        topic->clear();
    }
}

std::shared_ptr<Topic> EventBus::getTopic(const std::string &topicName) const {
    std::vector<std::shared_ptr<Topic>>::const_iterator it = 
        std::find_if(topics.begin(), topics.end(), [&topicName](const std::shared_ptr<Topic>& topic) {
            return topic->getName() == topicName;
        });
    return it != topics.end() ? *it : nullptr;
}
