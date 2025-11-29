#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "TestUtils.hpp"

template <typename T>
void showInstanceInfo(const std::string name, const T& animal) {
	std::cout << name << std::endl;
	std::cout << " - typeid: " << typeid(animal).name() << std::endl;
	std::cout << " - Type  : " << animal.getType() << std::endl;
	std::cout << " - Sound : ";
	animal.makeSound();
	std::cout << std::endl;
}

int main()
{
	{
		std::cout << "=== CASE0: Testing constructor/destructor ===" << std::endl;
		TestUtils::execOrthodoxCanonicalFormFunctions<Animal>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Cat>();
		TestUtils::execOrthodoxCanonicalFormFunctions<Dog>();
		TestUtils::execOrthodoxCanonicalFormFunctions<WrongAnimal>();
		TestUtils::execOrthodoxCanonicalFormFunctions<WrongCat>();
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
		std::cout << "=== CASE2: Testing wrong polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const WrongAnimal &wrongCat = WrongCat();
		const WrongAnimal &wrongAnimal = WrongAnimal();
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const WrongCat wrongCat;", wrongCat);
			showInstanceInfo("const WrongAnimal &wrongAnimal = wrongCat;", wrongAnimal);
		}
	}
	{
		std::cout << "=== CASE3: Testing copy instance polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Cat cat;
		const Animal &clone(cat);
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const Cat cat;", cat);
			showInstanceInfo("const Animal &clone = cat;", clone);
		}
	}
	{
		std::cout << "=== CASE4: Testing assignment instance polymorphism ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		const Cat cat;
		const Animal &clone = cat;
		{
			TestUtils::ScopedUnsilencer unsilencer;
			showInstanceInfo("const Cat cat;", cat);
			showInstanceInfo("const Animal &clone = cat;", clone);
		}
	}
	{
		std::cout << "=== MEMO: Compare virtual/no-virtual x direct/reference ===" << std::endl;
		TestUtils::ScopedSilencer silencer;
		{
			const WrongAnimal cat1 = WrongCat();
			const Animal cat2 = Cat();
			const WrongAnimal &cat3 = WrongCat();
			const Animal &cat4 = Cat();
			TestUtils::ScopedUnsilencer unsilencer;
			{
				showInstanceInfo("const WrongAnimal cat1 = WrongCat();", cat1);
				showInstanceInfo("const Animal cat2 = Cat();", cat2);
				showInstanceInfo("const WrongAnimal &cat3 = WrongCat();", cat3);
				showInstanceInfo("const Animal &cat4 = Cat();", cat4);
			}
		}
	}
	return 0;
}
