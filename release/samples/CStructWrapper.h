/*
 * A C wrapper for a C function that takes a sample JSON doc and puts it inside a C struct
 */
#include "CStruct.h"
#include "ResponseWrapper.h"

#ifndef CSTRUCTWRAPPER_H
#define CSTRUCTWRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// member/static wrapper functions
void cstruct_unpack(CResponse* resp,struct sampledoc* obj);

#ifdef __cplusplus
}
#endif


#endif