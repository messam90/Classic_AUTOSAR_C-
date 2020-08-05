/*
 * PduR.h
 *
 *  Created on: Mar 19, 2019
 *      Author: messam
 */

#ifndef STUBS_PDUR_H_
#define STUBS_PDUR_H_

#include "std_types.h"
#include <vector>

namespace PduR{
class PduR{
public:
	Std_ReturnType CanIfTriggerTransmit(PduIdType TxPduId, PduInfoType& PduInfoPtr);
	void CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);
	void CanIfRxIndication(PduIdType RxPduId, const PduInfoType& PduInfoPtr);
};
}

#endif /* STUBS_PDUR_H_ */
