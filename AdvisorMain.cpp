#include "AdvisorMain.h"

AdvisorMain::AdvisorMain() {
    std::cout << "The advisor is loading. Please wait ..." << std::flush;
    orderBook.load("20200601.csv");
    logo();
    timeIndex = 0;
    timeString = orderBook.getTimestamps()[timeIndex];
    registerCommands();
    registerHelp();
}

void AdvisorMain::logo() {
    std::cout << R"(
    _       _       _                _           _
   / \   __| |_   _(_)___  ___  _ __| |__   ___ | |_
  / _ \ / _` \ \ / / / __|/ _ \| '__| '_ \ / _ \| __|
 / ___ \ (_| |\ V /| \__ \ (_) | |  | |_) | (_) | |_
/_/   \_\__,_| \_/ |_|___/\___/|_|  |_.__/ \___/ \__|

)";
}

void AdvisorMain::registerCommands() {
    menu.insert({"help", std::mem_fn(&AdvisorMain::helpCommand)});
    menu.insert({"prod", std::mem_fn(&AdvisorMain::prodCommand)});
    menu.insert({"min", std::mem_fn(&AdvisorMain::minCommand)});
    menu.insert({"max", std::mem_fn(&AdvisorMain::maxCommand)});
    menu.insert({"avg", std::mem_fn(&AdvisorMain::avgCommand)});
    menu.insert({"predict", std::mem_fn(&AdvisorMain::predictCommand)});
    menu.insert({"time", std::mem_fn(&AdvisorMain::timeCommand)});
    menu.insert({"step", std::mem_fn(&AdvisorMain::stepCommand)});
    menu.insert({"spread", std::mem_fn(&AdvisorMain::spreadCommand)});
    menu.insert({"median", std::mem_fn(&AdvisorMain::medianCommand)});
    menu.insert({"clear", std::mem_fn(&AdvisorMain::clearCommand)});

}

void AdvisorMain::registerHelp() {
    help_menu.insert({"help",
                      "Description:\n\tLists all available commands or output help for the specified command\n\nUsage:\n\thelp\n\thelp [command]"});
    help_menu.insert({"prod", "Description:\n\tLists all available products\n\nUsage:\n\tprod"});
    help_menu.insert({"min",
                      "Description:\n\tFind minimum bid or ask for product in current time step\n\nUsage:\n\tmin [product] [bid/ask]"});
    help_menu.insert({"max",
                      "Description:\n\tFind maximum bid or ask for product in current time step\n\nUsage:\n\tmax [product] [bid/ask]"});
    help_menu.insert({"avg",
                      "Description:\n\tCompute average ask or bid for the sent product over the sent number of time steps\n\nUsage:\n\tavg [product] [bid/ask] [steps]"});
    help_menu.insert({"predict",
                      "Description:\n\tPredict max or min ask or bid for the sent product for the next time step\n\nUsage:\n\tpredict [min/max] [product] [bid/ask]"});
    help_menu.insert({"time",
                      "Description:\n\tState current time in dataset, i.e. which timeframe are we looking at\n\nUsage:\n\ttime"});
    help_menu.insert({"step", "Description:\n\tMove to next time step\n\nUsage:\n\tstep"});
    help_menu.insert(
            {"spread", "Description:\n\tFind spread for product in current time step\n\nUsage:\n\tspread [product]"});
    help_menu.insert({"median",
                      "Description:\n\tFind median bid or ask for the product in current time step\n\nUsage:\n\tmedian [product] [bid/ask]"});
    help_menu.insert({"clear", "Description:\n\tClear the screen\n\nUsage:\n\tclear"});

}

void AdvisorMain::start() {
    std::cout.precision(5);
    std::cout << std::fixed;

    std::cout << "advisorbot> Please enter a command, or type \"help\" for a list of commands\nuser> ";
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> tokens = Helpers::tokenize(line, " ");
        executeCommand(tokens);
        std::cout << "user> ";
    }
}

void AdvisorMain::findCommand(const std::string &command) {
    if (menu.find(command) == menu.end()) {
        throw std::runtime_error("Error: Command \"" + command + "\" is not defined");
    }
}

void AdvisorMain::executeCommand(std::vector<std::string> &tokens) {
    if (tokens.empty()) {
        return;
    }

    try {
        const auto &command = tokens[0];
        std::vector<std::string> arguments = {tokens.begin() + 1, tokens.end()};

        findCommand(command);
        menu[command](*this, arguments);

    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
}

void AdvisorMain::helpCommand(std::vector<std::string> &args) {
    if (args.size() > 1) {
        throw std::invalid_argument("Error: Number of arguments does not match.");
    }

    if (args.size() == 1) {
        const auto &command = args[0];
        findCommand(command);

        std::cout << help_menu[command] << '\n';
        return;
    }

    std::cout << "advisor> " << R"(Available commands:
    help                List all available commands
    help [command]      Output help for the specified command
    prod                List available products
    min                 Find minimum bid or ask for product in current time step
    max                 Find maximum bid or ask for product in current time step
    avg                 Compute average ask or bid for the sent product over the sent number of time steps
    median              Find median bid or ask for the product in current time step
    spread              Find spread for product in current time step
    predict             Predict max or min ask or bid for the sent product for the next time step
    time                State current time in dataset, i.e. which timeframe are we looking at
    step                Move to next time step
    clear               Clear the screen
)";
}

void AdvisorMain::prodCommand(std::vector<std::string> &args) {
    checkArguments(args, 0);

    std::cout << "advisor> " << "Available products are:\n";
    for (const auto &product: orderBook.getProducts()) {
        std::cout << "- " << product << '\n';
    }
}

void AdvisorMain::minCommand(std::vector<std::string> &args) {
    checkArguments(args, 2);

    const auto product = orderBook.productExists(args[0]);
    const auto orderType = Order::stoOT(args[1]);

    std::cout << "advisor> " << "The minimum " << args[1] << " price for " << product << " is: "
              << Math::min(orderBook.getPricesFromOrders(timeString, product, orderType))
              << '\n';
}

void AdvisorMain::maxCommand(std::vector<std::string> &args) {
    checkArguments(args, 2);

    const auto product = orderBook.productExists(args[0]);
    const auto orderType = Order::stoOT(args[1]);

    std::cout << "advisor> " << "The maximum " << args[1] << " price for " << product << " is: "
              << Math::max(orderBook.getPricesFromOrders(timeString, product, orderType))
              << '\n';
}

void AdvisorMain::spreadCommand(std::vector<std::string> &args) {
    checkArguments(args, 1);

    const auto product = orderBook.productExists(args[0]);

    std::cout << "advisor> " << "The spread for " << product << " is: "
              << Math::bidAskSpread(
                      orderBook.getPricesFromOrders(timeString, product, OrderType::ask),
                      orderBook.getPricesFromOrders(timeString, product, OrderType::bid))
              << '\n';
}

void AdvisorMain::medianCommand(std::vector<std::string> &args) {
    checkArguments(args, 2);

    const auto product = orderBook.productExists(args[0]);
    const auto orderType = Order::stoOT(args[1]);

    std::cout << "advisor> " << "The median " << args[1] << " price for " << product << " is: "
              << Math::median(orderBook.getPricesFromOrders(timeString, product, orderType))
              << '\n';
}

void AdvisorMain::avgCommand(std::vector<std::string> &args) {
    checkArguments(args, 3);

    const auto product = orderBook.productExists(args[0]);
    const auto orderType = Order::stoOT(args[1]);
    const auto steps = std::stoi(args[2]);

    std::cout << "advisor> "
              << "The average " << product << ' ' << args[1] << " price over the last " << steps << " steps is "
              << orderBook.avgTimesteps(timeIndex, product, orderType, steps)
              << '\n';
}

void AdvisorMain::predictCommand(std::vector<std::string> &args) {
    checkArguments(args, 3);

    if (timeIndex == 0) {
        throw std::runtime_error("Error: Not enough info. Try again another time.");
    }

    const auto minmax = args[0];
    if (minmax != "max" && minmax != "min")
        throw std::invalid_argument("Error: The first parameter must be max or min.");
    const auto product = orderBook.productExists(args[1]);
    const auto orderType = Order::stoOT(args[2]);

    std::cout << "advisor> "
              << "I predict that the " << minmax << ' ' << args[2] << " price for " << product << " will be "
              << orderBook.predictPrice(minmax, product, orderType)
              << '\n';
}

void AdvisorMain::timeCommand(std::vector<std::string> &args) {
    checkArguments(args, 0);

    std::cout << "advisor> " << "Current time is: " << timeString << '\n';
}

void AdvisorMain::stepCommand(std::vector<std::string> &args) {
    checkArguments(args, 0);

    orderBook.updateStats(timeIndex);
    timeIndex++;
    if (timeIndex > orderBook.getTimestamps().size()) {
        timeIndex--;
        throw std::out_of_range("Attention: Reached end of timeline.");
    }
    timeString = orderBook.getTimestamps()[timeIndex];

    std::cout << "advisor> " << "The time is now at: " << timeString << '\n';
}

void AdvisorMain::clearCommand(std::vector<std::string> &args) {
    checkArguments(args, 0);
    system("clear||cls");
}

void AdvisorMain::checkArguments(const std::vector<std::string> &args, int size) {
    if (args.size() != size) {
        std::string e = (args.size() > size ? "many" : "few");
        throw std::invalid_argument("Error: Number of arguments does not match. Too " + e + " arguments!");
    }
}
