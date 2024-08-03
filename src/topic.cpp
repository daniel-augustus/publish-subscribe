#include "topic.hpp"
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

Topic::Topic(const std::string &topicName):  name(topicName) {}

std::string Topic::getName() const { return name; }

void Topic::clear() { subscribers_.clear(); }

bool Topic::anySubscriber() { return !subscribers_.empty(); }

void Topic::addSubscriber(const std::shared_ptr<ISubscriber>& subscriber) { subscribers_.push_back(subscriber); }

void Topic::delSubscriber(const std::shared_ptr<ISubscriber>& subscriber) {
    std::vector<std::shared_ptr<ISubscriber>>::iterator it = std::find(subscribers_.begin(), subscribers_.end(), subscriber);
    if (it != subscribers_.end()) {
        subscribers_.erase(it);
    }
}

void Topic::notifySubscribers(const std::string& message) const {
    for(const std::shared_ptr<ISubscriber>& subscriber : subscribers_) {
        subscriber->update(message);
    }
}
