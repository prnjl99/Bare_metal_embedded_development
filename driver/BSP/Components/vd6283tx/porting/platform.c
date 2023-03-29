#include "vd6283tx.h"
#include "STALS_platform.h"

STALS_ErrCode_t STALS_WrByte(void *pClient, uint8_t index, uint8_t data)
{
	int32_t res;
	VD6283TX_Object_t *pObj = (VD6283TX_Object_t *) pClient;

	res = pObj->IO.WriteReg(pObj->IO.Address, index, &data, 1);

	if (res)
			return STALS_ERROR_WRITE;

	return STALS_NO_ERROR;
}

STALS_ErrCode_t STALS_RdByte(void *pClient, uint8_t index, uint8_t *data)
{
	int32_t res;
	VD6283TX_Object_t *pObj = (VD6283TX_Object_t *) pClient;

	res = pObj->IO.ReadReg(pObj->IO.Address, index, data, 1);

	if (res)
			return STALS_ERROR_READ;

	return STALS_NO_ERROR;
}

STALS_ErrCode_t STALS_RdMultipleBytes(void *pClient, uint8_t index, uint8_t *data, int nb)
{
	int32_t res;
	VD6283TX_Object_t *pObj = (VD6283TX_Object_t *) pClient;

	res = pObj->IO.ReadReg(pObj->IO.Address, index, data, nb);

	if (res)
			return STALS_ERROR_READ;

	return STALS_NO_ERROR;
}
