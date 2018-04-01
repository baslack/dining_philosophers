/*
Benjamin A. Slack
03.29.2018
CS5541
Dining Philosphers

Description:
Implements the dining philosphers problem, somewhat literally.
Implementation sans starvaation and deadlock.
*/

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include "Barrier.hpp"

#define kDEBUG true
#define kFULL 10
#define kSUPPRESS true
#define kEATMAX 2000
#define kEATMIN 500
#define kTALKMAX 1000
#define kTALKMIN 250
#define kNAPKINMAX 3000
#define kNAPKINMIN 1000

bool bSuppress = kSUPPRESS;

// Needed a thread safe random 
// https://stackoverflow.com/questions/21237905/how-do-i-generate-thread-safe-uniform-random-numbers
int intRand(const int & min, const int & max) {
	std::random_device r;
	static thread_local std::mt19937 generator(r());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

class Utensil {
public:
	Utensil(void);
	Utensil(const Utensil &);
	~Utensil(void);
	bool acquire(void);
	bool takeNhold(void);
	void release(void);
	std::mutex lock;
};

class Philosopher {
public:
	Philosopher(std::string, Utensil &, Utensil &);
	~Philosopher();
	unsigned int talked;
	unsigned int ate;
	std::string name;
	Utensil &left;
	Utensil &right;
	void eat(void);
	void talk(void);
};

void run(Philosopher &, Barrier &);

int main(int argc, char **argv)
{
	//parse args

	std::vector<std::string> args;
	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	args.erase(args.cbegin());

	for (auto iter = args.cbegin(); iter != args.cend(); iter++) {
		if (*iter == "-h") {
			std::cout << "Usage: [-h] [-v] [...]\n";
			exit(EXIT_SUCCESS);
		}
	}

	for (auto iter = args.cbegin(); iter != args.cend(); iter++) {
		if (*iter == "-v") {
			bSuppress = false;
			args.erase(iter);
			break;
		}
	}

	std::cout << "Starting dinner." << std::endl << std::endl;
	// set the table
	std::vector<Utensil> utensils;
	for (size_t i = 0; i < args.size(); i++) {
		utensils.push_back(Utensil());
	}
	Barrier bar(args.size());
	// seat the diners
	std::vector<Philosopher> diners;
	for (size_t i = 0; i < args.size(); i++) {
		diners.push_back(Philosopher(args[i], utensils[i], utensils[(i + 1) % (args.size())]));
	}
	// start the meal
	std::vector<std::thread> threads;
	for (size_t i = 0; i < args.size(); i++) {
		threads.push_back(std::thread(run, std::ref(diners[i]), std::ref(bar)));
	}
	// clean up the table
	for (size_t i = 0; i < args.size(); i++) {
		threads[i].join();
	}
	std::cout << "Dinner ends." << std::endl << std::endl;
	exit(EXIT_SUCCESS);
}

Philosopher::Philosopher(\
	std::string name, \
	Utensil &left, \
	Utensil &right): name(name), left(left), right(right)
{
	ate = 0;
	talked = 0;
}

Philosopher::~Philosopher()
{
}

void Philosopher::eat(void)
{
	this->ate++;
	if (!bSuppress) {
		printf("%s eats some food.\n\n", this->name.c_str());
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(intRand(kEATMIN, kEATMAX)));

	// std::cout << this->name << " eats some food." << std::endl;
}

void Philosopher::talk(void)
{
	this->talked++;
	if (!bSuppress) {
		printf("%s talks a lot.\n\n", this->name.c_str());
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(intRand(kTALKMIN, kTALKMAX)));

	// std::cout << this->name << " talks a lot." << std::endl;
}

Utensil::Utensil(void):lock()
{
}

Utensil::Utensil(const Utensil &other) : lock()
{	
}

Utensil::~Utensil(void)
{
}

bool Utensil::acquire(void)
{
	return lock.try_lock();
}

bool Utensil::takeNhold(void)
{
	lock.lock();
	return true;
}

void Utensil::release(void)
{
	lock.unlock();
}

void run(Philosopher &phil, Barrier &barrier)
{
	if (!bSuppress) {
		printf("%s takes his seat.\n\n", phil.name.c_str());
	}
	barrier.Wait();
	while (phil.ate < kFULL) {
		bool hasLeft = false;
		hasLeft = phil.left.acquire();
		bool hasRight = false;
		hasRight = phil.right.acquire();
		if (hasLeft && hasRight) {
			phil.eat();
			phil.left.release();
			phil.right.release();
			// timeout to prevent starvation of other threads
			if (!bSuppress) {
				printf("%s dabs his or her mouth with a napkin.\n\n", phil.name.c_str());
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(intRand(kNAPKINMIN, kNAPKINMAX)));
		}
		else {
			if (hasLeft) {
				phil.left.release();
			}
			if (hasRight) {
				phil.right.release();
			}
			phil.talk();
		}
	} // end while
	// std::cout << phil.name << " sits and smokes his (or her) pipe." << std::endl;
	if (!bSuppress) {
		printf("%s sits and smokes.\n\n", phil.name.c_str());
	}
	barrier.Wait();
	// std::cout << phil.name << " ate " << phil.ate << " times and talked " << phil.talked << "." << std::endl;
	printf("%s ate %d times and talked %d\n\n", phil.name.c_str(), phil.ate, phil.talked);
}
