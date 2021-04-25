#include <iostream>
#include <random>
#include <future>
#include <memory>
#include <chrono>

#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */
template <typename T>
T MessageQueue<T>::receive() {
  std::unique_lock<std::mutex> uLock(_mutex);
  _cond.wait(uLock, [this] { return !_queue.empty(); });
  
  T msg = std::move(_queue.back());
  _queue.pop_back();

  return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::lock_guard<std::mutex> uLock(_mutex);
  
  _queue.clear();
  _queue.push_back(std::move(msg));
  _cond.notify_one();
}


/* Implementation of class "TrafficLight" */
TrafficLight::TrafficLight(){
  	_messageQueue = std::make_shared<MessageQueue<TrafficLightPhase>>();
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen() {
  
  while(true){
  	auto msg = _messageQueue->receive();
    if(msg == TrafficLightPhase::green){
    	return;
    }
  }
}

TrafficLightPhase TrafficLight::getCurrentPhase() {
    return _currentPhase;
}

void TrafficLight::simulate() {
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {  
  
  std::random_device rand_dev;
  std::mt19937 gen(rand_dev());
  std::uniform_int_distribution<int>  distr(4000, 6000);
  
  auto duration = distr(gen);
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  
  lastUpdate = std::chrono::system_clock::now();
  while(true){
  	std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    
    if(timeSinceLastUpdate >= duration){
    	if(_currentPhase == green){
    		_currentPhase = red;
        } else {
            _currentPhase = green;
        } 
		auto is_sent = std::async(&MessageQueue<TrafficLightPhase>::send, _messageQueue, std::move(_currentPhase)); 
        is_sent.wait();

        lastUpdate = std::chrono::system_clock::now();	      
    }

  }
}