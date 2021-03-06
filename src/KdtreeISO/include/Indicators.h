//
// Created by Danielhu on 2018/4/20.
//

#ifndef VOXELWORLD_INDICATORS_H
#define VOXELWORLD_INDICATORS_H

#include "Utils.h"

using glm::fvec2;
using glm::fvec3;
using glm::ivec3;

inline int encodeCell(ivec3 code) {
  return code.x * 4 + code.y * 2 + code.z;
}

inline const fvec3 &min_offset_subdivision(int i) {
  static const fvec3 offsets[8] = {
    fvec3(0.f, 0.f, 0.f),
    fvec3(0.f, 0.f, 1.f),
    fvec3(0.f, 1.f, 0.f),
    fvec3(0.f, 1.f, 1.f),
    fvec3(1.f, 0.f, 0.f),
    fvec3(1.f, 0.f, 1.f),
    fvec3(1.f, 1.f, 0.f),
    fvec3(1.f, 1.f, 1.f),
  };
  assert(i >= 0 && i < 8);
  return offsets[i];
};

inline const PositionCode &decodeCell(int i) {
  static const PositionCode offsets[8] = {
    PositionCode(0, 0, 0),
    PositionCode(0, 0, 1),
    PositionCode(0, 1, 0),
    PositionCode(0, 1, 1),
    PositionCode(1, 0, 0),
    PositionCode(1, 0, 1),
    PositionCode(1, 1, 0),
    PositionCode(1, 1, 1),
  };
  assert(i >= 0 && i < 8);
  return offsets[i];
};

inline const fvec3 &directionMap(int i) {
  static const fvec3 offsets[3] = {
    fvec3(1.f, 0.f, 0.f),
    fvec3(0.f, 1.f, 0.f),
    fvec3(0.f, 0.f, 1.f),
  };
  assert(i >= 0 && i < 3);
  return offsets[i];
}

// from original dc implementation

const int edge_map[12][2] = {
  {0, 4}, {1, 5}, {2, 6}, {3, 7}, // x-axis
  {0, 2},
  {1, 3},
  {4, 6},
  {5, 7}, // y-axis
  {0, 1},
  {2, 3},
  {4, 5},
  {6, 7} // z-axis
};

const int cellProcFaceMask[12][3] =
  {{0, 4, 0}, {1, 5, 0}, {2, 6, 0}, {3, 7, 0}, {0, 2, 1}, {4, 6, 1}, {1, 3, 1}, {5, 7, 1}, {0, 1, 2}, {2, 3, 2}, {4, 5, 2}, {6, 7, 2}};

const int cellProcEdgeMask[6][5] =
  {{0, 2, 1, 3, 0}, {4, 6, 5, 7, 0}, {0, 1, 4, 5, 1}, {2, 3, 6, 7, 1}, {0, 4, 2, 6, 2}, {1, 5, 3, 7, 2}};

const int faceProcFaceMask[3][4][3] = {
  {{4, 0, 0}, {5, 1, 0}, {6, 2, 0}, {7, 3, 0}},
  {{2, 0, 1}, {6, 4, 1}, {3, 1, 1}, {7, 5, 1}},
  {{1, 0, 2}, {3, 2, 2}, {5, 4, 2}, {7, 6, 2}}};

const int edgeTestNodeOrder[4][2] = {{0, 1}, {3, 2}, {1, 2}, {0, 3}};

inline const fvec3 &faceSubDivision(int dir, int i) {
  static const fvec3 offsets[3][4] = {
    {
      fvec3(0.f, 0.f, 0.f),
      fvec3(0.f, 0.f, 1.f),
      fvec3(0.f, 1.f, 0.f),
      fvec3(0.f, 1.f, 1.f),
    },
    {
      fvec3(0.f, 0.f, 0.f),
      fvec3(1.f, 0.f, 0.f),
      fvec3(0.f, 0.f, 1.f),
      fvec3(1.f, 0.f, 1.f),
    },
    {
      fvec3(0.f, 0.f, 0.f),
      fvec3(0.f, 1.f, 0.f),
      fvec3(1.f, 0.f, 0.f),
      fvec3(1.f, 1.f, 0.f),
    },
  };
  assert(i >= 0 && i < 4);
  return offsets[dir][i];
};

const int faceNodeOrder[4] = {0, 0, 1, 1};

const int faceProcEdgeMask[3][4][6] = {
  {{1, 4, 5, 0, 1, 1}, {1, 6, 7, 2, 3, 1}, {0, 4, 6, 0, 2, 2}, {0, 5, 7, 1, 3, 2}},
  {{0, 2, 3, 0, 1, 0}, {0, 6, 7, 4, 5, 0}, {1, 2, 6, 0, 4, 2}, {1, 3, 7, 1, 5, 2}},
  {{1, 1, 3, 0, 2, 0}, {1, 5, 7, 4, 6, 0}, {0, 1, 5, 0, 4, 1}, {0, 3, 7, 2, 6, 1}}};

inline const fvec3 &edgeProcDir(int i, int j) {
  const static fvec3 dirs[3][4] = {
    {
      fvec3(0.f, -1.f, -1.f),
      fvec3(0.f, -1.f, 1.f),
      fvec3(0.f, 1.f, 1.f),
      fvec3(0.f, 1.f, -1.f),
    },
    {
      fvec3(-1.f, 0.f, -1.f),
      fvec3(-1.f, 0.f, 1.f),
      fvec3(1.f, 0.f, 1.f),
      fvec3(1.f, 0.f, -1.f),
    },
    {
      fvec3(-1.f, -1.f, 0.f),
      fvec3(1.f, -1.f, 0.f),
      fvec3(1.f, 1.f, 0.f),
      fvec3(-1.f, 1.f, 0.f),
    },
  };
  assert(i >= 0 && i < 3 && i >= 0 && i < 4);
  return dirs[i][j];
};

const int edgeProcEdgeMask[3][2][4] = {
  {{3, 1, 2, 0}, {7, 5, 6, 4}},
  {{5, 4, 1, 0}, {7, 6, 3, 2}},
  {{6, 2, 4, 0}, {7, 3, 5, 1}},
};

const int planeSpreadingDir[3][2][4] = {
  {{0, 2, 3, 1}, {4, 6, 7, 5}},
  {{0, 1, 5, 4}, {2, 3, 7, 6}},
  {{0, 4, 6, 2}, {1, 5, 7, 2}},
};

const int intergralOrder[8] = {
  0, 1, 2, 4, 3, 5, 6, 7};
//
//const int planeSpreadingMask[8][8] = {
//    {0, 1, 2, 4, 3, 5, 6, 7},
//    {1, 0, 3, 5, 2, 4, 7, 6},
//    {2, 0, 3, 6, 1, 4, 7, 5},
//    {3, 1, 2, 7, 0, 5, 6, 4},
//    {4, 0, 5, 6, 1, 2, 7, 3},
//    {5, 1, 4, 7, 0, 3, 6, 2},
//    {6, 2, 4, 7, 0, 3, 5, 1},
//    {7, 3, 5, 6, 1, 2, 4, 0},
//};
//
//const int adjacentNodes[8][8] = {
//    {0, 1, 1, 0, 1, 0, 0, 0,},
//    {1, 0, 0, 1, 0, 1, 0, 0,},
//    {1, 0, 0, 1, 0, 0, 1, 0,},
//    {0, 1, 1, 0, 0, 0, 0, 1,},
//    {1, 0, 0, 0, 0, 1, 1, 0,},
//    {0, 1, 0, 0, 1, 0, 0, 1,},
//    {0, 0, 1, 0, 1, 0, 0, 1,},
//    {0, 0, 0, 1, 0, 1, 1, 0,},
//};

const int dirRelatedEdge[8][8][3] = {
  {
    {-1, -1, -1},
    {-1, 2, 6},
    {-1, 1, 10},
    {-1, -1, 0},
    {-1, 5, 9},
    {-1, -1, 4},
    {-1, -1, 8},
    {0, 4, 8},
  },
  {
    {-1, 3, 11},
    {-1, -1, -1},
    {-1, -1, 1},
    {-1, 0, 10},
    {-1, -1, 5},
    {-1, 4, 9},
    {1, 5, 8},
    {-1, -1, 8},
  },
  {
    {-1, 11, 3},
    {-1, -1, 2},
    {-1, -1, -1},
    {-1, 0, 6},
    {-1, -1, 9},
    {2, 4, 9},
    {-1, 5, 8},
    {-1, -1, 4},
  },
  {
    {-1, -1, 3},
    {-1, 2, 11},
    {-1, 1, 7},
    {-1, -1, -1},
    {3, 5, 9},
    {-1, -1, 9},
    {-1, -1, 5},
    {-1, 4, 8},
  },
  {
    {-1, 7, 11},
    {-1, -1, 5},
    {-1, -1, 10},
    {0, 6, 10},
    {-1, -1, -1},
    {-1, 2, 4},
    {-1, 1, 8},
    {-1, -1, 0},
  },
  {{-1, -1, 7}, {-1, 0, 11}, {1, 7, 10}, {-1, -1, 10}, {-1, 3, 5}, {-1, -1, -1}, {-1, -1, 1}, {-1, 1, 8}},
  {
    {-1, -1, 11},
    {2, 6, 11},
    {-1, 7, 10},
    {-1, -1, 6},
    {-1, 3, 9},
    {-1, -1, 2},
    {-1, -1, -1},
    {-1, 1, 4},
  },
  {
    {3, 7, 11},
    {-1, -1, 11},
    {-1, -1, 7},
    {-1, 6, 10},
    {-1, -1, 3},
    {-1, 2, 9},
    {-1, 1, 5},
    {-1, -1, -1},
  }};

const int processEdgeMask[3][4] = {{3, 2, 1, 0}, {7, 5, 6, 4}, {11, 10, 9, 8}};

constexpr int oppositeQuadIndex(int i) {
  return (i / 2) * 2 + 1 - i % 2;
}

constexpr int symmetryQuadIndex(int i) {
  return (1 - i / 2) * 2 + 1 - i % 2;
}

inline void quadIndex(int quadDir1, int quadDir2, int i, int &p1, int &p2) {
  ivec3 code(0);
  code[quadDir1] = i % 2;
  code[quadDir2] = i / 2;
  p1 = encodeCell(code);
  code[3 - quadDir1 - quadDir2] = 1;
  p2 = encodeCell(code);
}

//const int triangleIndices[6] = {0, 1, 2, 0, 2, 3};
//const int triangleIndicesFlip[6] = {0, 3, 2, 0, 2, 1};

#endif //VOXELWORLD_INDICATORS_H
