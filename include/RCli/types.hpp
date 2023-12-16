#ifndef __RCLI_TYPES__
#define __RCLI_TYPES__

    #include <string>
    #include <vector> 
    #include <tuple> 
    #include <map> 
    #include <set> 
    #include <algorithm>
    #include <numeric>
    
    namespace RCli{
        
        using String = std::string;
        using VectorString = std::vector<String>;
        using MapString = std::map<String, String>;
        using SetString = std::set<String>;
        
        class InputConfig{
            public:
                RCli::String _text, _default;
                bool _clean, _required;
                
                InputConfig(String text, bool clean = true, bool required = false, String default_value = "")
                    : _text(text), _clean(clean), _default(default_value), _required(required) {}
                InputConfig(const InputConfig& other){ *this = other; }
                InputConfig& operator=(const InputConfig& other) {
                    if (this != &other) {
                        _text = other._text;
                        _clean = other._clean;
                        _default = other._default;
                        _required = other._required;
                    }
                    return *this;
                }
        };

    } 

#endif