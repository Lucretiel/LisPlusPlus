#include "NilType.h"

ObjectH NilType::nilHandle(static_cast<Object*>(new NilType));