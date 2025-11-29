#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "TestUtils.hpp"

int main()
{
	{
		std::cout << "\n=== CASE0: Testing constructor/destructor ===" << std::endl;
		TestUtils::execOrthodoxCanonicalFormFunctions<Animal>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Cat>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Dog>();
		TestUtils::execOrthodoxCanonicalFormFunctions<WrongAnimal>();
		TestUtils::execOrthodoxCanonicalFormFunctions<WrongCat>();
	}
	{
		std::cout << "\n=== CASE1: Testing correct polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Animal cat = Cat();
		const Animal dog = Dog();
		const Animal meta = Animal();
		{
			TestUtils::ScopedUnsilencer unsilencer;
			std::cout << "\n--- Type information ---" << std::endl;
			std::cout << cat.getType() << " " << std::endl;
			std::cout << dog.getType() << " " << std::endl;
			std::cout << meta.getType() << " " << std::endl;

			std::cout << "\n--- Making sounds ---" << std::endl;
			cat.makeSound();
			dog.makeSound();
			meta.makeSound();
		}
	}
	{
		std::cout << "\n=== CASE2: Testing wrong polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const WrongAnimal wrongCat = WrongCat();
		const WrongAnimal wrongMeta = WrongAnimal();
		{
			TestUtils::ScopedUnsilencer unsilencer;
			std::cout << "\n--- Type information ---" << std::endl;
			std::cout << wrongCat.getType() << " " << std::endl;
			std::cout << wrongMeta.getType() << " " << std::endl;
			
			std::cout << "\n--- Making sounds (should output WrongAnimal sound) ---" << std::endl;
			wrongCat.makeSound();
			wrongMeta.makeSound();
		}
	}
	{
		std::cout << "\n=== CASE3: Testing copy instance polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Cat cat;
		const Animal clone(cat);
		{
			TestUtils::ScopedUnsilencer unsilencer;
			std::cout << "\n--- Type information ---" << std::endl;
			std::cout << clone.getType() << " " << std::endl;
			
			std::cout << "\n--- Making sounds (should output WrongAnimal sound) ---" << std::endl;
			clone.makeSound();
		}
	}
	{
		std::cout << "\n=== CASE4: Testing assignment instance polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Cat cat;
		const Animal clone = cat;
		{
			TestUtils::ScopedUnsilencer unsilencer;
			std::cout << "\n--- Type information ---" << std::endl;
			std::cout << clone.getType() << " " << std::endl;
			
			std::cout << "\n--- Making sounds (should output WrongAnimal sound) ---" << std::endl;
			clone.makeSound();
		}
	}
	return 0;
}
