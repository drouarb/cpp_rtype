//
// Created by lewis_e on 30/12/16.
//

#ifndef CPP_RTYPE_GRID_HH
#define CPP_RTYPE_GRID_HH

#include "Definitions.hh"
#include <vector>

#define GRID_CELL_SIZE 150
#define GRID_HEIGHT (FIELD_HEIGHT / GRID_CELL_SIZE + 2)
#define GRID_WIDTH ((FIELD_WIDTH + LEFT_MARGIN + RIGHT_MARGIN) / GRID_CELL_SIZE + 2)

namespace server
{
    class Entity;

    class Grid
    {
    public:
        typedef std::vector<Entity *> line_t[GRID_WIDTH];

        void remove(const Entity * entity);
        void add(Entity * entity);

        int getCoordinate(pos_t pos) const;

        line_t& operator[](int index);
        const line_t& operator[](int index) const;

    private:
        std::vector<Entity*> grid[GRID_HEIGHT][GRID_WIDTH];
    };
}

#endif //CPP_RTYPE_GRID_HH
