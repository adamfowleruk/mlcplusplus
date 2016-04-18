/*
 * A C language sample to show fetching a document as a C struct and printing out to screen
 */
#include <stdio.h>
#include "ConnectionWrapper.h"
#include "ConnectionFactoryWrapper.h"
#include "ResponseWrapper.h"
#include "CStruct.h"
#include "CStructWrapper.h"

int main(int argc, const char * argv[])
{
	printf("Running getasstruct...\n");

    CConnection* ml = connectionfactory_getConnection();

    CResponse* response = connection_getDocument(ml,"/some/doc.json");

    const int rt = response_GetResponseType(response);
    printf("Response type: %i \n",rt);
    const int rc = response_GetResponseCode(response);
    printf("Response code: %i \n",rc);
    if (RESPONSETYPE_JSON == rt) {
    	//printf("This is /some/doc.json: %s \n",response_Json(response) );
    	// convert to struct and output relevant fields
    	struct sampledoc result; // from CStruct.h
    	cstruct_unpack(response,&result); // from CStructWrapper.h
    	printf("/some/doc.json contains a sampledoc with 'first' set to '%s' and 'second' set to '%s' \n",result.first,result.second);
    } else {
    	printf("Response: %s \n",response_String(response));
    }

    printf("getasstruct complete\n");
    return 0;
}