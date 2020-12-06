#ifndef ELEMENTS_H
#define ELEMENTS_H

namespace Elemental {

  struct Element {
		std::string Name;
		Game::Color3f Color;
		float Weight;
		float Conductivity;
		float StateTransitions[2];

		int operator==(Element b) {
      return this->Name == b.Name;
    }
	};

  Element Vacuum = {
		{ "Vacuum" },							// Name
		{ 0, 0, 0 },					// Color
		0,										// Weight
		0,										// Conductivity
		{ }										// StateTransitions
	};

	Element Hydrogen = {
		{ "Hydrogen" },
		{ 255, 100, 100 },
		1.008,
		2.0,
		{ -259.2, -239.9 }
	};

	Element Oxygen = {
		{ "Oxygen" },
		{ 150, 150, 255 },
		15.999,
		1.0,
		{ -218.8, -182.9 }
	};

	Element CarbonDioxide = {
		{ "Carbon Dioxide" },
		{ 20, 10, 0 },
		44,
		1.0,
		{ -78.5, -56.6 }
	};
}

#endif