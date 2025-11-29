#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "=== Testing abstract Animal class ===" << std::endl;
	std::cout << "Note: Cannot instantiate Animal directly (it's abstract)" << std::endl;
	
	// This should cause a compilation error if uncommented:
	// const Animal* meta = new Animal();
	
	std::cout << "\n=== Creating Dog and Cat through Animal pointers ===" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\n--- Type information ---" << std::endl;
	std::cout << "Dog type: " << j->getType() << std::endl;
	std::cout << "Cat type: " << i->getType() << std::endl;

	std::cout << "\n--- Making sounds ---" << std::endl;
	i->makeSound(); // will output the cat sound!
	j->makeSound(); // will output the dog sound!

	std::cout << "\n--- Deleting animals ---" << std::endl;
	delete j; // should not create a leak
	delete i;

	std::cout << "\n\n=== Testing array of Animals ===" << std::endl;
	const int arraySize = 6;
	Animal* animals[arraySize];

	std::cout << "--- Creating Dogs ---" << std::endl;
	for (int idx = 0; idx < arraySize / 2; idx++) {
		animals[idx] = new Dog();
	}

	std::cout << "\n--- Creating Cats ---" << std::endl;
	for (int idx = arraySize / 2; idx < arraySize; idx++) {
		animals[idx] = new Cat();
	}

	std::cout << "\n--- Making sounds from array ---" << std::endl;
	for (int idx = 0; idx < arraySize; idx++) {
		std::cout << "Animal[" << idx << "]: ";
		animals[idx]->makeSound();
	}

	std::cout << "\n--- Deleting all animals ---" << std::endl;
	for (int idx = 0; idx < arraySize; idx++) {
		delete animals[idx];
	}

	std::cout << "\n\n=== Testing deep copy ===" << std::endl;
	Dog* originalDog = new Dog();
	originalDog->getBrain()->setIdea(0, "Chase the mailman");
	originalDog->getBrain()->setIdea(1, "Dig a hole");

	std::cout << "\n--- Creating copy of Dog ---" << std::endl;
	Dog* copiedDog = new Dog(*originalDog);

	std::cout << "\n--- Verifying deep copy ---" << std::endl;
	originalDog->getBrain()->setIdea(0, "Sleep all day");
	
	std::cout << "Original Dog idea[0]: " << originalDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied Dog idea[0]: " << copiedDog->getBrain()->getIdea(0) << std::endl;

	if (originalDog->getBrain()->getIdea(0) != copiedDog->getBrain()->getIdea(0)) {
		std::cout << "SUCCESS: Deep copy working correctly!" << std::endl;
	}

	std::cout << "\n--- Deleting Dogs ---" << std::endl;
	delete originalDog;
	delete copiedDog;

	return 0;
}
