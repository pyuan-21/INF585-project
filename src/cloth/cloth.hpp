#pragma once

#include "cgp/cgp.hpp"

struct cloth_contact_info {
    cgp::vec3 offset; // from sphere's center to point on surface
    std::vector<size_t> connecting_spheres; // indices of connecting spheres
};

// Stores the buffers representing the cloth vertices
struct cloth_structure
{    
    // Buffers are stored as 2D grid that can be accessed as grid(ku,kv)
    cgp::grid_2D<cgp::vec3> position;  
    cgp::grid_2D<cgp::vec3> velocity;  
    cgp::grid_2D<cgp::vec3> force;
    cgp::grid_2D<cgp::vec3> normal;

    cgp::buffer<cloth_contact_info> contact_info;

    cgp::buffer<cgp::uint3> triangle_connectivity;

    // Also stores the triangle connectivity used to update the normals
    cgp::buffer<cgp::buffer<cgp::int3>> neighbor_cross_map;  // cross neighbor. each particle has its neighbor information: int3{ ku, kv, offset}
    cgp::buffer<cgp::buffer<cgp::int3>> neighbor_diagonal_map;  // diagonal neighbor
    
    void initialize(int N_samples_edge);  // Initialize a square flat cloth
    void update_normal();       // Call this function every time the cloth is updated before its draw
    int N_samples_edge() const; // Number of vertex along one dimension of the grid
    
    void precompute_neighbor(int resolution1, int resolution2);
    void initialize_contact_sphere();
};


// Helper structure and functions to draw a cloth
// ********************************************** //
struct cloth_structure_drawable
{
    cgp::mesh_drawable drawable;

    void initialize(int N_sample_edge);
    void update(cloth_structure const& cloth);
};

template <typename ENVIRONMENT>
void draw(cloth_structure_drawable const& drawable, ENVIRONMENT const& environment)
{
    draw(drawable.drawable, environment);
}
template <typename ENVIRONMENT>
void draw_wireframe(cloth_structure_drawable const& drawable, ENVIRONMENT const& environment)
{
    draw_wireframe(drawable.drawable, environment);
}