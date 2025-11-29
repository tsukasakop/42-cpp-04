#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "=== Testing basic functionality ===" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j; // should not create a leak
	delete i;

	std::cout << "\n\n=== Testing array of Animals ===" << std::endl;
	const int arraySize = 10;
	Animal* animals[arraySize];

	std::cout << "--- Creating Dogs ---" << std::endl;
	for (int idx = 0; idx < arraySize / 2; idx++) {
		animals[idx] = new Dog();
	}

	std::cout << "\n--- Creating Cats ---" << std::endl;
	for (int idx = arraySize / 2; idx < arraySize; idx++) {
		animals[idx] = new Cat();
	}

	std::cout << "\n--- Deleting all animals ---" << std::endl;
	for (int idx = 0; idx < arraySize; idx++) {
		delete animals[idx];
	}

	std::cout << "\n\n=== Testing deep copy for Dog ===" << std::endl;
	Dog* originalDog = new Dog();
	originalDog->getBrain()->setIdea(0, "I want to chase cats");
	originalDog->getBrain()->setIdea(1, "I love bones");

	std::cout << "\n--- Creating copy of Dog ---" << std::endl;
	Dog* copiedDog = new Dog(*originalDog);

	std::cout << "\n--- Verifying deep copy (modifying original) ---" << std::endl;
	originalDog->getBrain()->setIdea(0, "I want to sleep");
	
	std::cout << "Original Dog idea[0]: " << originalDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied Dog idea[0]: " << copiedDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied Dog idea[1]: " << copiedDog->getBrain()->getIdea(1) << std::endl;

	if (originalDog->getBrain()->getIdea(0) != copiedDog->getBrain()->getIdea(0)) {
		std::cout << "SUCCESS: Deep copy working correctly!" << std::endl;
	} else {
		std::cout << "FAILURE: Shallow copy detected!" << std::endl;
	}

	std::cout << "\n--- Verifying Brain addresses are different ---" << std::endl;
	std::cout << "Original Dog Brain address: " << originalDog->getBrain() << std::endl;
	std::cout << "Copied Dog Brain address: " << copiedDog->getBrain() << std::endl;

	std::cout << "\n--- Deleting Dogs ---" << std::endl;
	delete originalDog;
	delete copiedDog;

	std::cout << "\n\n=== Testing deep copy for Cat ===" << std::endl;
	Cat* originalCat = new Cat();
	originalCat->getBrain()->setIdea(0, "I want to hunt mice");

	std::cout << "\n--- Creating copy of Cat ---" << std::endl;
	Cat* copiedCat = new Cat(*originalCat);

	std::cout << "\n--- Verifying deep copy (modifying original) ---" << std::endl;
	originalCat->getBrain()->setIdea(0, "I want to nap");
	
	std::cout << "Original Cat idea[0]: " << originalCat->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied Cat idea[0]: " << copiedCat->getBrain()->getIdea(0) << std::endl;

	if (originalCat->getBrain()->getIdea(0) != copiedCat->getBrain()->getIdea(0)) {
		std::cout << "SUCCESS: Deep copy working correctly!" << std::endl;
	} else {
		std::cout << "FAILURE: Shallow copy detected!" << std::endl;
	}

	std::cout << "\n--- Deleting Cats ---" << std::endl;
	delete originalCat;
	delete copiedCat;

	std::cout << "\n\n=== Testing assignment operator ===" << std::endl;
	Dog dog1;
	dog1.getBrain()->setIdea(0, "Dog1's idea");
	
	Dog dog2;
	dog2.getBrain()->setIdea(0, "Dog2's idea");
	
	std::cout << "Before assignment - dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;
	dog2 = dog1;
	std::cout << "After assignment - dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;
	
	std::cout << "\n--- Modifying dog1 after assignment ---" << std::endl;
	dog1.getBrain()->setIdea(0, "Modified idea");
	std::cout << "dog1 idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
	std::cout << "dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;

	if (dog1.getBrain()->getIdea(0) != dog2.getBrain()->getIdea(0)) {
		std::cout << "SUCCESS: Assignment creates deep copy!" << std::endl;
	} else {
		std::cout << "FAILURE: Assignment creates shallow copy!" << std::endl;
	}

	return 0;
}
