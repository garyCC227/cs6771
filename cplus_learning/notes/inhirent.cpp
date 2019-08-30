non-reference, non-pointer -> dynamic type is same as stastic type
reference, pointer -> stastic type is static type, but dynamic type may be casting


template with && rvalue -> will keep the value type be the same (for lvalue and rvalue)
std::forward is used to make sure the lvalue and rvalue will be match -> no change
--------- use to call another function with the same argument we given (since rvalue in function will convert to lvalue. 你懂的)
//TODO: check ... in github