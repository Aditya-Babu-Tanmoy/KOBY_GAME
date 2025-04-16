#pragma once

class Position {
public: // Change access specifier to public to make members accessible
   Position(int row, int column);
   int row;
   int column;
};