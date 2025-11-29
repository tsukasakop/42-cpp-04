#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include "TestUtils.hpp"
#include <iomanip>

template <typename T>
void showInstanceInfo(const std::string name, const T& animal) {
	std::cout << name << std::endl;
	std::cout << " - typeid: " << typeid(animal).name() << std::endl;
	std::cout << " - Type  : " << animal.getType() << std::endl;
	std::cout << " - Sound : ";
	animal.makeSound();
	std::cout << std::endl;
}

void showBrainIdeas(const Brain* brain) {
	std::cout << " - Brain Address: " << brain << std::endl;
	std::cout << " - Brain Ideas: " << std::endl;
	for (int i = 0; i < 100; ++i) {
		if (!brain->getIdea(i).empty()) {
			std::cout << "  [" << i << "]: " << brain->getIdea(i) << std::endl;
		}
	}
	std::cout << std::endl;
}

int main()
{
	{
		std::cout << "=== CASE0: Testing constructor/destructor ===" << std::endl;
		TestUtils::execOrthodoxCanonicalFormFunctions<Animal>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Cat>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Dog>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Brain>();
	}
	{
		std::cout << "=== CASE1: Testing correct polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Animal &cat = Cat();
		const Animal &dog = Dog();
		const Animal &animal = Animal();
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const Animal &cat = Cat();", cat);
			showInstanceInfo("const Animal &dog = Dog();", dog);
			showInstanceInfo("const Animal &animal = Animal();", animal);
		}
	}
	{
		std::cout << "=== CASE2: Testing empty brain ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Cat cat;
		const Brain* catBrain = cat.getBrain();
		const Dog dog;
		const Brain* dogBrain = dog.getBrain();
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const Cat cat;", cat);
			showBrainIdeas(catBrain);
			showInstanceInfo("const Dog dog;", dog);
			showBrainIdeas(dogBrain);
		}
	}
	{
		std::cout << "=== CASE3: Testing tiny brain ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		Cat cat;
		Brain* catBrain = cat.getBrain();
		catBrain->setIdea(0, "I want fish.");
		catBrain->setIdea(1, "I want to play.");
		Dog dog;
		Brain* dogBrain = dog.getBrain();
		dogBrain->setIdea(99, "I want a walk.");
		dogBrain->setIdea(50, "I want to fetch the ball.");
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const Cat cat;", cat);
			showBrainIdeas(catBrain);
			showInstanceInfo("const Dog dog;", dog);
			showBrainIdeas(dogBrain);
		}
	}
	{
		std::cout << "=== CASE3: Testing deep copy ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		Cat cat;
		cat.getBrain()->setIdea(0, "I want fish.");
		const Cat clone(cat);
		cat.getBrain()->setIdea(0, "I want beef.");
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const Cat cat;", cat);
			showBrainIdeas(cat.getBrain());
			showInstanceInfo("const Cat &clone = cat;", clone);
			showBrainIdeas(clone.getBrain());
		}
	}
	{
		std::cout << "=== CASE4: Testing memory leak ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		{
			const int numAnimals = 100;
			Animal* animals[numAnimals];
			for (int i = 0; i < numAnimals; i++) {
				if (i % 2 == 0) {
					animals[i] = new Cat();
				} else {
					animals[i] = new Dog();
				}
			}
			for (int i = 0; i < numAnimals; i++) {
				delete animals[i];
			}
		}
	}
	return 0;
}
