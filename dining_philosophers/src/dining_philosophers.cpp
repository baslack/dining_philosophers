#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include "Barrier.hpp"

#define kDEBUG true
#define kFULL 10
#define kSUPPRESS false

class Utensil {
public:
	Utensil(void);
	Utensil(const Utensil &);
	~Utensil(void);
	bool acquire(void);
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
	std::cout << "Starting dinner." << std::endl;
	// set the table
	std::vector<Utensil> utensils;
	for (int i = 0; i < argc-1; i++) {
		utensils.push_back(Utensil());
	}
	Barrier bar(argc-1);
	// seat the diners
	std::vector<Philosopher> diners;
	for (int i = 0; i < argc - 1; i++) {
		diners.push_back(Philosopher(argv[i + 1], utensils[i], utensils[(i + 1) % (argc - 1)]));
	}
	// start the meal
	std::vector<std::thread> threads;
	for (int i = 0; i < argc - 1; i++) {
		threads.push_back(std::thread(run, std::ref(diners[i]), std::ref(bar)));
	}
	// clean up the table
	for (int i = 0; i < argc - 1; i++) {
		threads[i].join();
	}
	std::cout << "Dinner ends." << std::endl;
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
	if (!kSUPPRESS) {
		printf("%s eats some food.\n", this->name.c_str());
	}
	// std::cout << this->name << " eats some food." << std::endl;
}

void Philosopher::talk(void)
{
	this->talked++;
	if (!kSUPPRESS) {
		printf("%s talks a lot.\n", this->name.c_str());
	}
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

void Utensil::release(void)
{
	lock.unlock();
}

void run(Philosopher &phil, Barrier &barrier)
{
	if (!kSUPPRESS) {
		printf("%s takes his seat.\n", phil.name.c_str());
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
	if (!kSUPPRESS) {
		printf("%s sits and smokes.\n", phil.name.c_str());
	}
	// std::cout << phil.name << " ate " << phil.ate << " times and talked " << phil.talked << "." << std::endl;
	printf("%s ate %d times and talked %d\n", phil.name.c_str(), phil.ate, phil.talked);
}
