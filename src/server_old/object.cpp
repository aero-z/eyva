/*
 * `eyva'
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "object.h"

/**
 * Constructor.
 * @param id The object ID from which the rest of the information is generated.
 */
Object::Object(int id, FileHandler* file_handler)
{
	int len;

	/* If there is no object with the requested ID, break here:
	 */
	name = new char[len = file_handler->getName(NULL, id, 0)];
	if(len == 0) {
		delete name;
		throw new Exception("user with ID %d not found", id);
	}
	file_handler->getName(name, id, len);

	rules = new char[len = file_handler->getRules(NULL, id, 0)];
	file_handler->getRules(rules, id, len);

	effect = new char[len = file_handler->getEffect(NULL, id, 0)];
	file_handler->getEffect(effect, id, len);

	trigger = new char[len = file_handler->getTrigger(NULL, id, 0)];
	file_handler->getTrigger(trigger, id, len);

	this->id = id;
}

/**
 * Destructor.
 */
Object::~Object(void)
{
	delete[] name;
	delete[] rules;
	delete[] effect;
	delete[] trigger;
}

