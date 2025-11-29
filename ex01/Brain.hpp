#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <iostream>

class Brain {
public:
	static const int kNumIdeas = 100;

private:
	std::string ideas[kNumIdeas];

public:
	Brain();
	Brain(const Brain& other);
	Brain& operator=(const Brain& other);
	~Brain();

	void setIdea(int index, const std::string& idea);
	std::string getIdea(int index) const;
};

#endif
