#pragma once
#include "util.h"
#include "ball.h"
#include "paddle.h"

template<typename PaddleType>
Contact CheckPaddleCollision(Ball const& ball, PaddleType const& paddle);

template<typename BallType>
Contact CheckWallCollision(BallType const& ball);

#include "collision.tpp"