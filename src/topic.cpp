#include "topic.hpp"
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

Topic::Topic(const std::string &topicName):  name(topicName) {}

std::string Topic::getName() const { return name; }

void Topic::clear() { subscribers.clear(); }

bool Topic::anySubscriber() { return !subscribers.empty(); }

void Topic::addSubscriber(const std::shared_ptr<ISubscriber>& subscriber) {
    subscribers.push_back(subscriber);
}

void Topic::delSubscriber(const std::shared_ptr<ISubscriber>& subscriber) {
    std::vector<std::shared_ptr<ISubscriber>>::iterator it = std::find(subscribers.begin(), subscribers.end(), subscriber);
    if (it != subscribers.end()) {
        subscribers.erase(it);
    }
}

void Topic::notifySubscribers(const std::string& message) const {
    for(const std::shared_ptr<ISubscriber>& subscriber : subscribers) {
        subscriber->update(message);
    }
}
