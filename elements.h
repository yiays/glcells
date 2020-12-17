#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "gamemodel.h"

namespace Element {

  struct cElement {
		std::string Name;
		GameModel::Color3f Color;
		float Weight;
		float Conductivity;
		float StateTransitions[2];

		int operator==(cElement b) {
      return this->Name == b.Name;
    }
	};

	// Vacuums
  cElement Vacuum = {
		{ "Vacuum" },							// Name
		{ 0, 0, 0 },					// Color
		0,										// Weight
		0,										// Conductivity
		{ }										// StateTransitions
	};

	// Gasses
	cElement Hydrogen = {
		{ "Hydrogen" },
		{ 255, 100, 100 },
		1.008,
		2.0,
		{ -259.2, -239.9 }
	};
	cElement Oxygen = {
		{ "Oxygen" },
		{ 150, 150, 255 },
		15.999,
		1.0,
		{ -218.8, -182.9 }
	};
	cElement CarbonDioxide = {
		{ "Carbon Dioxide" },
		{ 20, 10, 0 },
		44,
		1.0,
		{ -78.5, -56.6 }
	};

	// Liquids
	cElement Water = {
		{ "Water" },
		{ 100, 100, 255 },
		33,
		0.5,
		{ 0, 100 }
	};
}

#endif