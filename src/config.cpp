#include "config.hpp"

#include <iostream>
#include <string>


Config::Config(float k_value, int n, float initial, std::vector<Source> s)
:k(k_value), numberOfSections(n), initialTemperature(initial), sourcesAndSinks(s)
{}

Config Configure::configureHeatFlow()
{
    float k = getInput(0.0f, 0.5f, "Please enter a value for K (0, 0.5): ", 0.1f);
    int numberOfSections = getInput(1, 100, "Please enter the number of sections (1, 100): ", 5);
    float initialTemperature = getInput(-1000.f, 1000.f, "Please enter the initial temperature for each section (-1000, 1000): ", 10.f);

    std::vector<Source> sources {};
    for (int i = 0; i < numberOfSections; i++)
    {
        std::cout << "Would you like a source/sink in section " << i << "? (y/n): \n";
        std::string answer {};
        std::getline(std::cin, answer);

        // Any answer other than y is defaulted to no
        if (answer == "y" || answer == "Y")
        {
            float sourceAmount = getInput(-1000.f, 1000.f, "Please enter the source/sink amount you would like (-1000, 1000): ", 100.f);
            sources.push_back({i, sourceAmount});
        }
    }

    return Config(k, numberOfSections, initialTemperature, sources);
}

int Configure::getInput(int lowerBound, int upperBound, const std::string& prompt, int defaultValue)
{
    std::string userInput {};
    int val {};

    while (true)
    {
        std::cout << prompt << "\n";
        std::getline(std::cin, userInput);

        if (userInput == "default")
        {
            return defaultValue;
        }
        else if (userInput == "exit")
        {
            return lowerBound - 1;
        }

        try
        {
            val = std::stoi(userInput);
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Number out of range for this type.\n";
            continue;
        }

        if (val < lowerBound || val > upperBound)
        {
            std::cout << "Value is out of range. Please try again.\n";
            continue;
        }

        return val;
    }
}

float Configure::getInput(float lowerBound, float upperBound, const std::string& prompt, float defaultValue)
{
    std::string userInput {};
    float val {};

    while (true)
    {
        std::cout << prompt << "\n";
        std::getline(std::cin, userInput);

        if (userInput == "default")
        {
            return defaultValue;
        }
        else if (userInput == "exit")
        {
            return lowerBound - 1;
        }

        try
        {
            val = std::stof(userInput);
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Number out of range for this type.\n";
            continue;
        }

        if (val < lowerBound || val > upperBound)
        {
            std::cout << "Value is out of range. Please try again.\n";
            continue;
        }

        return val;
    }
}
