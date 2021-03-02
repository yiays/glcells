#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "gamemodel.h"

namespace Element {
	struct cBase {
		std::string Name;
		GameModel::Color Color;

		int operator==(cBase b) {
      return this->Name == b.Name;
    }
	};

  struct cElement {
		std::string Name;
		GameModel::Color Color;
		float Weight;
		float Conductivity;
		float StateTransitions[2];

		int operator==(cElement b) {
      return this->Name == b.Name;
    }
	};

	struct cBuilding {
		std::string Name;
		GameModel::Color Color;
		cElement Composition;
		GameModel::Rect2d Size;

		int operator==(cBuilding b) {
      return this->Name == b.Name;
    }
	};

	struct cBiome {
		std::string Name;
		GameModel::Color Color;

		int operator==(cBiome b) {
      return this->Name == b.Name;
    }
	};

	// Vacuums
  cElement Vacuum = {
		.Name = { "Vacuum" },
		.Color = { 0, 0, 0 },
		.Weight = 0,
		.Conductivity = 0,
		.StateTransitions = { }
	};

	// Gasses
	cElement Hydrogen = {
		.Name = { "Hydrogen" },
		.Color = { 255, 150, 160 },
		.Weight = 1.008,
		.Conductivity = 2.0,
		.StateTransitions = { -259.2, -239.9 }
	};
	cElement Oxygen = {
		.Name = { "Oxygen" },
		.Color = { 150, 150, 255 },
		.Weight = 15.999,
		.Conductivity = 1.0,
		.StateTransitions = { -218.8, -182.9 }
	};
	cElement CarbonDioxide = {
		.Name = { "Carbon Dioxide" },
		.Color = { 20, 10, 0 },
		.Weight = 44,
		.Conductivity = 1.0,
		.StateTransitions = { -78.5, -56.6 }
	};

	// Liquids
	cElement Water = {
		.Name = { "Ice|Water|Steam" },
		.Color = { 100, 100, 255 },
		.Weight = 33,
		.Conductivity = 0.5,
		.StateTransitions = { 0, 100 }
	};

	// Solids
	cElement IgneousRock = {
		.Name = { "Igneous Rock|Magma" },
		.Color = { 200, 200, 200 },
		.Weight = 200,
		.Conductivity = 1.0,
		.StateTransitions = { 1000, 2200 }
	};

	// Buildings
	cBuilding Door = {
		.Name = "Door",
		.Color = { 200, 10, 200 },
		.Composition = IgneousRock,
		.Size = { 0, -1, 1, 2 }
	};

	// Biomes
	cBiome Marsh = {
		.Name = "Marsh",
		.Color = { 0, 150, 50 }
	};
}

#endif