// A list of blinn-phong materials sourced from http://devernay.free.fr/cours/opengl/materials.html
// This data was converted into an unordered map for ease of use

#ifndef TEAPOT_DEMO_TEAPOTMATERIALS_H
#define TEAPOT_DEMO_TEAPOTMATERIALS_H

#include "Material.h"

#include <string>
#include <unordered_map>

const std::unordered_map<std::string, Material> materials_list = {
        {"emerald",Material{glm::vec3(0.0215,0.1745,0.0215),glm::vec3(0.07568,0.61424,0.07568),glm::vec3(0.633,0.727811,0.633),0.6}},
        {"jade",Material{glm::vec3(0.135,0.2225,0.1575),glm::vec3(0.54,0.89,0.63),glm::vec3(0.316228,0.316228,0.316228),0.1}},
        {"obsidian",Material{glm::vec3(0.05375,0.05,0.06625),glm::vec3(0.18275,0.17,0.22525),glm::vec3(0.332741,0.328634,0.346435),0.3}},
        {"pearl",Material{glm::vec3(0.25,0.20725,0.20725),glm::vec3(1,0.829,0.829),glm::vec3(0.296648,0.296648,0.296648),0.088}},
        {"ruby",Material{glm::vec3(0.1745,0.01175,0.01175),glm::vec3(0.61424,0.04136,0.04136),glm::vec3(0.727811,0.626959,0.626959),0.6}},
        {"turquoise",Material{glm::vec3(0.1,0.18725,0.1745),glm::vec3(0.396,0.74151,0.69102),glm::vec3(0.297254,0.30829,0.306678),0.1}},
        {"brass",Material{glm::vec3(0.329412,0.223529,0.027451),glm::vec3(0.780392,0.568627,0.113725),glm::vec3(0.992157,0.941176,0.807843),0.21794872}},
        {"bronze",Material{glm::vec3(0.2125,0.1275,0.054),glm::vec3(0.714,0.4284,0.18144),glm::vec3(0.393548,0.271906,0.166721),0.2}},
        {"chrome",Material{glm::vec3(0.25,0.25,0.25),glm::vec3(0.4,0.4,0.4),glm::vec3(0.774597,0.774597,0.774597),0.6}},
        {"copper",Material{glm::vec3(0.19125,0.0735,0.0225),glm::vec3(0.7038,0.27048,0.0828),glm::vec3(0.256777,0.137622,0.086014),0.1}},
        {"gold",Material{glm::vec3(0.24725,0.1995,0.0745),glm::vec3(0.75164,0.60648,0.22648),glm::vec3(0.628281,0.555802,0.366065),0.4}},
        {"silver",Material{glm::vec3(0.19225,0.19225,0.19225),glm::vec3(0.50754,0.50754,0.50754),glm::vec3(0.508273,0.508273,0.508273),0.4}},
        {"black plastic",Material{glm::vec3(0.0,0.0,0.0),glm::vec3(0.01,0.01,0.01),glm::vec3(0.50,0.50,0.50),0.25}},
        {"cyan plastic",Material{glm::vec3(0.0,0.1,0.06),glm::vec3(0.0,0.50980392,0.50980392),glm::vec3(0.50196078,0.50196078,0.50196078),0.25}},
        {"green plastic",Material{glm::vec3(0.0,0.0,0.0),glm::vec3(0.1,0.35,0.1),glm::vec3(0.45,0.55,0.45),0.25}},
        {"red plastic",Material{glm::vec3(0.0,0.0,0.0),glm::vec3(0.5,0.0,0.0),glm::vec3(0.7,0.6,0.6),0.25}},
        {"white plastic",Material{glm::vec3(0.0,0.0,0.0),glm::vec3(0.55,0.55,0.55),glm::vec3(0.70,0.70,0.70),0.25}},
        {"yellow plastic",Material{glm::vec3(0.0,0.0,0.0),glm::vec3(0.5,0.5,0.0),glm::vec3(0.60,0.60,0.50),0.25}},
        {"black rubber",Material{glm::vec3(0.02,0.02,0.02),glm::vec3(0.01,0.01,0.01),glm::vec3(0.4,0.4,0.4),0.078125}},
        {"cyan rubber",Material{glm::vec3(0.0,0.05,0.05),glm::vec3(0.4,0.5,0.5),glm::vec3(0.04,0.7,0.7),0.078125}},
        {"green rubber",Material{glm::vec3(0.0,0.05,0.0),glm::vec3(0.4,0.5,0.4),glm::vec3(0.04,0.7,0.04),0.078125}},
        {"red rubber",Material{glm::vec3(0.05,0.0,0.0),glm::vec3(0.5,0.4,0.4),glm::vec3(0.7,0.04,0.04),0.078125}},
        {"white rubber",Material{glm::vec3(0.05,0.05,0.05),glm::vec3(0.5,0.5,0.5),glm::vec3(0.7,0.7,0.7),0.078125}},
        {"yellow rubber",Material{glm::vec3(0.05,0.05,0.0),glm::vec3(0.5,0.5,0.4),glm::vec3(0.7,0.7,0.04),0.078125}},
        {"jade",Material{glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 12.8f/128.0f}},
        {"polished gold",Material{glm::vec3(0.24725f,0.2245f,0.0645f),glm::vec3(0.34615f,0.3143f,0.0903f),glm::vec3(0.797357f,0.723991f,0.208006f),83.2f/128.0f}},
};



#endif //TEAPOT_DEMO_TEAPOTMATERIALS_H
