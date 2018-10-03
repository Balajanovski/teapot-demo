#version 330 core

layout (location = 0) in vec3 i_pos;
layout (location = 1) in vec3 i_normal;

out vec3 normal;
out vec3 FragPos;

#define MAX_OBJS_SAME_MODEL 100
uniform mat4 models[MAX_OBJS_SAME_MODEL];
uniform mat4 view;
uniform mat4 projection;

void main() {
    normal = mat3(transpose(inverse(models[gl_InstanceID]))) * i_normal;
    FragPos = vec3(models[gl_InstanceID] * vec4(i_pos, 1.0));
    gl_Position = projection * view * models[gl_InstanceID] * vec4(i_pos, 1.0);
}
