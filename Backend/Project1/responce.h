#pragma once
#include "requests.h"
class IRequestHandler;
struct Responce
{
	Buffer buffer;
	IRequestHandler* next;
};
struct LoginResponce :Responce
{
	
};
struct SignUpResponce : Responce
{
	
};
