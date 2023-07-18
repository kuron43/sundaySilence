#pragma once

//当たり判定属性
const unsigned short COLLISION_ATTR_UNKNOWN = 0b0000000000000000;
const unsigned short COLLISION_ATTR_ALL = 0b1111111111111111;
const unsigned short COLLISION_ATTR_LANDSPHERE = 0b1 << 0;
const unsigned short COLLISION_ATTR_ALLIES = 0b1 << 1;
const unsigned short COLLISION_ATTR_ENEMIES = 0b1 << 2;
const unsigned short COLLISION_ATTR_ENEMIEBULLETS = 0b1 << 3;
const unsigned short COLLISION_ATTR_PLAYER = 0b1 << 4;
const unsigned short COLLISION_ATTR_PLAYERBULLETS = 0b1 << 5;
const unsigned short COLLISION_ATTR_BARRIEROBJECT = 0b1 << 6;