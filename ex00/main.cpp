#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "=== Testing correct polymorphism ===" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n--- Type information ---" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	
	std::cout << "\n--- Making sounds ---" << std::endl;
	i->makeSound(); // will output the cat sound!
	j->makeSound();
	meta->makeSound();
	
	std::cout << "\n--- Deleting animals ---" << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << "\n\n=== Testing wrong polymorphism ===" << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();
	
	std::cout << "\n--- Type information ---" << std::endl;
	std::cout << wrongCat->getType() << " " << std::endl;
	
	std::cout << "\n--- Making sounds (should output WrongAnimal sound) ---" << std::endl;
	wrongCat->makeSound(); // will output the WrongAnimal sound!
	wrongMeta->makeSound();
	
	std::cout << "\n--- Deleting wrong animals ---" << std::endl;
	delete wrongMeta;
	delete wrongCat;

	std::cout << "\n\n=== Additional tests ===" << std::endl;
	std::cout << "--- Testing copy constructor ---" << std::endl;
	Dog originalDog;
	Dog copiedDog(originalDog);
	std::cout << "Original dog type: " << originalDog.getType() << std::endl;
	std::cout << "Copied dog type: " << copiedDog.getType() << std::endl;
	
	std::cout << "\n--- Testing assignment operator ---" << std::endl;
	Cat cat1;
	Cat cat2;
	cat2 = cat1;
	std::cout << "Cat1 type: " << cat1.getType() << std::endl;
	std::cout << "Cat2 type: " << cat2.getType() << std::endl;

	return 0;
}
