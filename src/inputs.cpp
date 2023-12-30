#include "rcli/inputs.hpp"
#include "rcli/utils.hpp"
#include "TColor/TColor.hpp"

using namespace rcli;

std::string rcli::ask_input_value(InputConfig config){
    std::string message{config._text};
    
    if(config._default != "")
        message = message + " (default: \"" + config._default + "\" )";

    TColor::write(ColorConfig::_input_key_color, message + ": ");
    TColor::set_color(ColorConfig::_input_value_color);
    std::string value = Utils::get_line();

    if(config._clean)
        value = Utils::clean_text(value);
    if(config._default != "" && value.empty())
        value = config._default;
    if(config._required && value.empty()){
        TColor::write_endl(ColorConfig::_error_color, "[ REQUIRED ]: This is required");
        return rcli::ask_input_value(config);
    }
    return value;
}

std::vector<std::string> rcli::ask_inputs_values(std::vector<InputConfig> configs){
    std::vector<std::string> results;
    for(const auto config: configs){
        results.push_back(rcli::ask_input_value(config));
    }
    return results;
}

std::string rcli::ask_value_in_list(InputConfig config, std::vector<std::string> options, bool ignore_case){
    std::string value = rcli::ask_input_value(config);

    if(!Utils::some(value, options, ignore_case)){
        TColor::write_endl(ColorConfig::_error_color, "[ NOT VALID ]: These are the expected values [" + Utils::join(options, ", ") + "]");
        return rcli::ask_value_in_list(config, options, ignore_case);
    }
    return value;
}

bool rcli::ask_boolean(std::string text, bool default_value){
    InputConfig config = InputConfig()
        .text(text)
        .default_value(default_value ? "y" : "n")
        .clean(true)
        .required(true);
    return Utils::lowercase(rcli::ask_value_in_list(config, {"n","y"}, true)) == "y";
}

std::string rcli::ask_value_in_options(std::string text, std::vector<std::string> options){
    std::vector<std::string> list_options;
    TColor::set_color(ColorConfig::_input_key_color);
    for(size_t i = 0; i < options.size(); i++){
        std::cout <<  i + 1 << ") " << options.at(i) << std::endl;
        list_options.push_back(std::to_string(i + 1));
    }

    InputConfig config = InputConfig().text(text).clean(true);
    
    std::string value = rcli::ask_value_in_list(config, list_options);
    return options.at(std::stoi(value) - 1);
}