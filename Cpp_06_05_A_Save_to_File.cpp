// Cpp_06_05_A_Save_to_File.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<vector>
#include <map>
#include<algorithm>
#include <string>
#include<sstream>
#include<fstream>
#include<cstdlib>


class Vehicle
{

private:
	std::string manufacturer;
	std::string model;
	double horsepower;
	std::string registrationNumber;

	//Person person;  //an owner (a pointer to a Person object)

public:
	Vehicle(std::string manufacturer, std::string model,
		double horsepower, std::string registrationNumber) :
		manufacturer(manufacturer), model(model), horsepower(horsepower),
		registrationNumber(registrationNumber) {
	}

	std::string getManufacturer()
	{
		return this->manufacturer;
	}
	std::string getModel()
	{
		return this->model;
	}
	double getHorsepower()
	{
		return this->horsepower;
	}
	std::string getRegistrationNumber()
	{
		return this->registrationNumber;
	}

	std::string getVehicleInfo() {
		std::ostringstream info;
		info << "manufacturer: " << this->manufacturer
			<< ", model: " << this->model
			<< ", horsepower: " << this->horsepower
			<< ", registrationNumber: " << this->registrationNumber << std::endl;
		return info.str();
	}
	std::string getVehicleInfoStandardStyle() {
		std::ostringstream info;
		info << this->manufacturer
			<< " " << this->model
			<< " " << this->horsepower
			<< " " << this->registrationNumber << std::endl;
		return info.str();
	}	
};

class Person
{
private:
	std::string name;
	int age;
	int id;

public:
	Person(std::string name, int age, int id) :
		name(name), age(age), id(id) {
	}

	std::string getName()
	{
		return this->name;
	}
	int getAge()
	{
		return this->age;
	}
	int getId()
	{
		return this->id;
	}

	Person getPerson()
	{
		return {
			this->name,
			this->age,
			this->id };
	}
	std::string getPersonInfo() {
		std::ostringstream info;
		info << "name: " << this->name
			<< ", age: " << this->age
			<< ", id: " << this->id << std::endl;
		return info.str();
	}
	std::string getPersonInfoStandardStyle() {
		std::ostringstream info;
		info << this->name
			<< " " << this->age
			<< " " << this->id;
		return info.str();
	}	
};

int main()
{
	std::map<std::string, std::vector<Vehicle>> dataPersonsAndVehicles;
	std::vector<std::string> idDataOwners;
	std::vector<Person> personsData;

	int choice = 7;

	int id = 0;
	std::string name;
	int age = 0;
	std::string manufacturer;
	std::string model;
	double horsepower = 0.0;
	std::string registrationNumber;
	std::string newName;

	while (choice)
	{
		//Person person(name, age, id);

		switch (choice)
		{
		case 1: //Add new car :
		{
			std::cout << "Enter name of the car owner: ";
			getline(std::cin, name);
			auto  it = std::find(idDataOwners.begin(), idDataOwners.end(), name);
			if (it != idDataOwners.end()) //if owner is in the list already:
			{
				id = std::find(idDataOwners.begin(), idDataOwners.end(), name) - idDataOwners.begin();
				//dataPersonsAndVehicles.insert();

				int age = personsData[id].getAge();

				std::cout << "Enter manufacturer: ";
				std::cin >> manufacturer;
				std::cin.ignore();

				std::cout << "Enter model: ";
				std::cin >> model;
				std::cin.ignore();

				std::cout << "Enter horsepowers (bhp): ";
				std::cin >> horsepower;
				std::cin.ignore();

				std::cout << "Enter registrationNumber: ";
				std::cin >> registrationNumber;
				std::cin.ignore();

				Vehicle vehicle(manufacturer, model, horsepower, registrationNumber);
				dataPersonsAndVehicles[name].push_back(vehicle);

			}
			else //adding new car and new owner too:
			{
				std::cout << "Enter age of the car owner: ";
				std::cin >> age;
				std::cin.ignore();

				idDataOwners.push_back(name);
				id = idDataOwners.size() - 1;

				std::cout << "Enter car manufacturer: ";
				std::cin >> manufacturer;
				std::cin.ignore();

				std::cout << "Enter model: ";
				std::cin >> model;
				std::cin.ignore();

				std::cout << "Enter horsepowers (bhp): ";
				std::cin >> horsepower;
				std::cin.ignore();

				std::cout << "Enter registrationNumber: ";
				std::cin >> registrationNumber;
				std::cin.ignore();

				Vehicle vehicle(manufacturer, model, horsepower, registrationNumber);
				std::vector<Vehicle> personsVehicles;
				personsVehicles.push_back(vehicle);
				dataPersonsAndVehicles.insert({ name, personsVehicles });
				Person person(name, age, id);
				personsData.push_back(person);
			}
			break;
		}
		case 2: //change vehicle's owner
		{
			//int idBefore, newId;
			std::cout << "Enter name of the previous owner: ";
			getline(std::cin, name);

			std::cout << "Enter name of the NEW owner: ";
			getline(std::cin, newName);

			std::cout << "Enter vechicles' registration number: ";
			getline(std::cin, registrationNumber);

			for (auto itera = dataPersonsAndVehicles[name].begin(); itera != dataPersonsAndVehicles[name].end(); itera++)
			{
				if ((*itera).getRegistrationNumber() == registrationNumber) {
					manufacturer = (*itera).getManufacturer();
					model = (*itera).getModel();
					horsepower = (*itera).getHorsepower();
				}
			}
			Vehicle newOwnerVechicle(manufacturer, model, horsepower, registrationNumber);
			dataPersonsAndVehicles[newName].push_back(newOwnerVechicle);
			//int index = std::find(dataPersonsAndVehicles[name].begin(), dataPersonsAndVehicles[name].end(), newOwnerVechicle) - dataPersonsAndVehicles[name].begin();

			////dataPersonsAndVehicles[name].erase(*itera);
			//dataPersonsAndVehicles[name].erase(dataPersonsAndVehicles[name].begin() + index);

			for (int j = 0; j < dataPersonsAndVehicles[name].size(); j++)
			{
				if (newOwnerVechicle.getRegistrationNumber() == dataPersonsAndVehicles[name][j].getRegistrationNumber())
				{
					dataPersonsAndVehicles[name].erase(dataPersonsAndVehicles[name].begin() + j);
				}
			}
			break;
		}
		case 3: //A person’s name and age change: Change the owner of all person's vehicles 
		{
			std::cout << "Enter name of the previous owner who sells all his cars: ";
			getline(std::cin, name);

			std::cout << "Enter name of the NEW owner of all previous owner' cars: ";
			getline(std::cin, newName);

			auto  iit = std::find(idDataOwners.begin(), idDataOwners.end(), newName);
			if (iit != idDataOwners.end()) //if NEW owner is in the list already:
			{
				for (auto iitt = dataPersonsAndVehicles.begin(); iitt != dataPersonsAndVehicles.end(); iitt++)
				{
					if ((*iitt).first == newName)
					{
						for (auto iiitt = dataPersonsAndVehicles.begin(); iiitt != dataPersonsAndVehicles.end(); iiitt++)
						{
							if ((*iiitt).first == name)
							{
								for (auto iii = ((*iiitt).second).begin(); iii != ((*iiitt).second).end(); iii++)
								{
									((*iitt).second).push_back(*iii);
								}
							}
						}
					}
				}
				for (auto iittt = dataPersonsAndVehicles.begin(); iittt != dataPersonsAndVehicles.end(); iittt++)
				{
					if ((*iittt).first == name)
					{
						(*iittt).second.clear();
					}
				}
			}
			else //new owner is not in the list:
			{
				std::cout << "The new owner hasn't got an ID (is not in the list). Enter age of the new car owner: ";
				std::cin >> age;
				std::cin.ignore();

				idDataOwners.push_back(name);
				id = idDataOwners.size() - 1;

				Person newOwner(newName, age, id);
				personsData.push_back(newOwner);
				idDataOwners.push_back(newName);
				std::vector<Vehicle> newOwnerVehicles;
				for (auto iterr = dataPersonsAndVehicles.begin(); iterr != dataPersonsAndVehicles.end(); iterr++)
				{
					if ((*iterr).first == name)
					{
						for (auto iterrr = ((*iterr).second).begin(); iterrr != ((*iterr).second).end(); iterr++)
						{
							newOwnerVehicles.push_back(*iterrr);
						}
					}
				}

				dataPersonsAndVehicles.insert({ newName, newOwnerVehicles });

				for (auto iittt = dataPersonsAndVehicles.begin(); iittt != dataPersonsAndVehicles.end(); iittt++)
				{
					if ((*iittt).first == name)
					{
						(*iittt).second.clear();
					}
				}
			}
			break;
		}
		case 4: //print to console
		{
			//auto itt = personsData.begin();
			std::cout << std::endl;
			std::cout << "********************************************************************************************************" << std::endl;
			for (auto iterator = dataPersonsAndVehicles.begin(); iterator != dataPersonsAndVehicles.end(); iterator++)
			{
				//std::cout << "Owner: " << (*iterator) .first << std::endl;
				//std::cout << "Owner: " << (*itt).getPersonInfo() << std::endl;
				for (auto itte = personsData.begin(); itte != personsData.end(); itte++)
				{
					if ((*iterator).first == (*itte).getName())
					{
						std::cout << "OWNER: " << (*itte).getPersonInfo();
					}
				}
				int number = 1;
				for (int m = 0; m < (*iterator).second.size(); m++)
				{
					std::cout << number << ". VEHICLE info: " << (*iterator).second[m].getVehicleInfo();
					number++;
				}
				std::cout << std::endl;
				//itt++;
			}
			std::cout << "********************************************************************************************************" << std::endl;
			std::cout << std::endl;

			break;
		}

		case 5:  // extract DB in file  
		{
			std::ofstream fileOut("dataBase_Owners_id.txt");
			fileOut << "\t\tDATABASE VEHICLES AND OWNERS" << std::endl;
			for (auto iterator = dataPersonsAndVehicles.begin(); iterator != dataPersonsAndVehicles.end(); iterator++)
			{
				//std::cout << "Owner: " << (*iterator) .first << std::endl;
				//std::cout << "Owner: " << (*itt).getPersonInfo() << std::endl;
				for (auto itte = personsData.begin(); itte != personsData.end(); itte++)
				{
					if ((*iterator).first == (*itte).getName())
					{
						fileOut << "OWNER: " << (*itte).getPersonInfo();
					}
				}
				int number = 1;
				for (int m = 0; m < (*iterator).second.size(); m++)
				{
					fileOut << number << ". VEHICLE info: " << (*iterator).second[m].getVehicleInfo();
					number++;
				}
				fileOut << std::endl;
				//itt++;
			}
			fileOut.close();

			break;
		}
		case 6: //extract Standard Style DB in file  
			{
			std::ofstream fileOut("dataBase_Owners_Vehicles_STANDARD_STYLE_new_file.txt");
			//fileOut << "\t\tDATABASE VEHICLES AND OWNERS - STANDARD STYLE" << std::endl;
			//fileOut << "NAME-AGE-ID-manufacturer-model-horsePower-registrationNumber" << std::endl;
			for (auto iterator = dataPersonsAndVehicles.begin(); iterator != dataPersonsAndVehicles.end(); iterator++)
			{	
				//int number = 1;
				for (int m = 0; m < (*iterator).second.size(); m++)
				{
					for (auto itte = personsData.begin(); itte != personsData.end(); itte++)
					{
						if ((*iterator).first == (*itte).getName())
						{
							fileOut << (*itte).getPersonInfoStandardStyle() << " ";
						}
					}
					fileOut << (*iterator).second[m].getVehicleInfoStandardStyle();
					//number++;
				}
				fileOut << std::endl;
				//itt++;
			}
			fileOut.close();
			break;
			}
		case 7:  //firstTimeOnly - info / DB from file !!!
			{
			std::string line;

			std::ifstream reader("dataBase_Owners_and_Vehicles.txt");

			if (!reader) {
				std::cout << "Error opening input file" << std::endl;
				return -1;
			}

			for (int i = 0; !reader.eof(); i++) {

				getline(reader, line);
				//CHECK:
				//std::cout << line << std::endl ;

				std::istringstream isst(line);
				std::string arrOneLineData[6];
				std::string item;
				int p = 0;
				while (isst >> item)
				{
					arrOneLineData[p] = item;
					p++;
				}
				name = arrOneLineData[0];
				age = atoi(arrOneLineData[1].c_str());
				//id
				manufacturer = arrOneLineData[2];
				model = arrOneLineData[3];
				std::string::size_type sz;     // alias of size_t
				horsepower = std::stod(arrOneLineData[4], &sz);
				registrationNumber = arrOneLineData[5];

				Vehicle nextVehicle(manufacturer, model, horsepower, registrationNumber);

				if (std::find(idDataOwners.begin(), idDataOwners.end(), name) != idDataOwners.end()) {
					/* v contains x */
					dataPersonsAndVehicles[name].push_back(nextVehicle);
				}
				else
				{
					idDataOwners.push_back(name);
					id = idDataOwners.size() - 1;
					Person nextNewPerson(name, age, id);
					personsData.push_back(nextNewPerson);
					dataPersonsAndVehicles[name].push_back(nextVehicle);
				}
			}

			reader.close();

			/*std::string line;
			std::istringstream input;
			input.str("1\n2\n3\n4\n5\n6\n7\n");
			for (line; std::getline(input, line); ) {
			sum += std::stoi(line);
			}*/
			break;
			}
		default:
			break;
		}

		std::cout << "Choose: \n0 - exit\n1 - add new car \n2 - change vehicle's owner \n3 - Change the owner of all person's vehicles (change name and person'info ) \n4 - print to console \n5 - extract DB in file by Owner name \n6 - extract Standard Style DB in file  \nYour choice: ";
		std::cin >> choice;
		std::cin.ignore();
	}

	return 0;
}

