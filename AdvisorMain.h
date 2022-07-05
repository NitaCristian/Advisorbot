#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstdlib>

#include "Helpers.h"
#include "OrderBook.h"

class AdvisorMain {
public:
    // Constructor used to create and initialize the advisor
    AdvisorMain();

    /**
     * Function which starts the simulation of the program
     */
    void start();

private:

    /**
     * Function which displays a logo
     */
    static void logo();

    /**
     * Function which registers help messages
     */
    void registerHelp();

    /**
     * Function which registers commands
     */
    void registerCommands();

    /**
     * Function to call a command
     * @param tokens Vector of string containing the command and its arguments
     */
    void executeCommand(std::vector<std::string> &tokens);

    /**
     * Function used to check if a command exists
     * @param command
     */
    void findCommand(const std::string &command);

    /**
     * Function which check whether a command has the right number of arguments
     * @param args Vector of arguments
     * @param size Correct number of arguments
     */
    static void checkArguments(const std::vector<std::string> &args, int size);

    /**
     * Command to display help to the user
     * @param args Vector of arguments
     */
    void helpCommand(std::vector<std::string> &args);

    /**
     * Command to display all available products to the user
     * @param args Vector of arguments
     */
    void prodCommand(std::vector<std::string> &args);

    /**
     * Command to calculate the minimum price for a product
     * @param args Vector of arguments
     */
    void minCommand(std::vector<std::string> &args);

    /**
     * Command to calculate the maximum price for a product
     * @param args Vector of arguments
     */
    void maxCommand(std::vector<std::string> &args);

    /**
     * Command to calculate the bid-ask spread for a product
     * @param args Vector of arguments
     */
    void spreadCommand(std::vector<std::string> &args);

    /**
     * Command to calculate the median price for a product
     * @param args Vector of arguments
     */
    void medianCommand(std::vector<std::string> &args);

    /**
     * Command to calculate the average bid or ask for a product over a number of timesteps
     * @param args Vector of arguments
     */
    void avgCommand(std::vector<std::string> &args);

    /**
     * Command to output the current time
     * @param args Vector of arguments
     */
    void predictCommand(std::vector<std::string> &args);

    /**
     * Command predictPrice the minimum or maximum ask or bid for a product
     * @param args Vector of arguments
     */
    void timeCommand(std::vector<std::string> &args);

    /**
     * Command to move to next time step
     * @param args Vector of arguments
     */
    void stepCommand(std::vector<std::string> &args);

    /**
     * Command to clear the screen
     * @param args Vector of arguments
     */
    void clearCommand(std::vector<std::string> &args);

    // Current timestamp in our simulation
    int timeIndex;
    std::string timeString;

    // OrderBook used to store data from a CSV file
    OrderBook orderBook;

    // Map of commands mapped to their name
    std::map<std::string, std::function<void(AdvisorMain &, std::vector<std::string> &args)>> menu;

    // Map of help mapped to their command name
    std::map<std::string, std::string> help_menu;
};




