#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

in vec3 normal;
in vec3 FragPos;

out vec4 out_color;

// The blinn-phone BRDF
vec3 blinnPhongContribForLight(in vec3 diffuse_color, in vec3 specular_color, in float alpha, in vec3 p, in vec3 eye,
                          in vec3 lightPos, in vec3 lightIntensity) {
    vec3 N = normalize(normal);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));

    float dotLN = dot(L, N);
    float dotRV = dot(R, V);

    // Light not visible from this point
    if (dotLN < 0.0) {
        return vec3(0.0, 0.0, 0.0);
    }

    // Light reflection in opposite direction as viewer, apply only diffuse lighting
    if (dotRV < 0.0) {
        return lightIntensity * (diffuse_color * dotLN);
    }

    // Blinn - phong calculation
    vec3 half_direction = normalize(normalize(L) + V);
    float specular = pow(max(dot(half_direction, N), 0.0), 16.0);
    return (lightIntensity * diffuse_color * dotLN) +
           (specular_color * pow(dotRV, alpha) * specular);
}

vec3 blinnPhongIllumination(vec3 diffuse_color,
                            vec3 specular_color, float alpha,
                            vec3 light_pos, float light_intensity,
                            vec3 point_pos, vec3 eye) {
    vec3 light_I = light_intensity * vec3(1.0, 1.0, 1.0);

    vec3 color = blinnPhongContribForLight(diffuse_color, specular_color, alpha, point_pos, eye,
                                  light_pos,
                                  light_I);

    return color;
}

void main() {
    vec3 light_pos = vec3(0.0, 1.0, -3.0);
    float light_intensity = 0.5f;

    // Compute ambient light
    vec3 color = material.ambient;

    // Add the diffuse and specular components
    vec3 blinn_phong_contribution = blinnPhongIllumination(material.diffuse, material.specular, material.shininess * 128.0,
                                        light_pos, light_intensity, FragPos, vec3(0, 0, 0));
    color += blinn_phong_contribution;


	out_color = vec4(color, 1.0);
}
