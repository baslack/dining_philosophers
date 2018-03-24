/**
	Stack Overflow implementation of Barrier, missing from C++ 11 STD
	https://stackoverflow.com/questions/24465533/implementing-boostbarrier-in-c11
 */
#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>

class Barrier {
public:
	explicit Barrier(std::size_t);
	void Wait(void);
private:
	std::mutex mMutex;
	std::condition_variable mCond;
	std::size_t mThreshold;
	std::size_t mCount;
	std::size_t mGeneration;
};

#endif // !BARRIER_H