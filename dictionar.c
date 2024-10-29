#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


#define DICTIONARY_ITEM_KEY_BUFFER_SIZE  16
#define DICTIONARY_ITEM_VALUE_BUFFER_SIZE 24
#define DICTIONARY_ITEMS_CAPACITY 10

typedef struct T_item{
    bool valid;
    char key[DICTIONARY_ITEM_KEY_BUFFER_SIZE];
    char value[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
}T_item;

typedef struct TDictionary{
    T_item items[DICTIONARY_ITEMS_CAPACITY];
}TDictionary;

typedef enum StatusCode{
    DICTIONARY_SUCCESS,
    DICTIONARY_INVALID_KEY,
    DICTIONARY_READ_NO_SUCH_KEY,
    DICTIONARY_ITEMS_CAPACITY_EXCEEDED,
    DICTIONARY_ITEM_KEY_BUFFER_SIZE_EXCEEDED,
    DICTIONARY_ITEM_VALUE_BUFFER_SIZE_EXCEEDED,
    DICTIONARY_DESTINATION_IS_NULL,
    DICTIONARY_DESTIONATION_TOO_SMALL,
    JAVA_NULL_POINTER_EXCEPTION,
} StatusCode;

int strlcpy(char *dst, char*src, size_t destMaxSize){
    strncpy(dst,src, destMaxSize);
    dst[destMaxSize-1] = 0;
    return /* dummy */ 0;
}


char * TDictionary_getStatusName(int status){
    // "serializare,reflexie"
    if (DICTIONARY_SUCCESS == status){
        return "DICTIONARY_SUCCESS";
    }
    if (DICTIONARY_INVALID_KEY == status){
        return "DICTIONARY_INVALID_KEY";
    }
    if (DICTIONARY_READ_NO_SUCH_KEY == status){
        return "DICTIONARY_READ_NO_SUCH_KEY";
    }
    if (DICTIONARY_ITEMS_CAPACITY_EXCEEDED == status){
        return "DICTIONARY_ITEMS_CAPACITY_EXCEEDED";
    }
    if (DICTIONARY_ITEM_KEY_BUFFER_SIZE_EXCEEDED == status){
        return "DICTIONARY_ITEM_KEY_BUFFER_SIZE_EXCEEDED";
    }
    if (DICTIONARY_ITEM_VALUE_BUFFER_SIZE_EXCEEDED == status){
        return "DICTIONARY_ITEM_VALUE_BUFFER_SIZE_EXCEEDED";
    }
    if (DICTIONARY_DESTINATION_IS_NULL == status){
        return "DICTIONARY_DESTINATION_IS_NULL";
    }
    if (DICTIONARY_DESTIONATION_TOO_SMALL == status){
        return "DICTIONARY_DESTIONATION_TOO_SMALL";
    }
    if (JAVA_NULL_POINTER_EXCEPTION == status){
        return "JAVA_NULL_POINTER_EXCEPTION";
    }
    return "???";
}


int TDictionary_readKeyAtIndex(TDictionary *self, int keyIndex, char *dstBuffer, size_t dstBufferSize){
    /* make sure the dict exists
    make sure the key index makes sense, if keyIndex < 0 ???? keyIdnex > capacity,off by one, etc
    make sure dstBuffer is not null
    make sure the destinatin size is large enough to fit the strlen key
    if valid item at index keyIndex
    then strcpy
    return status code */
    if (NULL == self){
        return JAVA_NULL_POINTER_EXCEPTION;
    }
    if(keyIndex < 0 || keyIndex >= DICTIONARY_ITEMS_CAPACITY){
        return DICTIONARY_INVALID_KEY;
    }
    if(NULL == dstBuffer){
        return DICTIONARY_DESTINATION_IS_NULL;
    }
    StatusCode ret = DICTIONARY_SUCCESS;
    if (self->items[keyIndex].valid){
        size_t lenKey = strlen(self->items[keyIndex].key);
        if (lenKey + 1 > dstBufferSize){
            return DICTIONARY_DESTIONATION_TOO_SMALL;
        }
        strcpy(dstBuffer, self->items[keyIndex].key);
    }
    else{
        return DICTIONARY_INVALID_KEY;
    }
    return ret;

}

void TDictionary_clearAll(TDictionary *self){
    for(int i=0;i<DICTIONARY_ITEMS_CAPACITY;i++)
    {
        self->items[i].valid=0;
    }
}

int getFirstAvailableSlot(TDictionary *dict){
    // input: a valid dictionary
    // output: -1 if dict is full, otherwise a number between [0..cap-1], the index of the first (.valid == false) item
    int ret=-1;
    for(int i=0; i<=DICTIONARY_ITEMS_CAPACITY; i++)
    {
        if(dict->items[i].valid)
        {
            //carry on
        }
        else {
            if (-1 == ret){
                ret=i;
            }else{
                // already found first value
            }
        }
    }
    return ret;
}

int getKeyIndex(char *k, TDictionary *self){
    int ret=-1;
    for(int i = 0; i < DICTIONARY_ITEMS_CAPACITY ; i++){
        if(self->items[i].valid)
        {
            if(strcmp(self->items[i].key, k) == 0){
                ret=i;
            }
            else{
                //carry on
            }
        }
        else {
            //carry on
        }
    }
    return ret;
}

StatusCode TDictionary_writeValue(TDictionary *self, char *key, char *v){
    // adds, updates or removes key-value pair:
    //  input: key, value, self
    //           if value===NULL removes key
    //  output: result code
    if (NULL == self){
        return JAVA_NULL_POINTER_EXCEPTION;
    }
    if (NULL == key){
        return DICTIONARY_INVALID_KEY;
    }
    size_t lenKey = strlen(key);
    if (lenKey < 1){
        return DICTIONARY_INVALID_KEY;
    }
    if (lenKey >= DICTIONARY_ITEM_KEY_BUFFER_SIZE){
        return DICTIONARY_ITEM_KEY_BUFFER_SIZE_EXCEEDED;
    }
    StatusCode ret = DICTIONARY_SUCCESS;
    int ki= getKeyIndex(key, self);
    if (NULL == v){
        // TODO
       if (-1 == ki){
           // cheia asta nici nu exista,nu avem nimic de facut
       }
       else {
           self->items[ki].valid = 0;
       }

    }
    else{
        // TODO
        size_t lenValue = strlen(v);
        if(lenValue >= DICTIONARY_ITEM_VALUE_BUFFER_SIZE){
            return DICTIONARY_ITEM_VALUE_BUFFER_SIZE_EXCEEDED;
        }
        else{
            if (-1 == ki){
                //TODO find a slot
                int slot = getFirstAvailableSlot(self);
                if(-1 == slot){
                    return DICTIONARY_ITEMS_CAPACITY_EXCEEDED;
                }
                else{
                    strcpy(self->items[slot].key, key);
                    strcpy(self->items[slot].value, v);
                    self->items[slot].valid = true;
                }
            }
            else{
                //overwrite existing slot
                strcpy(self->items[ki].value, v);
            }

        }
    }
    return ret;
}

StatusCode TDictionary_readValue(TDictionary *self, char *key, char *vDest, size_t vDestBufferSize){
    // TODO
    // verificari
    // lookup cheie
    // populare vDest
    // returnare code de eroare
    if(NULL == self){
        return JAVA_NULL_POINTER_EXCEPTION;
    }
    if (NULL == key){
        return DICTIONARY_INVALID_KEY;
    }
    size_t lenKey = strlen(key);
    if (lenKey < 1){
        return DICTIONARY_INVALID_KEY;
    }
    if (lenKey >= DICTIONARY_ITEM_KEY_BUFFER_SIZE){
        return DICTIONARY_ITEM_KEY_BUFFER_SIZE_EXCEEDED;
    }
    if(NULL == vDest){
        return DICTIONARY_DESTINATION_IS_NULL;

    }
    StatusCode ret = DICTIONARY_SUCCESS;
    int ki = getKeyIndex(key, self);
    if(-1 == ki){
        return DICTIONARY_READ_NO_SUCH_KEY;
    }
    size_t lenValue = strlen(self->items[ki].value);
    if(lenValue + 1 > vDestBufferSize){
        return DICTIONARY_DESTIONATION_TOO_SMALL;
    }
    strcpy(vDest, self->items[ki].value);
    return ret;

}


//---------TEST FUNCTIONS-----------//
//---------------------------------//

int TDictionary_writeValue_test(){

    TDictionary *self = malloc(sizeof(TDictionary));
    char testName[100] = "Function to WRITE key-value pair";
    int err=0;
    int subTestIndex=0;
    StatusCode actualStatus;
    StatusCode expectedStatus;
    char key[DICTIONARY_ITEM_KEY_BUFFER_SIZE];
    char tooLongKey[DICTIONARY_ITEM_KEY_BUFFER_SIZE +1];
    char value[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
    char tooLongValue[DICTIONARY_ITEM_VALUE_BUFFER_SIZE+1];
    char buffer[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];

    //-------------------------------------------------//
    //typical case > write valid key-value pair

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strcpy(value, "valid value");
    //expectations
    expectedStatus=DICTIONARY_SUCCESS;

    //execution
    actualStatus = TDictionary_writeValue(self, key, value);
    if(actualStatus != expectedStatus){
        printf("(1) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    // corner case > write with null key

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");

    //expectations
    expectedStatus=DICTIONARY_INVALID_KEY;

    //execution
    actualStatus = TDictionary_writeValue(self, NULL, value);
    if(actualStatus != expectedStatus){
        printf("(2) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }
    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    // corner case > write with null value, delete pair

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strcpy(value, "valid value");

    // ----- //
    //STEP1 > Write valid pair
    TDictionary_writeValue(self, key, value);
    //STEP2 > Verify value is successfully written
    expectedStatus=DICTIONARY_SUCCESS;
    actualStatus = TDictionary_readValue(self, key, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(3) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }
    //STEP3 > Write null to delete pair
    actualStatus = TDictionary_writeValue(self, key, NULL);
    //STEP4 > Verify that write NULL value has successful status
    if(actualStatus != expectedStatus){
        printf("(4) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }
    //STEP5 > Verify that pair does not exist anymore
    expectedStatus=DICTIONARY_READ_NO_SUCH_KEY;
    actualStatus = TDictionary_readValue(self, key, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(5) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        printf("key %s \r\n",key);
        printf("buffer %s \r\n", buffer);
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    // corner case > write key too long

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strlcpy(tooLongKey, "key longer than DICTIONARY_ITEM_KEY_BUFFER_SIZE", sizeof(tooLongKey));
    strcpy(value, "valid value");

    //expectations
    expectedStatus=DICTIONARY_ITEM_KEY_BUFFER_SIZE_EXCEEDED;

    //execution
    actualStatus = TDictionary_writeValue(self, tooLongKey, value);
    if(actualStatus != expectedStatus){
        printf("(6) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    // corner case > write value too long

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strlcpy(tooLongValue, "value longer than DICTIONARY_ITEM_VALUE_BUFFER_SIZE", sizeof(tooLongValue));

    //expectations
    expectedStatus=DICTIONARY_ITEM_VALUE_BUFFER_SIZE_EXCEEDED;

    //execution
    actualStatus = TDictionary_writeValue(self, key, tooLongValue);
    if(actualStatus != expectedStatus){
        printf("(7) While testing:%s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    // corner case > write too many pairs

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");

    //expectations
    expectedStatus=DICTIONARY_ITEMS_CAPACITY_EXCEEDED;

    //execution
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY+1; i++){
        sprintf(key,"key%d",i);
        actualStatus=TDictionary_writeValue(self, key,value);
    }
    if(actualStatus != expectedStatus){
        printf("(8) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    free(self);

    return err;
}

int TDictionary_readValue_test(){

    TDictionary *self = malloc(sizeof(TDictionary));
    char testName[100] = "Function to READ value of a key to buffer";
    int err=0;
    int subTestIndex=0;
    StatusCode actualStatus;
    StatusCode expectedStatus;
    char key[DICTIONARY_ITEM_KEY_BUFFER_SIZE];
    char differentKey[DICTIONARY_ITEM_KEY_BUFFER_SIZE];
    char value[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
    char buffer[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
    char tooSmallBuffer[DICTIONARY_ITEM_VALUE_BUFFER_SIZE-1];

    //-------------------------------------------------//
    //typical case > read value of valid key to buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);

    //expectations
    expectedStatus=DICTIONARY_SUCCESS;

    //execution
    actualStatus = TDictionary_readValue(self, key, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(A) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    //corner case > read value of NULL key to buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);

    //expectations
    expectedStatus=DICTIONARY_INVALID_KEY;

    //execution
    actualStatus = TDictionary_readValue(self, NULL, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(B) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read value of key not in dictionary to buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strcpy(differentKey, "different key");
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);

    //expectations
    expectedStatus=DICTIONARY_READ_NO_SUCH_KEY;

    //execution
    actualStatus = TDictionary_readValue(self, differentKey, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(C) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read value of valid key to NULL buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);

    //expectations
    expectedStatus=DICTIONARY_DESTINATION_IS_NULL;

    //execution
    actualStatus = TDictionary_readValue(self, key, NULL, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(D) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    //-------------------------------------------------//
    //corner case > read value of valid key to small buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(key, "valid key");
    strlcpy(value, "value longer than DICTIONARY_ITEM_VALUE_BUFFER_SIZE", sizeof(value));
    TDictionary_writeValue(self, key, value);

    //expectations
    expectedStatus=DICTIONARY_DESTIONATION_TOO_SMALL;

    //execution
    actualStatus = TDictionary_readValue(self, key, tooSmallBuffer, sizeof(tooSmallBuffer));
    if(actualStatus != expectedStatus){
        printf("(E) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    free(self);

    return err;
}

int TDictionary_readKeyAtIndex_test(){

    TDictionary *self = malloc(sizeof(TDictionary));
    int err=0;
    char testName[100] = "Function to READ value of a key at a specific index to buffer";
    int keyIndex;
    int subTestIndex=0;
    StatusCode actualStatus;
    StatusCode expectedStatus;
    char key[DICTIONARY_ITEM_KEY_BUFFER_SIZE];
    char value[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
    char buffer[DICTIONARY_ITEM_VALUE_BUFFER_SIZE];
    char tooSmallBuffer[DICTIONARY_ITEM_KEY_BUFFER_SIZE-1];

    //-------------------------------------------------//
    //typical case > read key at a specific index to buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);
    keyIndex = 2;
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY; i++){
        sprintf(key, "key%d",i);
        TDictionary_writeValue(self, key,value);
    }

    //expectations
    expectedStatus=DICTIONARY_SUCCESS;

    //execution
    actualStatus = TDictionary_readKeyAtIndex(self, keyIndex, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(alpha) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read key at a specific index [greater than dictionary capacity] to buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);
    keyIndex = DICTIONARY_ITEMS_CAPACITY+1;
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY; i++){
        sprintf(key, "key%d",i);
        TDictionary_writeValue(self, key,value);
    }

    //expectations

    expectedStatus=DICTIONARY_ITEMS_CAPACITY_EXCEEDED;

    //execution
    actualStatus = TDictionary_writeValue(self, "somedummy", "some value");
    if(actualStatus != expectedStatus){
        printf("(beta) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read key at a specific index [negative] to buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);
    keyIndex = -1;
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY; i++){
        sprintf(key, "key%d",i);
        TDictionary_writeValue(self, key,value);
    }

    //expectations
    expectedStatus=DICTIONARY_INVALID_KEY;

    //execution
    actualStatus = TDictionary_readKeyAtIndex(self, keyIndex, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(gamma) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read key at a specific index to buffer, but item is not valid

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);
    keyIndex = 2;
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY; i++){
        sprintf(key, "key%d",i);
        TDictionary_writeValue(self, key,value);
    }
    self->items[keyIndex].valid = false;

    //expectations
    expectedStatus=DICTIONARY_INVALID_KEY;

    //execution
    actualStatus = TDictionary_readKeyAtIndex(self, keyIndex, buffer, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(delta) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read key at a specific index to NULL buffer

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");
    TDictionary_writeValue(self, key, value);
    keyIndex = 2;
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY; i++){
        sprintf(key, "key%d",i);
        TDictionary_writeValue(self, key,value);
    }

    //expectations
    expectedStatus=DICTIONARY_DESTINATION_IS_NULL;

    //execution
    actualStatus = TDictionary_readKeyAtIndex(self, keyIndex, NULL, sizeof(buffer));
    if(actualStatus != expectedStatus){
        printf("(epsilon) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);


    //-------------------------------------------------//
    //corner case > read key at a specific index to buffer, but sizeof buffer too small

    //preconditions, buildup
    subTestIndex++;
    TDictionary_clearAll(self);
    strcpy(value, "valid value");
    keyIndex = 2;
    for (int i=0; i<DICTIONARY_ITEMS_CAPACITY; i++){
        sprintf(key, "key%d",i);
        if (i==keyIndex){
            strlcpy(key, "special key longer than DICTIONARY_ITEM_KEY_BUFFER_SIZE",sizeof(key));
            TDictionary_writeValue(self, key,value);
        }
        TDictionary_writeValue(self, key,value);
    }

    //expectations
    expectedStatus=DICTIONARY_DESTIONATION_TOO_SMALL;

    //execution
    actualStatus = TDictionary_readKeyAtIndex(self, keyIndex, tooSmallBuffer, sizeof(tooSmallBuffer));
    if(actualStatus != expectedStatus){
        printf("(eta) While testing %s, subtest %d FAILED. Expected %s but found %s\n", testName, subTestIndex, TDictionary_getStatusName(expectedStatus),TDictionary_getStatusName(actualStatus));
        err++;
    }

    //cleanup
    TDictionary_clearAll(self);

    free(self);
    return err;
}

int main(){

    //running tests
    int errCount = 0;
    errCount += TDictionary_writeValue_test();
    errCount += TDictionary_readValue_test();
    errCount += TDictionary_readKeyAtIndex_test();

    //check results
    if(0 == errCount){
        printf("All tests PASSED\n");
    }else{
        printf("Total FAILED subtests: %d", errCount);
    }
    return 0;

}
