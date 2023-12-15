#include <component.h>

void Transform::set(const Coord& coord, glm::vec3& vert)
{
    switch (coord.axis)
    {
        case AXIS::X:
            vert.x = coord.val;
            break;
        case AXIS::Y:
            vert.y = coord.val;
            break;
        case AXIS::Z:
            vert.z = coord.val;
            break;
        default:
            break;
    }
}

std::vector<glm::vec4> Transform::transform(const std::vector<glm::vec4>& vertex)
{
    auto transform = glm::mat4(1.0f);
    transform = glm::translate(transform, __pos);
    transform = glm::rotate(transform, glm::radians(__rotate.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(__rotate.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(__rotate.z), glm::vec3(0, 0, 1));
    transform = glm::scale(transform, __scale);

    std::vector<glm::vec4> transformed_vertex;
    for (auto& vert : vertex) {
        transformed_vertex.emplace_back(transform * vert);
    }
    return transformed_vertex;
}

void Renderable::render(GLenum mode)
{
    if (changed) {
        transformed_vertex = transform(vertex);
        changed = false;
    }
    glPushMatrix();
    glColor3f(colour.x, colour.y, colour.z);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    // if (texture.size()) {
    //     glBindTexture(GL_TEXTURE_2D, texture[0]);
    // }
    glBegin(mode);
        for (int i = 0; i < transformed_vertex.size(); ++i) {
            // glTexCoord2f(tex_idx[i % 4].x, tex_idx[i % 4].y);
            glVertex3f(transformed_vertex[i].x, 
                       transformed_vertex[i].y,
                       transformed_vertex[i].z);
        }
    glEnd();
    glPopMatrix();
}

Rectangle::Rectangle(const float& w, const float& h)
{
    vertex.emplace_back(glm::vec4(0, 0, 0, 1));
    vertex.emplace_back(glm::vec4(w, 0, 0, 1));
    vertex.emplace_back(glm::vec4(w, h, 0, 1));
    vertex.emplace_back(glm::vec4(0, h, 0, 1));
}

void Rectangle::render()
{
    Renderable::render(GL_QUADS);
}

Circle::Circle(const T& radius, int count)
{
    vertex.emplace_back(glm::vec4{0, 0, 0, 1});
    const float angle = 360.0f / count;
    for (int i = 0; i < count; ++i) {
        float theta = angle * i;
        vertex.emplace_back(glm::vec4(
                    radius * cos(glm::radians(theta)),
                    radius * sin(glm::radians(theta)),
                    0.0f, 1.0f));
    }
    vertex.emplace_back(glm::vec4(0, radius, 0, 1));
}

void Circle::render()
{
    Renderable::render(GL_TRIANGLE_FAN);
}

Sphere::Sphere(const float& radius, const int& stacks, const int& slices) 
{
        for (int i = 0; i < stacks; ++i) {
            float phi1 = M_PI * (float) i / stacks;
            float phi2 = M_PI * (float) (i + 1) / stacks;
            for (int j = 0; j < slices; ++j) {
                float theta1 = 2 * M_PI * (float) j / slices;
                float theta2 = 2 * M_PI * (float) (j + 1) / slices;
                vertex.emplace_back(
                        radius * sin(phi1) * cos(theta1),
                        radius * sin(phi1) * sin(theta1),
                        radius * cos(phi1), 1);
                vertex.emplace_back(
                        radius * sin(phi1) * cos(theta2),
                        radius * sin(phi1) * sin(theta2),
                        radius * cos(phi1), 1);
                vertex.emplace_back(
                        radius * sin(phi2) * cos(theta2),
                        radius * sin(phi2) * sin(theta2),
                        radius * cos(phi2), 1);

                vertex.emplace_back(vertex[vertex.size() - 3]);
                vertex.emplace_back(vertex[vertex.size() - 2]);
                vertex.emplace_back(
                        radius * sin(phi2) * cos(theta1),
                        radius * sin(phi2) * sin(theta1),
                        radius * cos(phi2), 1);
            }
        }
}

void Sphere::render()
{
    Renderable::render(GL_TRIANGLES);
}

// Skybox::Skybox(const float& len)
// {
//     vertex = {
//         {-len, -len, -len}, { len, -len, -len}, { len,  len, -len},
//         {-len,  len, -len}, { len, -len, -len}, { len, -len,  len},
//         { len,  len,  len}, { len,  len, -len}, { len, -len,  len},
//         {-len, -len,  len}, {-len,  len,  len}, { len,  len,  len},
//         {-len, -len,  len}, {-len, -len, -len}, {-len,  len, -len},
//         {-len,  len,  len}, {-len,  len, -len}, { len,  len, -len},
//         { len,  len,  len}, {-len,  len,  len}, { len, -len, -len},
//         {-len, -len, -len}, {-len, -len,  len}, { len, -len,  len},
//     };
// }

/*
void Skybox::draw(GLenum mode) 
{
    glPushMatrix();
    this->transform();
    glBegin(mode);
        for (int i = 0; i < (int) vertex.size(); ++i) {
            if (!(i % 4)) {
                glBindTexture(GL_TEXTURE_2D, 
                        (i / 4 < texture.size() ? texture[i / 4] : 
                         texture.size() ? texture.back() : 0));
            }
            glTexCoord2f(tex_idx[i % 4].x, tex_idx[i % 4].y);
            glVertex3f(vertex[i].x, vertex[i].y, vertex[i].z);
        }
    glEnd();
    glPopMatrix();
}

*/
