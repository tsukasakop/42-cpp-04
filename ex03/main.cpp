#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
	std::cout << "=== Subject's required test ===" << std::endl;
	IMateriaSource* src = new MateriaSource();
	AMateria* ice1 = new Ice();
	AMateria* cure1 = new Cure();
	src->learnMateria(ice1);
	src->learnMateria(cure1);
	delete ice1;
	delete cure1;

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << "\n\n=== Additional tests ===" << std::endl;
	
	std::cout << "\n--- Testing MateriaSource with 4 materias ---" << std::endl;
	IMateriaSource* source = new MateriaSource();
	AMateria* ice2 = new Ice();
	AMateria* cure2 = new Cure();
	AMateria* ice3 = new Ice();
	AMateria* cure3 = new Cure();
	source->learnMateria(ice2);
	source->learnMateria(cure2);
	source->learnMateria(ice3);
	source->learnMateria(cure3);
	delete ice2;
	delete cure2;
	delete ice3;
	delete cure3;
	
	// Try to learn a 5th materia (should do nothing)
	AMateria* extraMateria = new Ice();
	source->learnMateria(extraMateria);
	delete extraMateria;

	std::cout << "\n--- Creating materias from source ---" << std::endl;
	AMateria* ice = source->createMateria("ice");
	AMateria* cure = source->createMateria("cure");
	AMateria* unknown = source->createMateria("fire");
	
	if (ice) std::cout << "Created: " << ice->getType() << std::endl;
	if (cure) std::cout << "Created: " << cure->getType() << std::endl;
	if (unknown) std::cout << "Created: " << unknown->getType() << std::endl;
	else std::cout << "fire materia not found (expected)" << std::endl;

	std::cout << "\n--- Testing Character inventory ---" << std::endl;
	ICharacter* hero = new Character("hero");
	hero->equip(ice);
	hero->equip(cure);
	
	ICharacter* enemy = new Character("enemy");
	hero->use(0, *enemy);
	hero->use(1, *enemy);
	hero->use(2, *enemy); // Should do nothing (empty slot)

	std::cout << "\n--- Testing unequip ---" << std::endl;
	AMateria* savedMateria = source->createMateria("ice");
	hero->equip(savedMateria);
	hero->use(2, *enemy); // Should work now
	hero->unequip(2);
	hero->use(2, *enemy); // Should do nothing (unequipped)
	delete savedMateria;

	std::cout << "\n--- Testing Character copy ---" << std::endl;
	Character* original = new Character("original");
	original->equip(source->createMateria("ice"));
	original->equip(source->createMateria("cure"));
	
	Character* copy = new Character(*original);
	std::cout << "Original name: " << original->getName() << std::endl;
	std::cout << "Copy name: " << copy->getName() << std::endl;
	
	ICharacter* target = new Character("target");
	std::cout << "Original uses materias:" << std::endl;
	original->use(0, *target);
	original->use(1, *target);
	
	std::cout << "Copy uses materias:" << std::endl;
	copy->use(0, *target);
	copy->use(1, *target);

	delete target;
	delete original;
	delete copy;

	std::cout << "\n--- Filling Character inventory ---" << std::endl;
	ICharacter* collector = new Character("collector");
	collector->equip(source->createMateria("ice"));
	collector->equip(source->createMateria("cure"));
	collector->equip(source->createMateria("ice"));
	collector->equip(source->createMateria("cure"));
	
	// Try to equip a 5th materia (should do nothing)
	AMateria* extraItem = source->createMateria("ice");
	collector->equip(extraItem);
	delete extraItem; // Must delete since it wasn't equipped

	ICharacter* dummy = new Character("dummy");
	collector->use(0, *dummy);
	collector->use(1, *dummy);
	collector->use(2, *dummy);
	collector->use(3, *dummy);

	delete dummy;
	delete collector;
	delete hero;
	delete enemy;
	delete source;

	return 0;
}
