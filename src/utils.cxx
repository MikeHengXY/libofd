#include <iostream>
#include <sstream>
#include <vector>
#include <tinyxml2.h>
using namespace tinyxml2;

#include "logger.h"

std::string GetChildElements(const XMLElement *element)
{
    std::stringstream ss;
    ss << std::endl
       << "------------------------------" << std::endl
       << element->Name() << std::endl;
    const XMLElement *childElement = element->FirstChildElement();
    while (childElement != NULL)
    {
        ss << "    " << childElement->Name() << std::endl;
        childElement = childElement->NextSiblingElement();
    }
    ss << "------------------------------" << std::endl;

    return ss.str();
}

std::vector<std::string> SpliteString(const std::string &content)
{
    std::istringstream iss(content);
    // std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
    //                                 std::istream_iterator<std::string>{}};
    // return tokens;

    //todo
    std::vector<std::string> tokens;
    char str[1024];
    while (iss.getline(str, 1024)) // loop getting single characters
    {
        tokens.push_back(std::string(str));
        std::cout << str;
    }

    return tokens;
}

std::tuple<double, double, double, double, bool> parsePhysicalBoxElement(const XMLElement *physicalBoxElement)
{
    double x0, y0, x1, y1 = 0.0;
    bool ok = false;

    if (physicalBoxElement != NULL)
    {
        std::string s = physicalBoxElement->GetText();

        // split string tokens
        //std::istringstream iss(s);
        //std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
        //std::istream_iterator<std::string>{}};
        std::vector<std::string> tokens = SpliteString(s);

        if (tokens.size() != 4)
        {
            std::cout << "Error: tokens.size() != 4 " << s << std::endl;
        }
        else
        {
            x0 = atof(tokens[0].c_str());
            y0 = atof(tokens[1].c_str());
            x1 = atof(tokens[2].c_str());
            y1 = atof(tokens[3].c_str());
            ok = true;
        }
    }

    return std::make_tuple(x0, y0, x1, y1, ok);
}
